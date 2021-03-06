/* 
 * File ProcessStats.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "clMgtContainer.hxx"
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "clMgtHistoryStat.hxx"
#include "ProcessState.hxx"
#include "SAFplusTypesCommon.hxx"
#include <vector>
#include "ProcessStats.hxx"


namespace SAFplusTypes
  {

    ProcessStats::ProcessStats(): SAFplus::MgtContainer("ProcessStats"), processState("processState")
    {
        this->addChildObject(&processState, "processState");
        this->addChildObject(&failures, "failures");
        this->addChildObject(&cpuUtilization, "cpuUtilization");
        this->addChildObject(&memUtilization, "memUtilization");
        this->addChildObject(&pageFaults, "pageFaults");
        this->addChildObject(&numThreads, "numThreads");
        this->addChildObject(&residentMem, "residentMem");
    };

    std::vector<std::string>* ProcessStats::getChildNames()
    {
        std::string childNames[] = { "failures", "cpuUtilization", "memUtilization", "pageFaults", "numThreads", "residentMem", "processState" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/processState
     */
    ::SAFplusTypes::ProcessState ProcessStats::getProcessState()
    {
        return this->processState.value;
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/processState
     */
    void ProcessStats::setProcessState(::SAFplusTypes::ProcessState &processStateValue, SAFplus::Transaction &txn)
    {
        this->processState.set(processStateValue,txn);
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/failures
     */
    SAFplus::MgtHistoryStat<int>* ProcessStats::getFailures()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("failures"));
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/failures
     */
    void ProcessStats::addFailures(SAFplus::MgtHistoryStat<int> *failuresValue)
    {
        this->addChildObject(failuresValue, "failures");
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/cpuUtilization
     */
    SAFplus::MgtHistoryStat<float>* ProcessStats::getCpuUtilization()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<float>*>(this->getChildObject("cpuUtilization"));
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/cpuUtilization
     */
    void ProcessStats::addCpuUtilization(SAFplus::MgtHistoryStat<float> *cpuUtilizationValue)
    {
        this->addChildObject(cpuUtilizationValue, "cpuUtilization");
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/memUtilization
     */
    SAFplus::MgtHistoryStat<float>* ProcessStats::getMemUtilization()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<float>*>(this->getChildObject("memUtilization"));
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/memUtilization
     */
    void ProcessStats::addMemUtilization(SAFplus::MgtHistoryStat<float> *memUtilizationValue)
    {
        this->addChildObject(memUtilizationValue, "memUtilization");
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/pageFaults
     */
    SAFplus::MgtHistoryStat<int>* ProcessStats::getPageFaults()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("pageFaults"));
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/pageFaults
     */
    void ProcessStats::addPageFaults(SAFplus::MgtHistoryStat<int> *pageFaultsValue)
    {
        this->addChildObject(pageFaultsValue, "pageFaults");
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/numThreads
     */
    SAFplus::MgtHistoryStat<int>* ProcessStats::getNumThreads()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("numThreads"));
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/numThreads
     */
    void ProcessStats::addNumThreads(SAFplus::MgtHistoryStat<int> *numThreadsValue)
    {
        this->addChildObject(numThreadsValue, "numThreads");
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/residentMem
     */
    SAFplus::MgtHistoryStat<int>* ProcessStats::getResidentMem()
    {
        return dynamic_cast<SAFplus::MgtHistoryStat<int>*>(this->getChildObject("residentMem"));
    };

    /*
     * XPATH: /SAFplusTypes/ProcessStats/residentMem
     */
    void ProcessStats::addResidentMem(SAFplus::MgtHistoryStat<int> *residentMemValue)
    {
        this->addChildObject(residentMemValue, "residentMem");
    };

    ProcessStats::~ProcessStats()
    {
    };

}
/* namespace ::SAFplusTypes */
