/* 
 * File EntityOperState.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include <iostream>
#include "EntityOperState.hxx"


namespace ENTITYSTATETCMIB {

     EntityOperState::EntityOperState() {
    };

    int EntityOperState::getValue() {
        return this->Value;
    };

    void EntityOperState::setValue(int value) {
        this->Value = value;
    };

    ENTITYSTATETCMIB::EntityOperState& EntityOperState::operator=(ENTITYSTATETCMIB::EntityOperState& EntityOperState) {
        Value = EntityOperState.Value;
        return *this;
    };

     EntityOperState::~EntityOperState() {
    };

    std::ostream& operator<<(std::ostream& os, const ENTITYSTATETCMIB::EntityOperState& EntityOperState) {
        return os << EntityOperState.Value;
    };

    std::istream& operator>>(std::istream& in, ENTITYSTATETCMIB::EntityOperState& EntityOperState) {
        return in >> EntityOperState.Value;
    };

}
/* namespace ENTITYSTATETCMIB */