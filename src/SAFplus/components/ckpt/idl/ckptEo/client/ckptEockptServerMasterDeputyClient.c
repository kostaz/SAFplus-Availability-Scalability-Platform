
/*********************************************************************
* ModuleName  : idl
*********************************************************************/
/*********************************************************************
* Description :ClientSide Stub routines
*
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*
*********************************************************************/

#include <netinet/in.h>
#include <string.h>
#include <clBufferApi.h>
#include <clRmdApi.h>
#include <clIdlApi.h>
#include <clEoApi.h>
#include <clXdrApi.h>
#include <clHandleApi.h>
#include "ckptEockptServerMasterDeputyClient.h"
extern ClIdlClntT gIdlClnt;


ClRcT clCkptDeputyMasterInfoSyncupClientSync_4_0_0(CL_IN ClIdlHandleT handle, CL_INOUT ClVersionT* pVersion, CL_OUT ClUint32T* numOfCkpts, CL_OUT CkptXlationDBEntryT_4_0_0** pXlationInfo, CL_OUT CkptMasterDBInfoIDLT_4_0_0* pMasterInfo, CL_OUT ClUint32T* mastHdlCount, CL_OUT CkptMasterDBEntryIDLT_4_0_0** pMasterDBInfo, CL_OUT ClUint32T* peerCount, CL_OUT CkptPeerListInfoT_4_0_0** pPeerListInfo, CL_OUT ClUint32T* clientHdlCount, CL_OUT CkptMasterDBClientInfoT_4_0_0** pClientDBInfo)
{
    ClRcT rc = CL_OK;
    ClVersionT funcVer = {4, 0, 0};
    ClUint32T funcNo = CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 18);
    ClBufferHandleT inMsgHdl = 0;
    ClBufferHandleT outMsgHdl = 0;
    ClIocAddressT address = {{0}};
    ClIdlHandleObjT* pHandleObj = NULL;
    ClUint32T tempFlags = 0;

    rc = clHandleCheckout(gIdlClnt.idlDbHdl,handle,(void **)&pHandleObj);
    if( rc != CL_OK )
    {
        return rc ;
    }
    if (CL_IDL_ADDRESSTYPE_IOC == pHandleObj->address.addressType)
    {
        address = pHandleObj->address.address.iocAddress;
    }
    else if (CL_IDL_ADDRESSTYPE_NAME == pHandleObj->address.addressType)
    {
        rc = clNameToObjectReferenceGet(&(pHandleObj->address.address.nameAddress.name),
                                        pHandleObj->address.address.nameAddress.attrCount,
                                        pHandleObj->address.address.nameAddress.attr,
                                        pHandleObj->address.address.nameAddress.contextCookie,
                                        (ClUint64T*)&address);
        if (CL_OK != rc)
        {
            return rc;
        }
    }
    else
    {
        return CL_IDL_RC(CL_ERR_INVALID_PARAMETER);
    }

    rc = clBufferCreate(&inMsgHdl);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClVersionT(pVersion, inMsgHdl, 1);
    if (CL_OK != rc)
    {
        return rc;
    }


    rc = clBufferCreate(&outMsgHdl);
    if (CL_OK != rc)
    {
        return rc;
    }

    tempFlags |= pHandleObj->flags |
                 (CL_RMD_CALL_NON_PERSISTENT | CL_RMD_CALL_NEED_REPLY);
    tempFlags &= ~CL_RMD_CALL_ASYNC;

    rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, outMsgHdl, tempFlags, &(pHandleObj->options), NULL);
    if(CL_OK != rc)
    {
        clBufferDelete(&outMsgHdl);
    return rc;
    }


    rc = clXdrUnmarshallClVersionT( outMsgHdl, pVersion);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClUint32T( outMsgHdl, numOfCkpts);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallCkptMasterDBInfoIDLT_4_0_0( outMsgHdl, pMasterInfo);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClUint32T( outMsgHdl, mastHdlCount);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClUint32T( outMsgHdl, peerCount);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClUint32T( outMsgHdl, clientHdlCount);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallPtrCkptXlationDBEntryT_4_0_0( outMsgHdl, (void **)pXlationInfo, *numOfCkpts);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallPtrCkptMasterDBEntryIDLT_4_0_0( outMsgHdl, (void **)pMasterDBInfo, *mastHdlCount);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallPtrCkptPeerListInfoT_4_0_0( outMsgHdl, (void **)pPeerListInfo, *peerCount);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallPtrCkptMasterDBClientInfoT_4_0_0( outMsgHdl, (void **)pClientDBInfo, *clientHdlCount);
    if (CL_OK != rc)
    {
        return rc;
    }

    clBufferDelete(&outMsgHdl);
    
    rc = clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;
}


static void clCkptDeputyMasterInfoSyncupAsyncCallback_4_0_0(ClRcT rc, void *pIdlCookie, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlCookieT* pCookie = (ClIdlCookieT*)pIdlCookie;
    ClRcT retVal = CL_OK;
    ClVersionT  pVersion;
    ClUint32T  numOfCkpts;
    CkptXlationDBEntryT_4_0_0* pXlationInfo;
    CkptMasterDBInfoIDLT_4_0_0  pMasterInfo;
    ClUint32T  mastHdlCount;
    CkptMasterDBEntryIDLT_4_0_0* pMasterDBInfo;
    ClUint32T  peerCount;
    CkptPeerListInfoT_4_0_0* pPeerListInfo;
    ClUint32T  clientHdlCount;
    CkptMasterDBClientInfoT_4_0_0* pClientDBInfo;

    memset(&(pVersion), 0, sizeof(ClVersionT));
    memset(&(numOfCkpts), 0, sizeof(ClUint32T));
    memset(&(pXlationInfo), 0, sizeof(CkptXlationDBEntryT_4_0_0*));
    memset(&(pMasterInfo), 0, sizeof(CkptMasterDBInfoIDLT_4_0_0));
    memset(&(mastHdlCount), 0, sizeof(ClUint32T));
    memset(&(pMasterDBInfo), 0, sizeof(CkptMasterDBEntryIDLT_4_0_0*));
    memset(&(peerCount), 0, sizeof(ClUint32T));
    memset(&(pPeerListInfo), 0, sizeof(CkptPeerListInfoT_4_0_0*));
    memset(&(clientHdlCount), 0, sizeof(ClUint32T));
    memset(&(pClientDBInfo), 0, sizeof(CkptMasterDBClientInfoT_4_0_0*));


    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallClVersionT(outMsgHdl, &(pVersion));
        if (CL_OK != retVal)
        {
            goto L0;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallClUint32T(outMsgHdl, &(numOfCkpts));
        if (CL_OK != retVal)
        {
            goto L1;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallCkptMasterDBInfoIDLT_4_0_0(outMsgHdl, &(pMasterInfo));
        if (CL_OK != retVal)
        {
            goto L2;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallClUint32T(outMsgHdl, &(mastHdlCount));
        if (CL_OK != retVal)
        {
            goto L3;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallClUint32T(outMsgHdl, &(peerCount));
        if (CL_OK != retVal)
        {
            goto L4;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallClUint32T(outMsgHdl, &(clientHdlCount));
        if (CL_OK != retVal)
        {
            goto L5;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallPtrCkptXlationDBEntryT_4_0_0(outMsgHdl, (void**)&(pXlationInfo), numOfCkpts);
        if (CL_OK != retVal)
        {
            goto L6;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallPtrCkptMasterDBEntryIDLT_4_0_0(outMsgHdl, (void**)&(pMasterDBInfo), mastHdlCount);
        if (CL_OK != retVal)
        {
            goto L7;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallPtrCkptPeerListInfoT_4_0_0(outMsgHdl, (void**)&(pPeerListInfo), peerCount);
        if (CL_OK != retVal)
        {
            goto L8;
        }
    }

    if (CL_OK == rc)
    {
        retVal = clXdrUnmarshallPtrCkptMasterDBClientInfoT_4_0_0(outMsgHdl, (void**)&(pClientDBInfo), clientHdlCount);
        if (CL_OK != retVal)
        {
            goto L9;
        }
    }

    if (rc != CL_OK)
    {
        retVal = rc;
    }

    ((CkptEoClCkptDeputyMasterInfoSyncupAsyncCallbackT_4_0_0)(pCookie->actualCallback))(pCookie->handle, &(pVersion), &(numOfCkpts), &pXlationInfo, &(pMasterInfo), &(mastHdlCount), &pMasterDBInfo, &(peerCount), &pPeerListInfo, &(clientHdlCount), &pClientDBInfo, retVal, pCookie->pCookie);
    goto L10;

L10: 
L9: 
L8: 
L7: 
L6: 
L5: 
L4: 
L3: 
L2: 
L1: 

L0:  clHeapFree(pCookie);
     clBufferDelete(&outMsgHdl);
     return;
}


ClRcT clCkptDeputyMasterInfoSyncupClientAsync_4_0_0(CL_IN ClIdlHandleT handle, CL_INOUT ClVersionT* pVersion, CL_OUT ClUint32T* numOfCkpts, CL_OUT CkptXlationDBEntryT_4_0_0** pXlationInfo, CL_OUT CkptMasterDBInfoIDLT_4_0_0* pMasterInfo, CL_OUT ClUint32T* mastHdlCount, CL_OUT CkptMasterDBEntryIDLT_4_0_0** pMasterDBInfo, CL_OUT ClUint32T* peerCount, CL_OUT CkptPeerListInfoT_4_0_0** pPeerListInfo, CL_OUT ClUint32T* clientHdlCount, CL_OUT CkptMasterDBClientInfoT_4_0_0** pClientDBInfo,CL_IN CkptEoClCkptDeputyMasterInfoSyncupAsyncCallbackT_4_0_0 fpAsyncCallback, CL_IN void *cookie)
{
    ClRcT rc = CL_OK;
    ClVersionT funcVer = {4, 0, 0};
    ClUint32T funcNo = CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 18);
    ClBufferHandleT inMsgHdl = 0;
    ClBufferHandleT outMsgHdl = 0;
    ClIocAddressT address = {{0}};
    ClIdlHandleObjT* pHandleObj = NULL;
    ClRmdAsyncOptionsT asyncOptions;
    ClUint32T tempFlags = 0;
    ClIdlCookieT* pCookie = NULL;

    rc = clHandleCheckout(gIdlClnt.idlDbHdl,handle,(void **)&pHandleObj);
    if(rc != CL_OK)
    {
        return rc;
    }
    if (CL_IDL_ADDRESSTYPE_IOC == pHandleObj->address.addressType)
    {
        address = pHandleObj->address.address.iocAddress;
    }
    else if (CL_IDL_ADDRESSTYPE_NAME == pHandleObj->address.addressType)
    {
        rc = clNameToObjectReferenceGet(&(pHandleObj->address.address.nameAddress.name),
                                        pHandleObj->address.address.nameAddress.attrCount,
                                        pHandleObj->address.address.nameAddress.attr,
                                        pHandleObj->address.address.nameAddress.contextCookie,
                                        (ClUint64T*)&address);
        if (CL_OK != rc)
        {
            goto L;
        }
    }
    else
    {
        rc = CL_IDL_RC(CL_ERR_INVALID_PARAMETER);
        goto L;
    }

    rc = clBufferCreate(&inMsgHdl);
    if (CL_OK != rc)
    {
        goto L;
    }

    rc = clXdrMarshallClVersionT(pVersion, inMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L;
    }

    if(fpAsyncCallback != NULL)
    {
        

        pCookie = (ClIdlCookieT*) clHeapAllocate(sizeof(ClIdlCookieT));
        if (NULL == pCookie)
        {
            return CL_IDL_RC(CL_ERR_NO_MEMORY);
        }
        
        asyncOptions.pCookie = NULL;
        asyncOptions.fpCallback = NULL;
        
        rc = clBufferCreate(&outMsgHdl);
        if (CL_OK != rc)
        {
            goto L2;
        }

        tempFlags |= pHandleObj->flags |
                     (CL_RMD_CALL_ASYNC | CL_RMD_CALL_NON_PERSISTENT | CL_RMD_CALL_NEED_REPLY);
        
        pCookie->pCookie = cookie;
        pCookie->actualCallback = (void(*)())fpAsyncCallback;
        pCookie->handle = handle;
        asyncOptions.pCookie = pCookie;
        asyncOptions.fpCallback = clCkptDeputyMasterInfoSyncupAsyncCallback_4_0_0;

        rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, outMsgHdl, tempFlags, &(pHandleObj->options), &asyncOptions);
        if (CL_OK != rc)
        {
            goto LL;
         }
    }
    else
    {
        tempFlags |= pHandleObj->flags |
                         (CL_RMD_CALL_ASYNC | CL_RMD_CALL_NON_PERSISTENT);
        rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, 0, tempFlags, &(pHandleObj->options),NULL);
        if(CL_OK != rc)
        {
               goto L;
        }
    }
    
    
    clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;

LL: clBufferDelete(&outMsgHdl);
L2:  clHeapFree(pCookie);
L:
     clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;
}


ClRcT clCkptLeaderAddrUpdateClientSync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClUint32T masterAddr, CL_IN ClUint32T deputyAddr)
{
    ClRcT rc = CL_OK;
    ClVersionT funcVer = {4, 0, 0};
    ClUint32T funcNo = CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 19);
    ClBufferHandleT inMsgHdl = 0;
    ClBufferHandleT outMsgHdl = 0;
    ClIocAddressT address = {{0}};
    ClIdlHandleObjT* pHandleObj = NULL;
    ClUint32T tempFlags = 0;

    rc = clHandleCheckout(gIdlClnt.idlDbHdl,handle,(void **)&pHandleObj);
    if( rc != CL_OK )
    {
        return rc ;
    }
    if (CL_IDL_ADDRESSTYPE_IOC == pHandleObj->address.addressType)
    {
        address = pHandleObj->address.address.iocAddress;
    }
    else if (CL_IDL_ADDRESSTYPE_NAME == pHandleObj->address.addressType)
    {
        rc = clNameToObjectReferenceGet(&(pHandleObj->address.address.nameAddress.name),
                                        pHandleObj->address.address.nameAddress.attrCount,
                                        pHandleObj->address.address.nameAddress.attr,
                                        pHandleObj->address.address.nameAddress.contextCookie,
                                        (ClUint64T*)&address);
        if (CL_OK != rc)
        {
            return rc;
        }
    }
    else
    {
        return CL_IDL_RC(CL_ERR_INVALID_PARAMETER);
    }

    rc = clBufferCreate(&inMsgHdl);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint32T(&(masterAddr), inMsgHdl, 0);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint32T(&(deputyAddr), inMsgHdl, 0);
    if (CL_OK != rc)
    {
        return rc;
    }


    tempFlags |= pHandleObj->flags |
                 (CL_RMD_CALL_NON_PERSISTENT);
    tempFlags &= ~CL_RMD_CALL_ASYNC;

    rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, outMsgHdl, tempFlags, &(pHandleObj->options), NULL);
    if(CL_OK != rc)
    {
        return rc;
    }


    
    rc = clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;
}


static void clCkptLeaderAddrUpdateAsyncCallback_4_0_0(ClRcT rc, void *pIdlCookie, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlCookieT* pCookie = (ClIdlCookieT*)pIdlCookie;
    ClRcT retVal = CL_OK;
    ClUint32T  masterAddr;
    ClUint32T  deputyAddr;

    memset(&(masterAddr), 0, sizeof(ClUint32T));
    memset(&(deputyAddr), 0, sizeof(ClUint32T));


    retVal = clXdrUnmarshallClUint32T(inMsgHdl, &(masterAddr));
    if (CL_OK != retVal)
    {
        goto L0;
    }

    retVal = clXdrUnmarshallClUint32T(inMsgHdl, &(deputyAddr));
    if (CL_OK != retVal)
    {
        goto L1;
    }

    if (rc != CL_OK)
    {
        retVal = rc;
    }

    ((CkptEoClCkptLeaderAddrUpdateAsyncCallbackT_4_0_0)(pCookie->actualCallback))(pCookie->handle, masterAddr, deputyAddr, retVal, pCookie->pCookie);
    goto L2;

L2: 
L1: 

L0:  clHeapFree(pCookie);
     clBufferDelete(&outMsgHdl);
     return;
}


ClRcT clCkptLeaderAddrUpdateClientAsync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClUint32T  masterAddr, CL_IN ClUint32T  deputyAddr,CL_IN CkptEoClCkptLeaderAddrUpdateAsyncCallbackT_4_0_0 fpAsyncCallback, CL_IN void *cookie)
{
    ClRcT rc = CL_OK;
    ClVersionT funcVer = {4, 0, 0};
    ClUint32T funcNo = CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 19);
    ClBufferHandleT inMsgHdl = 0;
    ClBufferHandleT outMsgHdl = 0;
    ClIocAddressT address = {{0}};
    ClIdlHandleObjT* pHandleObj = NULL;
    ClRmdAsyncOptionsT asyncOptions;
    ClUint32T tempFlags = 0;
    ClIdlCookieT* pCookie = NULL;

    rc = clHandleCheckout(gIdlClnt.idlDbHdl,handle,(void **)&pHandleObj);
    if(rc != CL_OK)
    {
        return rc;
    }
    if (CL_IDL_ADDRESSTYPE_IOC == pHandleObj->address.addressType)
    {
        address = pHandleObj->address.address.iocAddress;
    }
    else if (CL_IDL_ADDRESSTYPE_NAME == pHandleObj->address.addressType)
    {
        rc = clNameToObjectReferenceGet(&(pHandleObj->address.address.nameAddress.name),
                                        pHandleObj->address.address.nameAddress.attrCount,
                                        pHandleObj->address.address.nameAddress.attr,
                                        pHandleObj->address.address.nameAddress.contextCookie,
                                        (ClUint64T*)&address);
        if (CL_OK != rc)
        {
            goto L;
        }
    }
    else
    {
        rc = CL_IDL_RC(CL_ERR_INVALID_PARAMETER);
        goto L;
    }

    rc = clBufferCreate(&inMsgHdl);
    if (CL_OK != rc)
    {
        goto L;
    }

    rc = clXdrMarshallClUint32T(&(masterAddr), inMsgHdl, 0);
    if (CL_OK != rc)
    {
        goto L;
    }

    rc = clXdrMarshallClUint32T(&(deputyAddr), inMsgHdl, 0);
    if (CL_OK != rc)
    {
        goto L;
    }

    if(fpAsyncCallback != NULL)
    {
        

        pCookie = (ClIdlCookieT*) clHeapAllocate(sizeof(ClIdlCookieT));
        if (NULL == pCookie)
        {
            return CL_IDL_RC(CL_ERR_NO_MEMORY);
        }
        
        asyncOptions.pCookie = NULL;
        asyncOptions.fpCallback = NULL;
        
        rc = clBufferCreate(&outMsgHdl);
        if (CL_OK != rc)
        {
            goto L2;
        }

        tempFlags |= pHandleObj->flags |
                     (CL_RMD_CALL_ASYNC | CL_RMD_CALL_NON_PERSISTENT | CL_RMD_CALL_NEED_REPLY);
        
        pCookie->pCookie = cookie;
        pCookie->actualCallback = (void(*)())fpAsyncCallback;
        pCookie->handle = handle;
        asyncOptions.pCookie = pCookie;
        asyncOptions.fpCallback = clCkptLeaderAddrUpdateAsyncCallback_4_0_0;

        rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, outMsgHdl, tempFlags, &(pHandleObj->options), &asyncOptions);
        if (CL_OK != rc)
        {
            goto LL;
         }
    }
    else
    {
        tempFlags |= pHandleObj->flags |
                         (CL_RMD_CALL_ASYNC | CL_RMD_CALL_NON_PERSISTENT);
        rc = clRmdWithMsgVer(address, &funcVer, funcNo, inMsgHdl, 0, tempFlags, &(pHandleObj->options),NULL);
        if(CL_OK != rc)
        {
               goto L;
        }
    }
    
    
    clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;

LL: clBufferDelete(&outMsgHdl);
L2:  clHeapFree(pCookie);
L:
     clHandleCheckin(gIdlClnt.idlDbHdl,handle);
    return rc;
}


