/* 
 * File Cluster.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef CLUSTER_HXX_
#define CLUSTER_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "SaTimeT.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include <string>

namespace SAFplusAmf
  {

    class Cluster : public SAFplus::ClMgtObject {

        /* Apply MGT object factory */
        MGT_REGISTER(Cluster);

    public:

        /*
         * Unique name of this entity
         */
        SAFplus::ClMgtProv<std::string> name;

        /*
         * Each SAFplus AMF entity gets a unique numerical identifier
         */
        SAFplus::ClMgtProv<unsigned short int> id;

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::ClMgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * When the cluster is first started, no work will be assigned until either ALL configured service units are instantiated or this time duration elapses.  By giving every node a chance to come up fully, this ensures that initial work assignments are as close as possible to preferred work assignments.
         */
        SAFplus::ClMgtProv<SAFplusTypes::SaTimeT> startupAssignmentDelay;

    public:
        Cluster();
        Cluster(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Cluster/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusAmf/Cluster/name
         */
        void setName(std::string nameValue);

        /*
         * XPATH: /SAFplusAmf/Cluster/id
         */
        unsigned short int getId();

        /*
         * XPATH: /SAFplusAmf/Cluster/id
         */
        void setId(unsigned short int idValue);

        /*
         * XPATH: /SAFplusAmf/Cluster/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/Cluster/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue);

        /*
         * XPATH: /SAFplusAmf/Cluster/startupAssignmentDelay
         */
        SAFplusTypes::SaTimeT getStartupAssignmentDelay();

        /*
         * XPATH: /SAFplusAmf/Cluster/startupAssignmentDelay
         */
        void setStartupAssignmentDelay(SAFplusTypes::SaTimeT startupAssignmentDelayValue);
        ~Cluster();

    };
}
/* namespace SAFplusAmf */
#endif /* CLUSTER_HXX_ */
