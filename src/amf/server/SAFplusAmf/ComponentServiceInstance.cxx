/* 
 * File ComponentServiceInstance.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "clMgtIdentifier.hxx"
#include "clTransaction.hxx"
#include "ServiceInstance.hxx"
#include "clMgtIdentifierList.hxx"
#include "Component.hxx"
#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "EntityId.hxx"
#include <string>
#include "clMgtProvList.hxx"
#include "ComponentServiceInstance.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(ComponentServiceInstance, /SAFplusAmf/ComponentServiceInstance)

    ComponentServiceInstance::ComponentServiceInstance(): protectionGroup("protectionGroup"), dependencies("dependencies"), serviceInstance("serviceInstance"), standbyComponents("standbyComponents"), activeComponents("activeComponents"), dataList("data")
    {
        this->addChildObject(&protectionGroup, "protectionGroup");
        this->addChildObject(&dependencies, "dependencies");
        this->addChildObject(&serviceInstance, "serviceInstance");
        this->addChildObject(&standbyComponents, "standbyComponents");
        standbyComponents.config = false;
        this->addChildObject(&activeComponents, "activeComponents");
        activeComponents.config = false;
        this->addChildObject(&dataList, "data");
        this->tag.assign("ComponentServiceInstance");
    };

    ComponentServiceInstance::ComponentServiceInstance(std::string nameValue): protectionGroup("protectionGroup"), dependencies("dependencies"), serviceInstance("serviceInstance"), standbyComponents("standbyComponents"), activeComponents("activeComponents"), dataList("data")
    {
        this->name.value =  nameValue;
        this->addChildObject(&protectionGroup, "protectionGroup");
        this->addChildObject(&dependencies, "dependencies");
        this->addChildObject(&serviceInstance, "serviceInstance");
        this->addChildObject(&standbyComponents, "standbyComponents");
        this->addChildObject(&activeComponents, "activeComponents");
        this->addChildObject(&dataList, "data");
        this->tag.assign("ComponentServiceInstance");
    };

    std::vector<std::string> ComponentServiceInstance::getKeys()
    {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* ComponentServiceInstance::getChildNames()
    {
        std::string childNames[] = { "name", "id", "protectionGroup", "dependencies", "data", "serviceInstance", "standbyComponents", "activeComponents" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/protectionGroup
     */
    std::vector<std::string> ComponentServiceInstance::getProtectionGroup()
    {
        return this->protectionGroup.value;
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/protectionGroup
     */
    void ComponentServiceInstance::setProtectionGroup(std::string protectionGroupValue)
    {
        this->protectionGroup.value.push_back(protectionGroupValue);
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/dependencies
     */
    std::vector<SAFplusAmf::ComponentServiceInstance*> ComponentServiceInstance::getDependencies()
    {
        return this->dependencies.value;
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/dependencies
     */
    void ComponentServiceInstance::setDependencies(SAFplusAmf::ComponentServiceInstance* dependenciesValue)
    {
        this->dependencies.value.push_back(dependenciesValue);
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/serviceInstance
     */
    SAFplusAmf::ServiceInstance* ComponentServiceInstance::getServiceInstance()
    {
        return this->serviceInstance.value;
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/serviceInstance
     */
    void ComponentServiceInstance::setServiceInstance(SAFplusAmf::ServiceInstance* serviceInstanceValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->serviceInstance.value = serviceInstanceValue;
        else
        {
            SAFplus::SimpleTxnOperation<SAFplusAmf::ServiceInstance*> *opt = new SAFplus::SimpleTxnOperation<SAFplusAmf::ServiceInstance*>(&(serviceInstance.value),serviceInstanceValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/standbyComponents
     */
    std::vector<SAFplusAmf::Component*> ComponentServiceInstance::getStandbyComponents()
    {
        return this->standbyComponents.value;
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/standbyComponents
     */
    void ComponentServiceInstance::setStandbyComponents(SAFplusAmf::Component* standbyComponentsValue)
    {
        this->standbyComponents.value.push_back(standbyComponentsValue);
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/activeComponents
     */
    std::vector<SAFplusAmf::Component*> ComponentServiceInstance::getActiveComponents()
    {
        return this->activeComponents.value;
    };

    /*
     * XPATH: /SAFplusAmf/ComponentServiceInstance/activeComponents
     */
    void ComponentServiceInstance::setActiveComponents(SAFplusAmf::Component* activeComponentsValue)
    {
        this->activeComponents.value.push_back(activeComponentsValue);
    };

    ComponentServiceInstance::~ComponentServiceInstance()
    {
    };

}
/* namespace SAFplusAmf */
