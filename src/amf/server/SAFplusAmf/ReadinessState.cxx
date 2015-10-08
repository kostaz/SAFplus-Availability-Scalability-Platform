/* 
 * File ReadinessState.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "SAFplusAmfCommon.hxx"
#include <iostream>
#include "MgtEnumType.hxx"
#include "ReadinessState.hxx"


namespace SAFplusAmf
  {

    /*
     * Provide an implementation of the en2str_map lookup table.
     */
    const ReadinessStateManager::map_t ReadinessStateManager::en2str_map = {
            pair_t(ReadinessState::outOfService, "outOfService"),
            pair_t(ReadinessState::inService, "inService"),
            pair_t(ReadinessState::stopping, "stopping")
    }; // uses c++11 initializer lists 

    const char* c_str(const ::SAFplusAmf::ReadinessState &readinessState)
    {
        return ReadinessStateManager::c_str(readinessState);
    };

    std::ostream& operator<<(std::ostream &os, const ::SAFplusAmf::ReadinessState &readinessState)
    {
        return os << ReadinessStateManager::toString(readinessState);
    };

    std::istream& operator>>(std::istream &is, ::SAFplusAmf::ReadinessState &readinessState)
    {
        std::string buf;
        is >> buf;
        readinessState = ReadinessStateManager::toEnum(buf);
        return is;
    };

}
/* namespace ::SAFplusAmf */
