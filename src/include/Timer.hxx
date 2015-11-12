
/*******************************************************************************
 *
 * This headerfile is auto-generated by OpenClovis IDE
 *
 * clCompPorts.h
 *
 ********************************************************************************/
#ifndef TimerH
#define TimerH

// Standard includes
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/intrusive/rbtree.hpp>
#include <boost/noncopyable.hpp>
#include <functional>
// SAFplus includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
//#include <clList.h>
#include <clCommon.hxx>
#include <clTimerErrors6.h>
#include <clThreadPool.hxx>

#define TIMER_RUNNING  (0x1)
#define TIMER_STOPPED  (0x2)
#define TIMER_DELETED  (0x4)
#define TIMER_CLUSTER  (0x8)
#define TIMER_FREQUENCY (10)  /*10 millisecs*/
#define TIMER_CLUSTER_FREQUENCY_USEC (10000000L)
#define TIMER_CLUSTER_VERSION (0x1)
#ifndef VXWORKS_BUILD
#define TIMER_MAX_PARALLEL_TASKS (0x20)
#else
#define TIMER_MAX_PARALLEL_TASKS (0x2)
#endif

typedef ClRcT (*TimerCallBackT) (void *);
typedef ClPtrT TimerHandleT;

typedef struct {
  /** Number of seconds of the timeout */
  ClUint32T   tsSec;
  /** Number of Milliseconds.  Its ok for this to be > 1000 (i.e. more than 1 second) */
  ClUint32T   tsMilliSec;
} TimerTimeOutT;

typedef enum {
  /** Fire just once */
  TIMER_ONE_SHOT = 0,
  /** Fire periodically */
  TIMER_REPETITIVE,
  /* Fire once and deleted automatically*/
  TIMER_VOLATILE,
  TIMER_MAX_TYPE,
}TimerTypeT;

typedef enum {
  /** Use the timer thread */
  TIMER_TASK_CONTEXT = 0,
  /** A new thread will be created to invoke the callback. */
  TIMER_SEPARATE_CONTEXT,
  TIMER_MAX_CONTEXT,
}TimerContextT;

namespace SAFplus
{
  ClRcT timerInitialize(ClPtrT config);
  ClRcT timerFinalize(void);

  class TimerPoolable: public Poolable
  {
  public:
    TimerPoolable(UserCallbackT fn=NULL, void* arg=NULL, uint32_t timeLimit=300000, bool deleteWhenComplete=false): Poolable(fn, arg, timeLimit, deleteWhenComplete) {}
    virtual void wake(int amt, void* cookie)
    {
      if (fn)
      {
        fn(arg);
      }
    }
  };


  class Timer : public boost::intrusive::set_base_hook<boost::intrusive::optimize_size<true>>
  {
  public:
    //ClRbTreeT timerList;
    TimerTypeT timerType;
    TimerContextT timerContext;
    signed long long timerTimeOut;
    boost::posix_time::ptime timerExpiry;
    TimerCallBackT timerCallback;
    ClPtrT timerData;
    bool timerFlags;
    signed int timerRefCnt; /*reference count of inflight separate task timers*/
    boost::posix_time::ptime startTime;
    boost::posix_time::ptime startRepTime;
    boost::posix_time::ptime endTime;
    pthread_t callbackTaskIds[TIMER_MAX_PARALLEL_TASKS];
    signed short freeCallbackTaskIndex;
    signed short freeCallbackTaskIndexPool[TIMER_MAX_PARALLEL_TASKS];
    TimerPoolable *timerPool;
    void timerDelCallbackTask(signed short freeIndex);
    signed short timerAddCallbackTask();
    void timerInitCallbackTask();
    ClRcT timerStartInternal(boost::posix_time::ptime expiry,bool locked);
    ClRcT timerStop();
    ClRcT timerState(bool flags, bool *pState);
    ClRcT timerStart();
    ClRcT timerUpdate(TimerTimeOutT newTimeOut);
    ClRcT timerRestart (TimerHandleT  timerHandle);
    bool timerIsStopped();
    bool timerIsRunning();
    ClRcT timerCreate(TimerTimeOutT timeOut,
        TimerTypeT timerType,
        TimerContextT timerContext,
        TimerCallBackT timerCallback,
        void *timerData);
    ClRcT timerCreateAndStart(TimerTimeOutT timeOut,
        TimerTypeT timerType,
        TimerContextT timerContext,
        TimerCallBackT timerCallback,
        void *timerData);
    Timer()
    {

    }
    Timer(TimerTimeOutT timeOut,
        TimerTypeT timerType,
        TimerContextT timerContext,
        TimerCallBackT timerCallback,
        void *timerData);
    ~Timer();
    friend bool operator< (const Timer &a, const Timer &b)
    {  return a.timerExpiry < b.timerExpiry;  }
    friend bool operator> (const Timer &a, const Timer &b)
    {  return a.timerExpiry > b.timerExpiry;  }
    friend bool operator== (const Timer &a, const Timer &b)
                   {  return a.timerExpiry == b.timerExpiry;  }
  };

  class TimerBase
  {
  public:
    bool initialized;
    bool timerRunning;
    SAFplus::Mutex timerListLock;
    boost::posix_time::ptime now;
    boost::intrusive::rbtree<Timer> timerTree;
    pthread_t timerId;
    unsigned int runningTimers;
    int frequency; //millisecond
    ThreadPool *pool;
    /*
     * Cluster timer replicate method registered
     */
    TimerBase();
    ClRcT TimerBaseInitialize();
    ClRcT timerRun(void);
    void timerSpawn(Timer *pTimer);
    void timeUpdate(void);
    ~TimerBase()
    {

    }
    Timer *get_rbtree_min();
  };

}

#endif
