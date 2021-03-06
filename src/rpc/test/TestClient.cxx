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

#include <iostream>
#include <sstream>
#include <clLogApi.hxx>
#include <clGlobals.hxx>
#include "clMsgApi.hxx"
#include "clRpcChannel.hxx"
#include "rpcTest.hxx"
#include "RpcWakeable.hxx"

using namespace std;
using namespace SAFplus;
using namespace google::protobuf;

//Auto scanning
#define IOC_PORT 66
#define IOC_PORT_SERVER 65

//ClBoolT gIsNodeRepresentative = CL_FALSE;

int main(void)
  {
    Handle msgDest;

    clMsgInitialize();

    logSeverity = LOG_SEV_MAX;

    msgDest = Handle::create(IOC_PORT_SERVER);

    char helloMsg[] = "Hello world ";

    SAFplus::Rpc::rpcTest::TestGetRpcMethodRequest request1;
    SAFplus::Rpc::rpcTest::TestGetRpcMethodResponse res1;

    request1.set_name("myNameRequest1");

    SAFplus::Rpc::rpcTest::TestGetRpcMethod2Request request2;
    SAFplus::Rpc::rpcTest::TestGetRpcMethod2Response res2;

    request2.set_name("myNameRequest2");

    SAFplus::Rpc::rpcTest::TestGetRpcMethod3Request request3;
    SAFplus::Rpc::rpcTest::TestGetRpcMethod3Response res3;

    request3.set_name("myNameRequest3");

    SAFplus::Rpc::rpcTest::WorkOperationRequest workOperationRequest;
    workOperationRequest.set_operation(1);

    SAFplus::Rpc::rpcTest::WorkOperationResponseRequest workOperationResponseRequest;
    workOperationResponseRequest.set_result(1);
    /*
     * ??? msgClient or safplusMsgServer
     */
    SafplusMsgServer msgClient(IOC_PORT);

    SAFplus::Rpc::RpcChannel * channel = new SAFplus::Rpc::RpcChannel(&msgClient, msgDest);
    channel->setMsgType(100, 101);

    SAFplus::Rpc::rpcTest::rpcTest *service = new SAFplus::Rpc::rpcTest::rpcTest::Stub(channel);

    msgClient.Start();

    //Test RPC
    //Loop forever
    while (1)
      {
        Rpc::RpcWakeable wakeable1(1);
        Rpc::RpcWakeable wakeable2(2);
        Rpc::RpcWakeable wakeable3(3);

        service->testGetRpcMethod(INVALID_HDL, &request1, &res1, wakeable1);
        service->testGetRpcMethod2(INVALID_HDL, &request2, &res2, wakeable2);
        service->testGetRpcMethod3(INVALID_HDL, &request3, &res3, wakeable3);
        service->workOperation(INVALID_HDL, &workOperationRequest);
        service->workOperationResponse(INVALID_HDL, &workOperationResponseRequest);

        sleep(1);
      }

  }
