/* 
 * File Node.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef NODE_HXX_
#define NODE_HXX_
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "clMgtIdentifierList.hxx"
#include "clMgtList.hxx"
#include "ServiceUnitFailureEscalationPolicy.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "ServiceUnitFailureEscalationPolicy.hxx"
#include "EntityId.hxx"
#include "ServiceUnit.hxx"

namespace SAFplusAmf
  {

    class Node : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(Node);

    public:

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::MgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * True is enabled, False is disabled.  To move from False to True a 'repair' action must occur.
         */
        SAFplus::MgtProv<bool> operState;

        /*
         * Automatically attempt to bring this entity back into a healthy state if its operational state becomes disabled.
         */
        SAFplus::MgtProv<bool> autoRepair;

        /*
         * If a component fails to instantiate on this node after potentially multiple attempts (as configured in the component) the AMF will reboot this node if this field is true
         */
        SAFplus::MgtProv<bool> failFastOnInstantiationFailure;

        /*
         * If a component's cleanup script fails on this node after potentially multiple attempts (as configured in the component) the AMF will reboot this node if this field is true
         */
        SAFplus::MgtProv<bool> failFastOnCleanupFailure;

        /*
         * Service Units configured to be instantiated on this node.
         */
        SAFplus::MgtIdentifierList<SAFplusAmf::ServiceUnit*> serviceUnits;

        /*
         * An abstract definition of the amount of work this node can handle.  Nodes can be assigned capacities for arbitrarily chosen strings (MEM or CPU, for example).  Service Instances can be assigned 'weights' and the sum of the weights of service instances assigned active or standby on this node cannot exceed these values.
         */
        SAFplus::MgtList<std::string> capacityList;

    public:
        Node();
        Node(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Node/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/Node/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Node/operState
         */
        bool getOperState();

        /*
         * XPATH: /SAFplusAmf/Node/operState
         */
        void setOperState(bool operStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Node/autoRepair
         */
        bool getAutoRepair();

        /*
         * XPATH: /SAFplusAmf/Node/autoRepair
         */
        void setAutoRepair(bool autoRepairValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Node/failFastOnInstantiationFailure
         */
        bool getFailFastOnInstantiationFailure();

        /*
         * XPATH: /SAFplusAmf/Node/failFastOnInstantiationFailure
         */
        void setFailFastOnInstantiationFailure(bool failFastOnInstantiationFailureValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Node/failFastOnCleanupFailure
         */
        bool getFailFastOnCleanupFailure();

        /*
         * XPATH: /SAFplusAmf/Node/failFastOnCleanupFailure
         */
        void setFailFastOnCleanupFailure(bool failFastOnCleanupFailureValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnits
         */
        std::vector<SAFplusAmf::ServiceUnit*> getServiceUnits();

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnits
         */
        void setServiceUnits(SAFplusAmf::ServiceUnit* serviceUnitsValue);

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy
         */
        SAFplusAmf::ServiceUnitFailureEscalationPolicy* getServiceUnitFailureEscalationPolicy();

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy
         */
        void addServiceUnitFailureEscalationPolicy(SAFplusAmf::ServiceUnitFailureEscalationPolicy *serviceUnitFailureEscalationPolicyValue);
        ~Node();

    };
}
/* namespace SAFplusAmf */
#endif /* NODE_HXX_ */