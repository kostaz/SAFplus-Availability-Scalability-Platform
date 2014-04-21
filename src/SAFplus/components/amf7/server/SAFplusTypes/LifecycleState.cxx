/* 
 * File LifecycleState.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <iostream>
#include "LifecycleState.hxx"


namespace SAFplusTypes {

     LifecycleState::LifecycleState() {
    };

    int LifecycleState::getValue() {
        return this->Value;
    };

    void LifecycleState::setValue(int value) {
        this->Value = value;
    };

    SAFplusTypes::LifecycleState& LifecycleState::operator=(SAFplusTypes::LifecycleState& lifecycleState) {
        Value = lifecycleState.Value;
        return *this;
    };

     LifecycleState::~LifecycleState() {
    };

    std::ostream& operator<<(std::ostream& os, const SAFplusTypes::LifecycleState& lifecycleState) {
        return os << lifecycleState.Value;
    };

    std::istream& operator>>(std::istream& in, SAFplusTypes::LifecycleState& lifecycleState) {
        return in >> lifecycleState.Value;
    };

}
/* namespace SAFplusTypes */