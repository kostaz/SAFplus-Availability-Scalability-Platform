/* 
 * File AdministrativeState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef ADMINISTRATIVESTATE_HXX_
#define ADMINISTRATIVESTATE_HXX_

#include <iostream>

namespace SAFplusAmf {

    class AdministrativeState {
    public:
        int Value;

    public:
         AdministrativeState();
        int getValue();
        void setValue(int value);
        SAFplusAmf::AdministrativeState& operator=(SAFplusAmf::AdministrativeState& AdministrativeState);
        friend std::ostream& operator<<(std::ostream& os, const SAFplusAmf::AdministrativeState& AdministrativeState);
        friend std::istream& operator>>(std::istream& in, SAFplusAmf::AdministrativeState& AdministrativeState);
         ~AdministrativeState();

    };
}
/* namespace SAFplusAmf */
#endif /* ADMINISTRATIVESTATE_HXX_ */