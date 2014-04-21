/* 
 * File ServiceUnitFailureEscalationPolicy.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef SERVICEUNITFAILUREESCALATIONPOLICY_HXX_
#define SERVICEUNITFAILUREESCALATIONPOLICY_HXX_

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "SaTimeT.hxx"
#include <vector>
#include "MgtFactory.hxx"

namespace SAFplusAmf {

    class ServiceUnitFailureEscalationPolicy : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(ServiceUnitFailureEscalationPolicy);

    public:

        /*
         * The maximum number of events that can occur within that time period before escalation occurs.
         */
        ClMgtProv<unsigned long int> maximum;

        /*
         * The time period (in milliseconds) involved.
         */
        ClMgtProv<SAFplusTypes::SaTimeT> duration;

    public:
         ServiceUnitFailureEscalationPolicy();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy/maximum
         */
        unsigned long int getMaximum();

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy/maximum
         */
        void setMaximum(unsigned long int maximumValue);

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy/duration
         */
        SAFplusTypes::SaTimeT getDuration();

        /*
         * XPATH: /SAFplusAmf/Node/serviceUnitFailureEscalationPolicy/duration
         */
        void setDuration(SAFplusTypes::SaTimeT durationValue);
         ~ServiceUnitFailureEscalationPolicy();

    };
}
/* namespace SAFplusAmf */
#endif /* SERVICEUNITFAILUREESCALATIONPOLICY_HXX_ */