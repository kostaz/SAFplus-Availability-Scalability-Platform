/* 
 * File SafplusLog.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SAFPLUSLOG_HXX_
#define SAFPLUSLOG_HXX_

#include "MgtFactory.hxx"
#include "SAFplusLogCommon.hxx"
#include "clMgtContainer.hxx"
#include "ServerConfig.hxx"
#include <vector>
#include "StreamConfig.hxx"

namespace SAFplusLog
  {

    class SafplusLog : public SAFplus::MgtContainer {

        /* Apply MGT object factory */
        MGT_REGISTER(SafplusLog);

    public:
        SAFplusLog::ServerConfig serverConfig;
        SAFplusLog::StreamConfig streamConfig;

    public:
        SafplusLog();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusLog/safplusLog/serverConfig
         */
        SAFplusLog::ServerConfig* getServerConfig();

        /*
         * XPATH: /SAFplusLog/safplusLog/serverConfig
         */
        void addServerConfig(SAFplusLog::ServerConfig *serverConfigValue);

        /*
         * XPATH: /SAFplusLog/safplusLog/streamConfig
         */
        SAFplusLog::StreamConfig* getStreamConfig();

        /*
         * XPATH: /SAFplusLog/safplusLog/streamConfig
         */
        void addStreamConfig(SAFplusLog::StreamConfig *streamConfigValue);
        ~SafplusLog();

    };
}
/* namespace ::SAFplusLog */
#endif /* SAFPLUSLOG_HXX_ */
