/* 
 * File PresenceState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef PRESENCESTATE_HXX_
#define PRESENCESTATE_HXX_

#include <iostream>

namespace SAFplusAmf {

    class PresenceState {
    public:
        int Value;

    public:
         PresenceState();
        int getValue();
        void setValue(int value);
        SAFplusAmf::PresenceState& operator=(SAFplusAmf::PresenceState& PresenceState);
        friend std::ostream& operator<<(std::ostream& os, const SAFplusAmf::PresenceState& PresenceState);
        friend std::istream& operator>>(std::istream& in, SAFplusAmf::PresenceState& PresenceState);
         ~PresenceState();

    };
}
/* namespace SAFplusAmf */
#endif /* PRESENCESTATE_HXX_ */