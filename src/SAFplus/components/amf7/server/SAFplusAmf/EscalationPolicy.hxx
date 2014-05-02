/* 
 * File EscalationPolicy.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef ESCALATIONPOLICY_HXX_
#define ESCALATIONPOLICY_HXX_
#include "SAFplusAmfCommon.hxx"

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "SaTimeT.hxx"
#include <vector>
#include "MgtFactory.hxx"

namespace SAFplusAmf
  {

    class EscalationPolicy : public SAFplus::ClMgtObject {

        /* Apply MGT object factory */
        MGT_REGISTER(EscalationPolicy);

    public:

        /*
         * The maximum number of events that can occur within that time period before escalation occurs.
         */
        SAFplus::ClMgtProv<unsigned long int> maximum;

        /*
         * The time period (in milliseconds) involved.
         */
        SAFplus::ClMgtProv<SAFplusTypes::SaTimeT> duration;

    public:
        EscalationPolicy();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/maximum
         */
        unsigned long int getMaximum();

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/maximum
         */
        void setMaximum(unsigned long int maximumValue);

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/duration
         */
        SAFplusTypes::SaTimeT getDuration();

        /*
         * XPATH: /SAFplusAmf/EscalationPolicy/duration
         */
        void setDuration(SAFplusTypes::SaTimeT durationValue);
        ~EscalationPolicy();

    };
}
/* namespace SAFplusAmf */
#endif /* ESCALATIONPOLICY_HXX_ */
