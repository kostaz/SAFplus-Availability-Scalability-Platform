/* 
 * File ServiceGroup.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SERVICEGROUP_HXX_
#define SERVICEGROUP_HXX_
#include "SAFplusAmfCommon.hxx"

#include <string>
#include "clTransaction.hxx"
#include "ComponentRestart.hxx"
#include "MgtFactory.hxx"
#include "NumSpareServiceUnits.hxx"
#include "ServiceUnitRestart.hxx"
#include "AdministrativeState.hxx"
#include "clMgtIdentifier.hxx"
#include "ComponentRestart.hxx"
#include "NumIdleServiceUnits.hxx"
#include "clMgtProv.hxx"
#include "Application.hxx"
#include "ServiceInstance.hxx"
#include "clMgtIdentifierList.hxx"
#include "NumIdleServiceUnits.hxx"
#include "ServiceUnitRestart.hxx"
#include <vector>
#include "NumAssignedServiceUnits.hxx"
#include "NumSpareServiceUnits.hxx"
#include "NumAssignedServiceUnits.hxx"
#include "EntityId.hxx"
#include "ServiceUnit.hxx"

namespace SAFplusAmf
  {

    class ServiceGroup : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(ServiceGroup);

    public:

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::MgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * Automatically attempt to bring this entity back into a healthy state if its operational state becomes disabled.  A 'false' value will cause the system to wait for operator intervention (via the repair API) before attempting to restart this entity.
         */
        SAFplus::MgtProv<bool> autoRepair;

        /*
         * Match this service group as closely as possible to the preferred high availability configuration.  For example, if the preferred active comes online, 'fail-back' to it.  Another example is if a new work assignment is provisioned, the system could remove an existing standby assignment so the new active can be provisioned.
         */
        SAFplus::MgtProv<bool> autoAdjust;

        /*
         * The time between checks to see if adjustment is needed.
         */
        SAFplus::MgtProv<SaTimeT> autoAdjustInterval;

        /*
         * 
         */
        SAFplus::MgtProv<unsigned int> preferredNumActiveServiceUnits;

        /*
         * 
         */
        SAFplus::MgtProv<unsigned int> preferredNumStandbyServiceUnits;

        /*
         * An idle service unit is running but is not assigned active or standby.  This concept is functionally equivalent to the saAmfSGNumPrefInserviceSUs since Active+Standby+Idle = Inservice
         */
        SAFplus::MgtProv<unsigned int> preferredNumIdleServiceUnits;

        /*
         * The maximum number of active work assignments that can be placed on a single service unit (and therefore component/process) simultaneously.
         */
        SAFplus::MgtProv<unsigned int> maxActiveWorkAssignments;

        /*
         * The maximum number of standby work assignments that can be placed on a single service unit (and therefore component/process) simultaneously.
         */
        SAFplus::MgtProv<unsigned int> maxStandbyWorkAssignments;

        /*
         * Service Units in this Service Group
         */
        SAFplus::MgtIdentifierList<SAFplusAmf::ServiceUnit*> serviceUnits;

        /*
         * Service Instances (work) in this Service group
         */
        SAFplus::MgtIdentifierList<SAFplusAmf::ServiceInstance*> serviceInstances;
        SAFplus::MgtIdentifier<SAFplusAmf::Application*> application;

    public:
        ServiceGroup();
        ServiceGroup(std::string myNameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/autoRepair
         */
        bool getAutoRepair();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/autoRepair
         */
        void setAutoRepair(bool autoRepairValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/autoAdjust
         */
        bool getAutoAdjust();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/autoAdjust
         */
        void setAutoAdjust(bool autoAdjustValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/autoAdjustInterval
         */
        SaTimeT getAutoAdjustInterval();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/autoAdjustInterval
         */
        void setAutoAdjustInterval(SaTimeT autoAdjustIntervalValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/preferredNumActiveServiceUnits
         */
        unsigned int getPreferredNumActiveServiceUnits();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/preferredNumActiveServiceUnits
         */
        void setPreferredNumActiveServiceUnits(unsigned int preferredNumActiveServiceUnitsValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/preferredNumStandbyServiceUnits
         */
        unsigned int getPreferredNumStandbyServiceUnits();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/preferredNumStandbyServiceUnits
         */
        void setPreferredNumStandbyServiceUnits(unsigned int preferredNumStandbyServiceUnitsValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/preferredNumIdleServiceUnits
         */
        unsigned int getPreferredNumIdleServiceUnits();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/preferredNumIdleServiceUnits
         */
        void setPreferredNumIdleServiceUnits(unsigned int preferredNumIdleServiceUnitsValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/maxActiveWorkAssignments
         */
        unsigned int getMaxActiveWorkAssignments();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/maxActiveWorkAssignments
         */
        void setMaxActiveWorkAssignments(unsigned int maxActiveWorkAssignmentsValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/maxStandbyWorkAssignments
         */
        unsigned int getMaxStandbyWorkAssignments();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/maxStandbyWorkAssignments
         */
        void setMaxStandbyWorkAssignments(unsigned int maxStandbyWorkAssignmentsValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/serviceUnits
         */
        std::vector<SAFplusAmf::ServiceUnit*> getServiceUnits();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/serviceUnits
         */
        void setServiceUnits(SAFplusAmf::ServiceUnit* serviceUnitsValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/serviceInstances
         */
        std::vector<SAFplusAmf::ServiceInstance*> getServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/serviceInstances
         */
        void setServiceInstances(SAFplusAmf::ServiceInstance* serviceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/application
         */
        SAFplusAmf::Application* getApplication();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/application
         */
        void setApplication(SAFplusAmf::Application* applicationValue, SAFplus::Transaction &t=SAFplus::NO_TXN);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/componentRestart
         */
        SAFplusAmf::ComponentRestart* getComponentRestart();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/componentRestart
         */
        void addComponentRestart(SAFplusAmf::ComponentRestart *componentRestartValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/serviceUnitRestart
         */
        SAFplusAmf::ServiceUnitRestart* getServiceUnitRestart();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/serviceUnitRestart
         */
        void addServiceUnitRestart(SAFplusAmf::ServiceUnitRestart *serviceUnitRestartValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/numAssignedServiceUnits
         */
        SAFplusAmf::NumAssignedServiceUnits* getNumAssignedServiceUnits();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/numAssignedServiceUnits
         */
        void addNumAssignedServiceUnits(SAFplusAmf::NumAssignedServiceUnits *numAssignedServiceUnitsValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/numIdleServiceUnits
         */
        SAFplusAmf::NumIdleServiceUnits* getNumIdleServiceUnits();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/numIdleServiceUnits
         */
        void addNumIdleServiceUnits(SAFplusAmf::NumIdleServiceUnits *numIdleServiceUnitsValue);

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/numSpareServiceUnits
         */
        SAFplusAmf::NumSpareServiceUnits* getNumSpareServiceUnits();

        /*
         * XPATH: /SAFplusAmf/ServiceGroup/numSpareServiceUnits
         */
        void addNumSpareServiceUnits(SAFplusAmf::NumSpareServiceUnits *numSpareServiceUnitsValue);
        ~ServiceGroup();

    };
}
/* namespace SAFplusAmf */
#endif /* SERVICEGROUP_HXX_ */
