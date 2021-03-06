/* 
 * File EntityOperState.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ENTITYOPERSTATE_HXX_
#define ENTITYOPERSTATE_HXX_
#include "ENTITYSTATETCMIBCommon.hxx"

#include "MgtEnumType.hxx"
#include <iostream>

namespace ENTITYSTATETCMIB
  {

    enum class EntityOperState
      {
        unknown=1, disabled=2, enabled=3, testing=4
      };
    std::ostream& operator<<(std::ostream& os, const EntityOperState& e);
    std::istream& operator>>(std::istream& is, EntityOperState& e);
    const char* c_str(const EntityOperState& e);

    /*
     * This is the class that will handle the conversion for us.
     */
    class EntityOperStateManager : public SAFplus::MgtEnumType<EntityOperStateManager, EntityOperState> {
        EntityOperStateManager();  // private to prevent instantiation
    public:
        static const map_t en2str_map;  // This is the lookup table.
    };
}
/* namespace ::ENTITYSTATETCMIB */
#endif /* ENTITYOPERSTATE_HXX_ */
