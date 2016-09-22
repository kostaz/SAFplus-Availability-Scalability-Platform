/* 
 * File SAFplusLogModule.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "SafplusLog.hxx"
#include "MgtFactory.hxx"
#include "SAFplusLogCommon.hxx"
#include "clMgtModule.hxx"
#include <vector>
#include "SAFplusLogModule.hxx"


namespace SAFplusLog
  {

    SAFplusLogModule::SAFplusLogModule(): SAFplus::MgtModule("SAFplusLog")
    {
        this->addChildObject(&safplusLog, "safplusLog");
    };

    std::vector<std::string>* SAFplusLogModule::getChildNames()
    {
        std::string childNames[] = { "safplusLog" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    SAFplusLogModule::~SAFplusLogModule()
    {
    };

}
/* namespace ::SAFplusLog */