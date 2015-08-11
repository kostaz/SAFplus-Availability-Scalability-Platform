/* 
 * File ProcessStats.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef PROCESSSTATS_HXX_
#define PROCESSSTATS_HXX_
#include "SAFplusTypesCommon.hxx"

#include "clMgtContainer.hxx"
#include <vector>
#include "clTransaction.hxx"
#include "ProcessState.hxx"
#include "clMgtProv.hxx"

namespace SAFplusTypes
  {

    class ProcessStats : public SAFplus::MgtContainer {
    public:
        SAFplus::MgtProv<SAFplusTypes::ProcessState> processState;
        SAFplus::MgtHistoryStat<int> failures;
        SAFplus::MgtHistoryStat<float> cpuUtilization;
        SAFplus::MgtHistoryStat<float> memUtilization;
        SAFplus::MgtHistoryStat<int> pageFaults;
        SAFplus::MgtHistoryStat<int> numThreads;
        SAFplus::MgtHistoryStat<int> residentMem;

    public:
        ProcessStats();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/processState
         */
        SAFplusTypes::ProcessState getProcessState();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/processState
         */
        void setProcessState(SAFplusTypes::ProcessState &processStateValue, SAFplus::Transaction &txn=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusTypes/ProcessStats/failures
         */
        SAFplus::MgtHistoryStat<int>* getFailures();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/failures
         */
        void addFailures(SAFplus::MgtHistoryStat<int> *failuresValue);

        /*
         * XPATH: /SAFplusTypes/ProcessStats/cpuUtilization
         */
        SAFplus::MgtHistoryStat<float>* getCpuUtilization();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/cpuUtilization
         */
        void addCpuUtilization(SAFplus::MgtHistoryStat<float> *cpuUtilizationValue);

        /*
         * XPATH: /SAFplusTypes/ProcessStats/memUtilization
         */
        SAFplus::MgtHistoryStat<float>* getMemUtilization();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/memUtilization
         */
        void addMemUtilization(SAFplus::MgtHistoryStat<float> *memUtilizationValue);

        /*
         * XPATH: /SAFplusTypes/ProcessStats/pageFaults
         */
        SAFplus::MgtHistoryStat<int>* getPageFaults();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/pageFaults
         */
        void addPageFaults(SAFplus::MgtHistoryStat<int> *pageFaultsValue);

        /*
         * XPATH: /SAFplusTypes/ProcessStats/numThreads
         */
        SAFplus::MgtHistoryStat<int>* getNumThreads();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/numThreads
         */
        void addNumThreads(SAFplus::MgtHistoryStat<int> *numThreadsValue);

        /*
         * XPATH: /SAFplusTypes/ProcessStats/residentMem
         */
        SAFplus::MgtHistoryStat<int>* getResidentMem();

        /*
         * XPATH: /SAFplusTypes/ProcessStats/residentMem
         */
        void addResidentMem(SAFplus::MgtHistoryStat<int> *residentMemValue);
        ~ProcessStats();

    };
}
/* namespace SAFplusTypes */
#endif /* PROCESSSTATS_HXX_ */
