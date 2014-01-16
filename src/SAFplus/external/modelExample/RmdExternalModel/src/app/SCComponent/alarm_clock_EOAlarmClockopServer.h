
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

#ifndef _ALARM_CLOCK_EOALARMCLOCKOP_SERVER_H_
#define _ALARM_CLOCK_EOALARMCLOCKOP_SERVER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <clXdrApi.h>
#include <clIdlApi.h>
#include <ipi/clRmdIpi.h>
#include "../common/clientIDDefinitions.h"
#include "xdrAlarmReactionT.h"
#include "xdrAcTimeT.h"



ClRcT GetTime_4_0_0(CL_OUT acTimeT_4_0_0*  current);

ClRcT GetTimeResponseSend_4_0_0(CL_IN ClIdlHandleT idlHdl,CL_IN ClRcT retCode,CL_OUT  acTimeT_4_0_0  current);



#ifdef __cplusplus
}
#endif
#endif /*_ALARM_CLOCK_EOALARMCLOCKOP_SERVER_H_*/
