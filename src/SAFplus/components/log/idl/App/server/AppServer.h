/*********************************************************************
* File: 
*********************************************************************/
/*********************************************************************
* Description : This file contains the declartions for server stub
*               routines
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _APP_SERVER_H_
#define _APP_SERVER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <clXdrApi.h>
#include <clIdlApi.h>
#include <ipi/clRmdIpi.h>
#include "../clientIDDefinitions.h"
#include "xdrClLogFilterT.h"



ClRcT clAppIdlSyncDefer(ClIdlHandleT *pIdlHdl);
        
ClRcT clAppClientInstall(void);

ClRcT clAppClientUninstall(void);

extern ClRcT clLogClientFilterSetNotifyServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inmSgHdl , ClBufferHandleT outMsgHdl);
extern ClRcT clLogClntFileHdlrDataReceiveServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inmSgHdl , ClBufferHandleT outMsgHdl);


#ifdef __cplusplus
}
#endif
#endif /*_APP_SERVER_H_*/