/* 
 * File Component.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "unitTestCommon.hxx"

#include <string>
#include "clTransaction.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "Component.hxx"


namespace unitTest
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Component, /unitTest/Component)

    Component::Component(): SAFplus::MgtContainer("Component"), name("name"), id("id"), data("data"), key("key")
    {
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&data, "data");
        this->addChildObject(&key, "key");
    };

    Component::Component(std::string nameValue, unsigned int idValue, unsigned int keyValue): SAFplus::MgtContainer("Component"), name("name"), id("id"), data("data"), key("key")
    {
        this->name.value =  nameValue;
        this->id.value =  idValue;
        this->key.value =  keyValue;
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&data, "data");
        this->addChildObject(&key, "key");
    };

    std::vector<std::string> Component::getKeys()
    {
        std::string keyNames[] = { "name", "id", "key" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Component::getChildNames()
    {
        std::string childNames[] = { "name", "id", "data", "key" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /unitTest/Component/name
     */
    std::string Component::getName()
    {
        return this->name.value;
    };

    /*
     * XPATH: /unitTest/Component/name
     */
    void Component::setName(std::string nameValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->name.value = nameValue;
        else
        {
            SAFplus::SimpleTxnOperation<std::string> *opt = new SAFplus::SimpleTxnOperation<std::string>(&(name.value),nameValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /unitTest/Component/id
     */
    unsigned int Component::getId()
    {
        return this->id.value;
    };

    /*
     * XPATH: /unitTest/Component/id
     */
    void Component::setId(unsigned int idValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->id.value = idValue;
        else
        {
            SAFplus::SimpleTxnOperation<unsigned int> *opt = new SAFplus::SimpleTxnOperation<unsigned int>(&(id.value),idValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /unitTest/Component/data
     */
    long int Component::getData()
    {
        return this->data.value;
    };

    /*
     * XPATH: /unitTest/Component/data
     */
    void Component::setData(long int dataValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->data.value = dataValue;
        else
        {
            SAFplus::SimpleTxnOperation<long int> *opt = new SAFplus::SimpleTxnOperation<long int>(&(data.value),dataValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /unitTest/Component/key
     */
    unsigned int Component::getKey()
    {
        return this->key.value;
    };

    /*
     * XPATH: /unitTest/Component/key
     */
    void Component::setKey(unsigned int keyValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->key.value = keyValue;
        else
        {
            SAFplus::SimpleTxnOperation<unsigned int> *opt = new SAFplus::SimpleTxnOperation<unsigned int>(&(key.value),keyValue);
            t.addOperation(opt);
        }
    };

    Component::~Component()
    {
    };

}
/* namespace unitTest */
