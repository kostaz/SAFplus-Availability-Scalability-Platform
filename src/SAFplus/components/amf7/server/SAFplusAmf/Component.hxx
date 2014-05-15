/* 
 * File Component.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef COMPONENT_HXX_
#define COMPONENT_HXX_
#include "SAFplusAmfCommon.hxx"

#include "RestartCount.hxx"
#include <string>
#include "HighAvailabilityReadinessState.hxx"
#include "Timeouts.hxx"
#include "StandbyAssignments.hxx"
#include "Instantiate.hxx"
#include "RestartCount.hxx"
#include "Terminate.hxx"
#include "Cleanup.hxx"
#include "MgtFactory.hxx"
#include "ActiveAssignments.hxx"
#include "CapabilityModel.hxx"
#include "Cleanup.hxx"
#include "Recovery.hxx"
#include "ReadinessState.hxx"
#include "Timeouts.hxx"
#include "Instantiate.hxx"
#include "clMgtProv.hxx"
#include "StandbyAssignments.hxx"
#include "Terminate.hxx"
#include <vector>
#include "ActiveAssignments.hxx"
#include "HighAvailabilityState.hxx"
#include "PresenceState.hxx"
#include "EntityId.hxx"
#include "ServiceUnit.hxx"
#include "clMgtProvList.hxx"

namespace SAFplusAmf
  {

    class Component : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(Component);

    public:
        SAFplus::MgtProv<SAFplusAmf::PresenceState> presence;

        /*
         * This is defined by the SA-Forum AMF specificaion but is read-only because it is an emergent property based on values in saAmfCompNumMaxActiveCSIs and saAmfCompNumMaxStandbyCSIs.
         */
        SAFplus::MgtProv<SAFplusAmf::CapabilityModel> capabilityModel;

        /*
         * Maximum number of active work assignments this component can handle.
         */
        SAFplus::MgtProv<unsigned int> maxActiveAssignments;

        /*
         * Maximum number of standby work assignments this component can handle.
         */
        SAFplus::MgtProv<unsigned int> maxStandbyAssignments;

        /*
         * Currently assigned work.
         */
        SAFplus::MgtProvList<std::string> assignedWork;

        /*
         * True is enabled, False is disabled.  To move from False to True a 'repair' action must occur.
         */
        SAFplus::MgtProv<bool> operState;
        SAFplus::MgtProv<SAFplusAmf::ReadinessState> readinessState;

        /*
         * This state field covers ALL work assignments...
         */
        SAFplus::MgtProv<SAFplusAmf::HighAvailabilityReadinessState> haReadinessState;
        SAFplus::MgtProv<SAFplusAmf::HighAvailabilityState> haState;

        /*
         * Compatible SA-Forum API version
         */
        SAFplus::MgtProv<std::string> safVersion;
        SAFplus::MgtProv<unsigned int> compCategory;

        /*
         * What software installation bundle does this component come from
         */
        SAFplus::MgtProv<std::string> swBundle;

        /*
         * List of environment variables in the form '<VARIABLE>=<VALUE>
<VARIABLE2>=<VALUE2>
' the form the environment in which this component should be started
         */
        SAFplus::MgtProvList<std::string> commandEnvironment;

        /*
         * How many times to attempt to instantiate this entity without delay.  If the number of instantiation attempts exceeds both this and the max delayed instantiations field, the fault will be elevated to the Service Unit level.
         */
        SAFplus::MgtProv<unsigned int> maxInstantInstantiations;

        /*
         * How many times to attempt to instantiate this entity after an initial delay.  If the number of instantiation attempts exceeds both this and the max instant instantiations field, the fault will be elevated to the Service Unit level.
         */
        SAFplus::MgtProv<unsigned int> maxDelayedInstantiations;

        /*
         * How long to delay between instantiation attempts
         */
        SAFplus::MgtProv<unsigned int> delayBetweenInstantiation;
        SAFplus::MgtProv<SAFplusAmf::ServiceUnit*> serviceUnit;
        SAFplus::MgtProv<SAFplusAmf::Recovery> recovery;

        /*
         * Set to true if this component can be restarted on failure, without this event registering as a fault
         */
        SAFplus::MgtProv<bool> restartable;

        /*
         * The component listed here is this component's proxy.
         */
        SAFplus::MgtProv<std::string> proxy;

        /*
         * This component is the proxy for the components listed here.
         */
        SAFplus::MgtProvList<std::string> proxied;

        /*
         * The process id of this component (if it is instantiated as a process), or 0
         */
        SAFplus::MgtProv<int> processId;

    public:
        Component();
        Component(std::string myNameValue);
        void toString(std::stringstream &xmlString);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Component/presence
         */
        SAFplusAmf::PresenceState getPresence();

        /*
         * XPATH: /SAFplusAmf/Component/presence
         */
        void setPresence(SAFplusAmf::PresenceState presenceValue);

        /*
         * XPATH: /SAFplusAmf/Component/capabilityModel
         */
        SAFplusAmf::CapabilityModel getCapabilityModel();

        /*
         * XPATH: /SAFplusAmf/Component/capabilityModel
         */
        void setCapabilityModel(SAFplusAmf::CapabilityModel capabilityModelValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxActiveAssignments
         */
        unsigned int getMaxActiveAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/maxActiveAssignments
         */
        void setMaxActiveAssignments(unsigned int maxActiveAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxStandbyAssignments
         */
        unsigned int getMaxStandbyAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/maxStandbyAssignments
         */
        void setMaxStandbyAssignments(unsigned int maxStandbyAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/assignedWork
         */
        std::vector<std::string> getAssignedWork();

        /*
         * XPATH: /SAFplusAmf/Component/assignedWork
         */
        void setAssignedWork(std::string assignedWorkValue);

        /*
         * XPATH: /SAFplusAmf/Component/operState
         */
        bool getOperState();

        /*
         * XPATH: /SAFplusAmf/Component/operState
         */
        void setOperState(bool operStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/readinessState
         */
        SAFplusAmf::ReadinessState getReadinessState();

        /*
         * XPATH: /SAFplusAmf/Component/readinessState
         */
        void setReadinessState(SAFplusAmf::ReadinessState readinessStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/haReadinessState
         */
        SAFplusAmf::HighAvailabilityReadinessState getHaReadinessState();

        /*
         * XPATH: /SAFplusAmf/Component/haReadinessState
         */
        void setHaReadinessState(SAFplusAmf::HighAvailabilityReadinessState haReadinessStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/haState
         */
        SAFplusAmf::HighAvailabilityState getHaState();

        /*
         * XPATH: /SAFplusAmf/Component/haState
         */
        void setHaState(SAFplusAmf::HighAvailabilityState haStateValue);

        /*
         * XPATH: /SAFplusAmf/Component/safVersion
         */
        std::string getSafVersion();

        /*
         * XPATH: /SAFplusAmf/Component/safVersion
         */
        void setSafVersion(std::string safVersionValue);

        /*
         * XPATH: /SAFplusAmf/Component/compCategory
         */
        unsigned int getCompCategory();

        /*
         * XPATH: /SAFplusAmf/Component/compCategory
         */
        void setCompCategory(unsigned int compCategoryValue);

        /*
         * XPATH: /SAFplusAmf/Component/swBundle
         */
        std::string getSwBundle();

        /*
         * XPATH: /SAFplusAmf/Component/swBundle
         */
        void setSwBundle(std::string swBundleValue);

        /*
         * XPATH: /SAFplusAmf/Component/commandEnvironment
         */
        std::vector<std::string> getCommandEnvironment();

        /*
         * XPATH: /SAFplusAmf/Component/commandEnvironment
         */
        void setCommandEnvironment(std::string commandEnvironmentValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxInstantInstantiations
         */
        unsigned int getMaxInstantInstantiations();

        /*
         * XPATH: /SAFplusAmf/Component/maxInstantInstantiations
         */
        void setMaxInstantInstantiations(unsigned int maxInstantInstantiationsValue);

        /*
         * XPATH: /SAFplusAmf/Component/maxDelayedInstantiations
         */
        unsigned int getMaxDelayedInstantiations();

        /*
         * XPATH: /SAFplusAmf/Component/maxDelayedInstantiations
         */
        void setMaxDelayedInstantiations(unsigned int maxDelayedInstantiationsValue);

        /*
         * XPATH: /SAFplusAmf/Component/delayBetweenInstantiation
         */
        unsigned int getDelayBetweenInstantiation();

        /*
         * XPATH: /SAFplusAmf/Component/delayBetweenInstantiation
         */
        void setDelayBetweenInstantiation(unsigned int delayBetweenInstantiationValue);

        /*
         * XPATH: /SAFplusAmf/Component/serviceUnit
         */
        SAFplusAmf::ServiceUnit* getServiceUnit();

        /*
         * XPATH: /SAFplusAmf/Component/serviceUnit
         */
        void setServiceUnit(SAFplusAmf::ServiceUnit* serviceUnitValue);

        /*
         * XPATH: /SAFplusAmf/Component/recovery
         */
        SAFplusAmf::Recovery getRecovery();

        /*
         * XPATH: /SAFplusAmf/Component/recovery
         */
        void setRecovery(SAFplusAmf::Recovery recoveryValue);

        /*
         * XPATH: /SAFplusAmf/Component/restartable
         */
        bool getRestartable();

        /*
         * XPATH: /SAFplusAmf/Component/restartable
         */
        void setRestartable(bool restartableValue);

        /*
         * XPATH: /SAFplusAmf/Component/proxy
         */
        std::string getProxy();

        /*
         * XPATH: /SAFplusAmf/Component/proxy
         */
        void setProxy(std::string proxyValue);

        /*
         * XPATH: /SAFplusAmf/Component/proxied
         */
        std::vector<std::string> getProxied();

        /*
         * XPATH: /SAFplusAmf/Component/proxied
         */
        void setProxied(std::string proxiedValue);

        /*
         * XPATH: /SAFplusAmf/Component/processId
         */
        int getProcessId();

        /*
         * XPATH: /SAFplusAmf/Component/processId
         */
        void setProcessId(int processIdValue);

        /*
         * XPATH: /SAFplusAmf/Component/activeAssignments
         */
        SAFplusAmf::ActiveAssignments* getActiveAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/activeAssignments
         */
        void addActiveAssignments(SAFplusAmf::ActiveAssignments *activeAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/standbyAssignments
         */
        SAFplusAmf::StandbyAssignments* getStandbyAssignments();

        /*
         * XPATH: /SAFplusAmf/Component/standbyAssignments
         */
        void addStandbyAssignments(SAFplusAmf::StandbyAssignments *standbyAssignmentsValue);

        /*
         * XPATH: /SAFplusAmf/Component/instantiate
         */
        SAFplusAmf::Instantiate* getInstantiate();

        /*
         * XPATH: /SAFplusAmf/Component/instantiate
         */
        void addInstantiate(SAFplusAmf::Instantiate *instantiateValue);

        /*
         * XPATH: /SAFplusAmf/Component/terminate
         */
        SAFplusAmf::Terminate* getTerminate();

        /*
         * XPATH: /SAFplusAmf/Component/terminate
         */
        void addTerminate(SAFplusAmf::Terminate *terminateValue);

        /*
         * XPATH: /SAFplusAmf/Component/cleanup
         */
        SAFplusAmf::Cleanup* getCleanup();

        /*
         * XPATH: /SAFplusAmf/Component/cleanup
         */
        void addCleanup(SAFplusAmf::Cleanup *cleanupValue);

        /*
         * XPATH: /SAFplusAmf/Component/timeouts
         */
        SAFplusAmf::Timeouts* getTimeouts();

        /*
         * XPATH: /SAFplusAmf/Component/timeouts
         */
        void addTimeouts(SAFplusAmf::Timeouts *timeoutsValue);

        /*
         * XPATH: /SAFplusAmf/Component/restartCount
         */
        SAFplusAmf::RestartCount* getRestartCount();

        /*
         * XPATH: /SAFplusAmf/Component/restartCount
         */
        void addRestartCount(SAFplusAmf::RestartCount *restartCountValue);
        ~Component();

    };
}
/* namespace SAFplusAmf */
#endif /* COMPONENT_HXX_ */
