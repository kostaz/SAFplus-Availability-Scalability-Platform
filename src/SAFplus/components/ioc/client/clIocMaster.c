
/*
 * Copyright (C) 2002-2012 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 * 
 * The source code for  this program is not published  or otherwise 
 * divested of  its trade secrets, irrespective  of  what  has been 
 * deposited with the U.S. Copyright office.
 * 
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 * 
 * For more  information, see  the file  COPYING provided with this
 * material.
 */

#include <fcntl.h>
#include <clCommon6.h>

#include <clCommonErrors6.h>
#include <clThreadApi.hxx>
//#include <clOsalApi.h>
//#include <clLogApi.hxx>
#include <clIocApi.h>
#include <clIocErrors.h>
#include <clIocMaster.h>
#include <clIocSetup.h>
#include <clIocConfig.h>
#include <clIocNeighComps.h>
#include <clTransport.h>

using namespace SAFplus;

#define CL_IOC_MASTER_ADDRESS_RETRIES (10)

static ClIocNodeAddressT *gpClIocMasterSeg;
static SAFplus::ProcSem* gClIocMasterSem = NULL;

/*
 * Locate the master through the LA availability.
 */
ClRcT clIocTryMasterAddressGet(ClIocLogicalAddressT logicalAddress,
                                      ClIocPortT portId,
                                      ClIocNodeAddressT *pIocNodeAddress
                                      )
{
    return clTransportMasterAddressGetDefault(logicalAddress, portId, pIocNodeAddress);
}


/*
 * Locate the master through the LA availability.
 */
ClRcT clIocMasterAddressGetExtended(ClIocLogicalAddressT logicalAddress,
                                    ClIocPortT portId,
                                    ClIocNodeAddressT *pIocNodeAddress,
                                    ClInt32T numRetries,
                                    uint_t delayMs)
{
    ClRcT rc = CL_OK;
    ClInt32T retryCnt = CL_IOC_MASTER_ADDRESS_RETRIES;
    ClIocNodeAddressT node = 0;
    ClInt32T nodeStatus = 1;
    ClInt32T mask = 1;

    if(portId >= CL_IOC_MAX_COMPONENTS_PER_NODE)
        return CL_IOC_RC(CL_ERR_OUT_OF_RANGE);

    if(!gpClIocMasterSeg || !gpClIocNeighComps)
        return CL_IOC_RC(CL_ERR_NOT_INITIALIZED);

    if(pIocNodeAddress == NULL)
        return CL_IOC_RC(CL_ERR_NULL_POINTER);

    if(numRetries)
        retryCnt = numRetries;

    gClIocMasterSem->lock();
    node = gpClIocMasterSeg[portId]; 

    if(node)
    {
        switch(portId)
        {
        case CL_IOC_CKPT_PORT:
            nodeStatus <<= CL_IOC_NEIGH_COMPS_STATUS_GET(node, CL_IOC_CKPT_PORT);
            mask <<= 1;
            /*
             * fall through
             */
        case CL_IOC_GMS_PORT:
            nodeStatus <<= CL_IOC_NEIGH_COMPS_STATUS_GET(node, CL_IOC_GMS_PORT);
            mask <<= 1;
            /*
             * fall through
             */
        case CL_IOC_LOG_PORT:
            nodeStatus <<= CL_IOC_NEIGH_COMPS_STATUS_GET(node, CL_IOC_LOG_PORT);
            mask <<= 1;
            /*
             *fall through
             */
        case CL_IOC_CPM_PORT:
            nodeStatus <<= CL_IOC_NEIGH_COMPS_STATUS_GET(node, CL_IOC_CPM_PORT);
            mask <<= 1;
            nodeStatus &= mask;
            break;

        default:
            nodeStatus = CL_IOC_NEIGH_NODE_STATUS_GET(node);
            break;
        }
     
        if(!nodeStatus)
            node = 0;
    }
    gClIocMasterSem->unlock();

    if(node == 0)
    {
        do {    
            /*
             * if this call is made during transcient time of switchover/failover,
             * this may fail, so retrying to ensure that master is 
             * not there 
             */
            rc = clIocTryMasterAddressGet(logicalAddress, portId, &node);
            if( CL_OK == rc ) 
            {
                gClIocMasterSem->lock();
                *pIocNodeAddress = gpClIocMasterSeg[portId] = node;
                gClIocMasterSem->unlock();
                logInfo("IOC", "MASTER", "Setting node [%d] as master for comp [%d].", node, portId);
                break;
            }
            logWarning("IOC","MASTER","Cannot get IOC master, return code [0x%x]",rc);
            boost::this_thread::sleep(boost::posix_time::milliseconds(delayMs));
        } while(--retryCnt > 0);
    }
    else
    {
        *pIocNodeAddress = node;
    }

    return rc;
}


ClRcT clIocMasterAddressGet(ClIocLogicalAddressT logicalAddress,
        ClIocPortT portId,
        ClIocNodeAddressT *pIocNodeAddress)
{
    return clIocMasterAddressGetExtended(logicalAddress, portId, pIocNodeAddress, 0, NULL);
}


void clIocMasterSegmentInitialize(void *pMasterSegment, ProcSem& masterSem)
{
    gpClIocMasterSeg = (ClIocNodeAddressT *)pMasterSegment;
    gClIocMasterSem = &masterSem;
}

void clIocMasterSegmentFinalize(void)
{
    gpClIocMasterSeg = NULL;
}

void clIocMasterSegmentSet(ClIocPhysicalAddressT compAddr, ClIocNodeAddressT master)
{
    ClUint32T i;

    if(!gpClIocMasterSeg || compAddr.portId >= CL_IOC_MAX_COMPONENTS_PER_NODE) 
        return;

    gClIocMasterSem->lock();
    if(compAddr.portId == CL_IOC_XPORT_PORT)
    {
        ClBoolT resetAll = CL_FALSE;
        if(!compAddr.nodeAddress)
        {
            resetAll = CL_TRUE;
            if (!master)
            {
                logInfo("IOC", "MASTER", "Resetting node info of master for all components");
            }
            else
            {
                logInfo("IOC", "MASTER", "Resetting node master for all components to node [%d]", master);
            }
        }
        for(i = CL_IOC_MIN_COMP_PORT ; i < CL_IOC_MAX_COMPONENTS_PER_NODE ; i++)
        {
            if(resetAll)
            {
                gpClIocMasterSeg[i] = master;
            }
            else if(gpClIocMasterSeg[i] == compAddr.nodeAddress)
            {
                gpClIocMasterSeg[i] = master;
            }
        }
    }
    else if(gpClIocMasterSeg[compAddr.portId] == compAddr.nodeAddress)
    {
        gpClIocMasterSeg[compAddr.portId] = master;
        if(!master)
        {
            logInfo("IOC", "MASTER", "Resetting segment info of master for comp [%d].", compAddr.portId);
        }
        else
        {
            logInfo("IOC", "MASTER", "Resetting segment master for comp [%d] to node [%d]",
                      compAddr.portId, master);
        }
    }
    gClIocMasterSem->unlock();
}

void clIocMasterSegmentUpdate(ClIocPhysicalAddressT compAddr)
{
    clIocMasterSegmentSet(compAddr, 0);
}
