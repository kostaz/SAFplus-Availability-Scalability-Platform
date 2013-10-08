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

/*********************************************************************
* ModuleName  : idl
* File        : clIdlOpen.c
*********************************************************************/
/*********************************************************************
* Description : This file contains IDL related open functions.
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE.
*     
*********************************************************************/
#include <clCommonErrors.h>
#include <clOsalApi.h>
#include <clDebugApi.h>
#include <clXdrApi.h>
/*********************************************************************
 * Description: This function is used for freeing the server side
 *              memory allocated by server when called from IDL. The
 *              memory free mechanism used should be the same as used
 *              while allocating the memory. By default, clHeapFree is
 *              used, which should be replaced by user specific "free"
 *              function.
*********************************************************************/

ClRcT clIdlFree(void *pData)
{
    CL_DEBUG_PRINT(CL_LOG_SEV_WARNING,("Warning! clIdlFree in file %s "
        "uses clHeapFree for freeing memory allocated by server "
        "function.\n", __FILE__));
    clHeapFree(pData);
    return CL_OK;    
}
