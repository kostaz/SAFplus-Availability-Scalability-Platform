/* 
 * File Capacity.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#include "MgtFactory.hxx"
#include "clMgtContainer.hxx"
#include "clTransaction.hxx"
#include <string>
#include "clMgtProv.hxx"
#include "SAFplusAmfCommon.hxx"
#include <cstdint>
#include <vector>
#include "Capacity.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(Capacity, /SAFplusAmf/safplusAmf/Node/capacity)

    Capacity::Capacity(): SAFplus::MgtContainer("capacity"), resource("resource"), value("value")
    {
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
    };

    Capacity::Capacity(std::string resourceValue): SAFplus::MgtContainer("capacity"), resource("resource"), value("value")
    {
        this->resource.value =  resourceValue;
        this->addChildObject(&resource, "resource");
        this->addChildObject(&value, "value");
    };

    std::vector<std::string> Capacity::getKeys()
    {
        std::string keyNames[] = { "resource" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* Capacity::getChildNames()
    {
        std::string childNames[] = { "resource", "value" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Node/capacity/resource
     */
    std::string Capacity::getResource()
    {
        return this->resource.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Node/capacity/resource
     */
    void Capacity::setResource(std::string resourceValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->resource.value = resourceValue;
        else
        {
            SAFplus::SimpleTxnOperation<std::string> *opt = new SAFplus::SimpleTxnOperation<std::string>(&(resource.value),resourceValue);
            t.addOperation(opt);
        }
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Node/capacity/value
     */
    ::int64_t Capacity::getValue()
    {
        return this->value.value;
    };

    /*
     * XPATH: /SAFplusAmf/safplusAmf/Node/capacity/value
     */
    void Capacity::setValue(::int64_t valueValue, SAFplus::Transaction &t)
    {
        if(&t == &SAFplus::NO_TXN) this->value.value = valueValue;
        else
        {
            SAFplus::SimpleTxnOperation<::int64_t> *opt = new SAFplus::SimpleTxnOperation<::int64_t>(&(value.value),valueValue);
            t.addOperation(opt);
        }
    };

    Capacity::~Capacity()
    {
    };

}
/* namespace ::SAFplusAmf */
