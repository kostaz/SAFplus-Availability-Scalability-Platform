/* 
 * File Node.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include <vector>
#include "Stats.hxx"
#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include "clMgtIdentifierList.hxx"
#include "Stats.hxx"
#include "clMgtList.hxx"
#include "ServiceUnitFailureEscalationPolicy.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "ServiceUnitFailureEscalationPolicy.hxx"
#include "EntityId.hxx"
#include "ServiceUnit.hxx"
#include "Node.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Node, /SAFplusAmf/Node)

    Node::Node(): adminState("adminState"), operState("operState"), autoRepair("autoRepair"), failFastOnInstantiationFailure("failFastOnInstantiationFailure"), failFastOnCleanupFailure("failFastOnCleanupFailure"), serviceUnits("serviceUnits"), capacityList("capacity")
    {
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&operState, "operState");
        operState.config = false;
        this->addChildObject(&autoRepair, "autoRepair");
        this->addChildObject(&failFastOnInstantiationFailure, "failFastOnInstantiationFailure");
        this->addChildObject(&failFastOnCleanupFailure, "failFastOnCleanupFailure");
        this->addChildObject(&serviceUnits, "serviceUnits");
        this->addChildObject(&stats, "stats");
        this->addChildObject(&serviceUnitFailureEscalationPolicy, "serviceUnitFailureEscalationPolicy");
        this->addChildObject(&capacityList, "capacity");
        capacityList.childXpath="/SAFplusAmf/Node/capacity";
        capacityList.setListKey("resource");
        this->tag.assign("Node");
    };

    Node::Node(std::string nameValue): adminState("adminState"), operState("operState"), autoRepair("autoRepair"), failFastOnInstantiationFailure("failFastOnInstantiationFailure"), failFastOnCleanupFailure("failFastOnCleanupFailure"), serviceUnits("serviceUnits"), capacityList("capacity")
    {
        this->name.value =  nameValue;
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&operState, "operState");
        operState.config = false;
        this->addChildObject(&autoRepair, "autoRepair");
        this->addChildObject(&failFastOnInstantiationFailure, "failFastOnInstantiationFailure");
        this->addChildObject(&failFastOnCleanupFailure, "failFastOnCleanupFailure");
        this->addChildObject(&serviceUnits, "serviceUnits");
        this->addChildObject(&stats, "stats");
        this->addChildObject(&serviceUnitFailureEscalationPolicy, "serviceUnitFailureEscalationPolicy");
        this->addChildObject(&capacityList, "capacity");
        capacityList.childXpath="/SAFplusAmf/Node/capacity";
        capacityList.setListKey("resource");
        this->tag.assign("Node");
    };

    std::vector<std::string> Node::getKeys()
    {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Node::getChildNames()
    {
        std::string childNames[] = { "name", "id", "stats", "adminState", "operState", "capacity", "serviceUnitFailureEscalationPolicy", "autoRepair", "failFastOnInstantiationFailure", "failFastOnCleanupFailure", "serviceUnits" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/Node/adminState
     */
    SAFplusAmf::AdministrativeState Node::getAdminState()
    {
        return this->adminState.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/adminState
     */
    void Node::setAdminState(SAFplusAmf::AdministrativeState &adminStateValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->adminState.value = adminStateValue;
        else
        {
            SAFplus::SimpleTxnOperation<SAFplusAmf::AdministrativeState> *opt = new SAFplus::SimpleTxnOperation<SAFplusAmf::AdministrativeState>(&(adminState.value),adminStateValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/Node/operState
     */
    bool Node::getOperState()
    {
        return this->operState.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/operState
     */
    void Node::setOperState(bool operStateValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->operState.value = operStateValue;
        else
        {
            SAFplus::SimpleTxnOperation<bool> *opt = new SAFplus::SimpleTxnOperation<bool>(&(operState.value),operStateValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/Node/autoRepair
     */
    bool Node::getAutoRepair()
    {
        return this->autoRepair.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/autoRepair
     */
    void Node::setAutoRepair(bool autoRepairValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->autoRepair.value = autoRepairValue;
        else
        {
            SAFplus::SimpleTxnOperation<bool> *opt = new SAFplus::SimpleTxnOperation<bool>(&(autoRepair.value),autoRepairValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnInstantiationFailure
     */
    bool Node::getFailFastOnInstantiationFailure()
    {
        return this->failFastOnInstantiationFailure.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnInstantiationFailure
     */
    void Node::setFailFastOnInstantiationFailure(bool failFastOnInstantiationFailureValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->failFastOnInstantiationFailure.value = failFastOnInstantiationFailureValue;
        else
        {
            SAFplus::SimpleTxnOperation<bool> *opt = new SAFplus::SimpleTxnOperation<bool>(&(failFastOnInstantiationFailure.value),failFastOnInstantiationFailureValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnCleanupFailure
     */
    bool Node::getFailFastOnCleanupFailure()
    {
        return this->failFastOnCleanupFailure.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/failFastOnCleanupFailure
     */
    void Node::setFailFastOnCleanupFailure(bool failFastOnCleanupFailureValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->failFastOnCleanupFailure.value = failFastOnCleanupFailureValue;
        else
        {
            SAFplus::SimpleTxnOperation<bool> *opt = new SAFplus::SimpleTxnOperation<bool>(&(failFastOnCleanupFailure.value),failFastOnCleanupFailureValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnits
     */
    std::vector<SAFplusAmf::ServiceUnit*> Node::getServiceUnits()
    {
        return this->serviceUnits.value;
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnits
     */
    void Node::setServiceUnits(SAFplusAmf::ServiceUnit* serviceUnitsValue)
    {
        this->serviceUnits.value.push_back(serviceUnitsValue);
    };

    /*
     * XPATH: /SAFplusAmf/Node/stats
     */
    SAFplusAmf::Stats* Node::getStats()
    {
        return dynamic_cast<Stats*>(this->getChildObject("stats"));
    };

    /*
     * XPATH: /SAFplusAmf/Node/stats
     */
    void Node::addStats(SAFplusAmf::Stats *statsValue)
    {
        this->addChildObject(statsValue, "stats");
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy
     */
    SAFplusAmf::ServiceUnitFailureEscalationPolicy* Node::getServiceUnitFailureEscalationPolicy()
    {
        return dynamic_cast<ServiceUnitFailureEscalationPolicy*>(this->getChildObject("serviceUnitFailureEscalationPolicy"));
    };

    /*
     * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy
     */
    void Node::addServiceUnitFailureEscalationPolicy(SAFplusAmf::ServiceUnitFailureEscalationPolicy *serviceUnitFailureEscalationPolicyValue)
    {
        this->addChildObject(serviceUnitFailureEscalationPolicyValue, "serviceUnitFailureEscalationPolicy");
    };

    Node::~Node()
    {
    };

}
/* namespace SAFplusAmf */
