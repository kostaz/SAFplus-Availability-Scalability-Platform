/* 
 * File HighAvailabilityReadinessState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef HIGHAVAILABILITYREADINESSSTATE_HXX_
#define HIGHAVAILABILITYREADINESSSTATE_HXX_

#include <iostream>

namespace SAFplusAmf {

    class HighAvailabilityReadinessState {
    public:
        int Value;

    public:
         HighAvailabilityReadinessState();
        int getValue();
        void setValue(int value);
        SAFplusAmf::HighAvailabilityReadinessState& operator=(SAFplusAmf::HighAvailabilityReadinessState& HighAvailabilityReadinessState);
        friend std::ostream& operator<<(std::ostream& os, const SAFplusAmf::HighAvailabilityReadinessState& HighAvailabilityReadinessState);
        friend std::istream& operator>>(std::istream& in, SAFplusAmf::HighAvailabilityReadinessState& HighAvailabilityReadinessState);
         ~HighAvailabilityReadinessState();

    };
}
/* namespace SAFplusAmf */
#endif /* HIGHAVAILABILITYREADINESSSTATE_HXX_ */