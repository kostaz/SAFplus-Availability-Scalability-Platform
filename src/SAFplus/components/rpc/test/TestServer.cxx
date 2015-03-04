/*
 * Copyright (C) 2002-2014 OpenClovis Solutions Inc.  All Rights Reserved.
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
#include <clLogApi.hxx>
#include <clGlobals.hxx>
//#include <clIocProtocols.h>
#include "clSafplusMsgServer.hxx"
#include "clRpcChannel.hxx"
#include "rpcTest.hxx"

using namespace SAFplus;

#define IOC_PORT_SERVER 65

//ClUint32T clAspLocalId = 0x1;
//ClBoolT gIsNodeRepresentative = CL_TRUE;

int
main(void)
{
    SAFplus::ASP_NODEADDR = 0x1;

    safplusInitialize(SAFplus::LibDep::LOG | SAFplus::LibDep::UTILS | SAFplus::LibDep::OSAL | SAFplus::LibDep::HEAP | SAFplus::LibDep::TIMER | SAFplus::LibDep::BUFFER | SAFplus::LibDep::IOC);
    logEchoToFd = 1;  // echo logs to stdout for debugging
    logSeverity = LOG_SEV_MAX;

    //Msg server listening
    SAFplus::SafplusMsgServer safplusMsgServer(IOC_PORT_SERVER, 10, 10);

    // Handle RPC
    SAFplus::Rpc::RpcChannel *channel = new SAFplus::Rpc::RpcChannel(&safplusMsgServer, new SAFplus::Rpc::rpcTest::rpcTestImpl());
    channel->setMsgType(100, 101);

    safplusMsgServer.Start();

    // Loop forever
    while(1)
      {
        sleep(1);
      }

}

