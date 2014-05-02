/* 
 * File EntityById.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ENTITYBYID_HXX_
#define ENTITYBYID_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include <string>

namespace SAFplusAmf
  {

    class EntityById : public SAFplus::ClMgtObject {

        /* Apply MGT object factory */
        MGT_REGISTER(EntityById);

    public:
        SAFplus::ClMgtProv<unsigned short int> id;
        SAFplus::ClMgtProv<std::string> entity;

    public:
        EntityById();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EntityById/id
         */
        unsigned short int getId();

        /*
         * XPATH: /SAFplusAmf/EntityById/id
         */
        void setId(unsigned short int idValue);

        /*
         * XPATH: /SAFplusAmf/EntityById/entity
         */
        std::string getEntity();

        /*
         * XPATH: /SAFplusAmf/EntityById/entity
         */
        void setEntity(std::string entityValue);
        ~EntityById();

    };
}
/* namespace SAFplusAmf */
#endif /* ENTITYBYID_HXX_ */
