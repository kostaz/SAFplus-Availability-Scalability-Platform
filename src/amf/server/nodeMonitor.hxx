#pragma once

#include <clMsgApi.hxx>
#include <clThreadApi.hxx>

class NodeMonitor:public SAFplus::MsgHandler
{
public:
  NodeMonitor():maxSilentInterval(0), active(false), standby(false),quit(true) {};  // two step constructor
  ~NodeMonitor();
  void init(void);
  void becomeActive(void);
  void becomeStandby(void);
  void monitorThread(void);
  void operator() () { monitorThread(); }
  virtual void msgHandler(SAFplus::MsgServer* svr, SAFplus::Message* msg, ClPtrT cookie);
protected:

  SAFplus::Mutex exclusion;
  int64_t lastHeard[SAFplus::MaxNodes];
  int64_t maxSilentInterval;
  int64_t lastHbRequest;
  SAFplus::Handle lastHbHandle;
  boost::thread thread;
  bool active;
  bool standby;
  bool quit;
};
