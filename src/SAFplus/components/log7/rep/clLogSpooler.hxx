#ifndef CLLOGSPOOLER_HXX
#define CLLOGSPOOLER_HXX

//#include <boost/unordered_map.hpp>
//#include <clHandleApi.hxx>
//#include <clLogApi.hxx>
#include <clObjectMessager.hxx>

#define LOG_SPOOLER_NAME "LogSpooler"

class LogSpooler: public SAFplus::MsgHandler
{
protected:
  SAFplus::Handle logSpoolerHdl;
public:
  LogSpooler();
  void subscribeStream(const char* streamName);
  void subscribeAllStreams();
  virtual void msgHandler(ClIocAddressT from, SAFplus::MsgServer* svr, ClPtrT msg, ClWordT msglen, ClPtrT cookie);
};

#endif // CLLOGSPOOLER
