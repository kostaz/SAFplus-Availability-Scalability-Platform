#include <EventClient.hxx>
#include <clGlobals.hxx>
#include <clMsgPortsAndTypes.hxx>
#include <clSafplusMsgServer.hxx>
#include <string>

using namespace std;
using namespace SAFplus;

//ClUint32T clAspLocalId = 0x1;
static unsigned int MAX_MSGS=25;
static unsigned int MAX_HANDLER_THREADS=2;
ClBoolT   gIsNodeRepresentative = false;
SafplusInitializationConfiguration sic;
SAFplus::Handle eventEntityHandle;
SAFplus::Handle me;
EventClient fc;

void testAllFeature();
#define EVENT_CLIENT_PID 50

void eventCallback(uintcw_t channelId,EventChannelScope scope,void* data,int length)
{
	logDebug("EVT", "MSG", "Receive event from event channel with id [%ld]", channelId);
	logDebug("EVT", "MSG", "Event data [%s]", static_cast<std::string*>(data));

}
int main(int argc, char* argv[])
{
	logEchoToFd = 1;  // echo logs to stdout for debugging
	logSeverity = LOG_SEV_MAX;
	sic.iocPort     = 50;
	safplusInitialize(SAFplus::LibDep::IOC | SAFplus::LibDep::LOG |SAFplus::LibDep::MSG ,sic);
	logSeverity = LOG_SEV_MAX;
	logInfo("FLT","CLT","********************Start msg server********************");
	safplusMsgServer.Start();

	me = getProcessHandle(EVENT_CLIENT_PID,SAFplus::ASP_NODEADDR);
	//eventEntityHandle = getProcessHandle(FAULT_ENTITY_PID,SAFplus::ASP_NODEADDR);
	logInfo("FLT","CLT","********************Initial event client*********************");
	fc.eventInitialize(me,&eventCallback);
	//fc.registerFault();
	testAllFeature();
	sleep(1);
	while(0)
	{
		sleep(10000);
	}
	return 0;
}


void testAllFeature()
{

	std::string localChannel = "testLocalchannel";
	std::string globalChannel = "testGlobalchannel";
	std::string localChannel1 = "testLocalchannel";
	const void* testEventData = "this is the test event";

	logInfo("FLT","CLT","********************Open local channel *********************");
	fc.eventChannelOpenRpc(localChannel,EventChannelScope::EVENT_LOCAL_CHANNEL);
	sleep(1);
	logInfo("FLT","CLT","********************Open global channel *********************");
	fc.eventChannelOpenRpc(globalChannel,EventChannelScope::EVENT_GLOBAL_CHANNEL);
	sleep(1);
	logInfo("FLT","CLT","********************Open local channel (test duplicate *********************");
	fc.eventChannelOpenRpc(localChannel,EventChannelScope::EVENT_LOCAL_CHANNEL);
	sleep(1);
	logInfo("FLT","CLT","********************close local channel *********************");
	fc.eventChannelCloseRpc(localChannel,EventChannelScope::EVENT_LOCAL_CHANNEL);
	sleep(1);
	logInfo("FLT","CLT","********************Open local channel *********************");
	fc.eventChannelOpenRpc(localChannel,EventChannelScope::EVENT_LOCAL_CHANNEL);
	sleep(1);
	logInfo("FLT","CLT","********************Unsubscriber local channel *********************");
	fc.eventChannelUnSubscriberRpc(localChannel,EventChannelScope::EVENT_LOCAL_CHANNEL);
	sleep(1);
	logInfo("FLT","CLT","********************Subscriber local channel *********************");
	fc.eventChannelSubscriberRpc(localChannel,EventChannelScope::EVENT_LOCAL_CHANNEL);
	sleep(1);

	logInfo("FLT","CLT","********************Subscriber local channel *********************");
	fc.eventPublishRpc(testEventData,22,localChannel,EventChannelScope::EVENT_LOCAL_CHANNEL);
	sleep(1);

	while(1)
	{
		sleep(1);
	}





}

