/* 
 * File Timestamp.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef TIMESTAMP_HXX_
#define TIMESTAMP_HXX_
#include "ietfYangTypesCommon.hxx"

#include <iostream>

namespace ietfYangTypes
  {

    class Timestamp {
    public:
        unsigned int Value;

    public:
        Timestamp();
        unsigned int getValue();
        void setValue(unsigned int value);
        ietfYangTypes::Timestamp& operator=(const ietfYangTypes::Timestamp &timestamp);
        friend std::ostream& operator<<(std::ostream &os, const ietfYangTypes::Timestamp &timestamp);
        friend std::istream& operator>>(std::istream &is, ietfYangTypes::Timestamp &timestamp);
        ~Timestamp();

    };
}
/* namespace ietfYangTypes */
#endif /* TIMESTAMP_HXX_ */
