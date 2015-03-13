/* 
 * File NumServiceGroups.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "MgtFactory.hxx"
#include "IntStatistic.hxx"
#include "NumServiceGroups.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(NumServiceGroups, /SAFplusAmf/Application/numServiceGroups)

    NumServiceGroups::NumServiceGroups()
    {
        this->config = false;
        this->tag.assign("numServiceGroups");
    };

    std::vector<std::string>* NumServiceGroups::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    NumServiceGroups::~NumServiceGroups()
    {
    };

}
/* namespace SAFplusAmf */
