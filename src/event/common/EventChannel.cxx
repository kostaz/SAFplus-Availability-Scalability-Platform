/*
 * EventChannel.cxx
 *
 *  Created on: Apr 13, 2017
 *      Author: minhgiang
 */

#include "EventChannel.hxx"
#include <clLogApi.hxx>


using namespace SAFplusI;
using namespace SAFplus;

EventChannel::EventChannel() {
	// TODO Auto-generated constructor stub

}

EventChannel::~EventChannel() {
	// TODO Auto-generated destructor stub
}

void EventChannel::addChannelSub(EventSubscriber * sub)
{
    this->eventSubs.push_back(*sub);
}

void EventChannel::addChannelPub(EventPublisher* pub)
{
    this->eventPubs.push_back(*pub);
}



struct eventSub_delete_disposer
{
  void operator()(EventSubscriber *delete_this)
  {
    delete delete_this;
  }
};

struct eventPub_delete_disposer
{
  void operator()(EventPublisher *delete_this)
  {
    delete delete_this;
  }
};

void EventChannel::deleteChannelSub(SAFplus::Handle subHandle)
{
    //TODO delete all sub with sub handle
	logDebug("EVT", "MSG", "debug 1");
    if(eventSubs.empty())
    {
    	logDebug("EVT", "MSG", "Event subscriber list is empty");
        return;
    }
    logDebug("EVT", "MSG", "debug 2");
    for (EventSubscriberList::iterator iter = eventSubs.begin(); iter != eventSubs.end(); iter++)
    {
        EventSubscriber &evtSub = *iter;
        if(evtSub.usr.evtHandle==subHandle)
        {
        	logDebug("EVT", "MSG", "Found event subscriber ... Removing...");
            eventPubs.erase_and_dispose(iter, eventPub_delete_disposer());ddd
            return;
        }
    }
	logDebug("EVT", "MSG", "No Subscriber found ...");
}

void EventChannel::deleteChannelPub(SAFplus::Handle pubHandle)
{
    //TODO delete all sub with sub handle
    if(eventPubs.empty())
    {
        return;
    }
    for (EventPublisherList::iterator iter = eventPubs.begin(); iter != eventPubs.end(); iter++)
    {
        EventPublisher &evtPub = *iter;
        if(evtPub.usr.evtHandle==pubHandle)
        {
            eventPubs.erase_and_dispose(iter, eventPub_delete_disposer());
            return;
        }
    }

}