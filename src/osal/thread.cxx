#include <clCommon.hxx>
#include <clThreadApi.hxx>
#include <cltypes.h>
//#include <clCksmApi.h>
//#include <clCommon.h>
//#include <clCommonErrors.h>
#include <errno.h>
#include <stdio.h>
#include <chrono>
#ifdef USE_BOOST_CHRONO
#include <boost/chrono.hpp>
#endif

namespace SAFplus
{

  uint64_t nowMs() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

  uint64_t timerMs() 
{ 
#ifdef USE_BOOST_CHRONO
  return boost::chrono::time_point_cast<boost::chrono::milliseconds>(boost::chrono::steady_clock::now()).time_since_epoch().count(); 
#else
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
#endif
}

Wakeable& BLOCK = *((Wakeable*) NULL);
Wakeable& ABORT = *((Wakeable*) 1);
WakeableNoop IGNORE;

  /* from semctl man page, calling program needs to define this struct */
typedef union CosSemCtl_u
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo  *__buf; 
} CosSemCtl_t;

  
  ProcSem::ProcSem(unsigned int key,int initialValue)
  {
    init(key,initialValue);   
  }

  ProcSem::ProcSem(const char* key,int initialValue)
  {
    ClUint32T realKey;
    int keyLen = strlen(key);
    realKey = computeCrc32((ClUint8T*) key, keyLen);
    init(realKey,initialValue);
  }
  
  void ProcSem::init(const char* key,int initialValue)
    {
    ClUint32T realKey;
    int keyLen = strlen(key);
    realKey = computeCrc32((ClUint8T*) key, keyLen);
    init(realKey,initialValue);
    }

  void ProcSem::init(unsigned int key,int initialValue)
  {
    uint_t retry;
    uint_t flags = 0666;
    do  // open the semaphore, creating it if it does not exist.
      {
      retry = 0;
      semId = semget(key, 1, flags);
      if(semId < 0 )
        {
        int err = errno;
        if(err == EINTR) retry = 1;
        // The IPC_EXCL is used because I need to KNOW whether I created this sem or not so that 
        // the creator is the only entity that initializes it
        else if (err == ENOENT) { flags |= IPC_CREAT | IPC_EXCL; retry = 1; }
        else if (err == EEXIST) { flags ^= IPC_CREAT | IPC_EXCL; retry = 1; }
        else
          {
            assert(0);  // Later raise exception
          }
        }
      } while(retry);

    if( (flags & IPC_CREAT) )
      {
        int err;
        CosSemCtl_t arg = {0};
        arg.val = initialValue;
        retry = 0;
        do
          {
            err = semctl(semId,0,SETVAL,arg);
            if(err < 0 )
              {
                if(errno == EINTR) retry = 1;
                else
                  {
                    assert(0);
                  }
        
              }
          } while(retry);
      }    
  }
  
  void ProcSem::lock(int amt)
    {
      struct sembuf sembuf = {0,(short int)(-1*amt),SEM_UNDO};
      int err;
      do
        {        
          err = semop(semId,&sembuf,1);
        } while ((err<0)&&(errno==EINTR));
      if (err<0)
        {
          int err = errno;
          assert(err<0);
        }
    }

  void ProcSem::wake(int amt,void* cookie) { unlock(amt); }  
  
  void ProcSem::unlock(int amt)
    {
      struct sembuf sembuf = {0,((short int)amt),SEM_UNDO};
      int err;
      do
        {        
          err = semop(semId,&sembuf,1);
        } while ((err<0)&&(errno==EINTR));
      if (err<0)
        {
          int err = errno;
          assert(err<0);
        }
    }
  
  bool ProcSem::try_lock(int amt)
  {
    struct sembuf sembuf = {0, (short int)(-1*amt),SEM_UNDO | IPC_NOWAIT};
    int err;
    do
      {
        err = semop(semId,&sembuf,1);
      } while ((err<0)&&(errno==EINTR));
    if (err<0)
      {
        int err = errno;
        if (err == EAGAIN) return false;
      }
    return true;
  }
  
  bool ProcSem::timed_lock(uint64_t mSec,int amt)
    {
      struct sembuf sembuf = {0,(short int)(-1*amt),SEM_UNDO};
      long int temp = (((long)mSec)%1000L)*1000L*1000L;
      struct timespec timeout = {(time_t) (mSec/1000), temp};  // tv_sec, tv_nsec
      int err;
      do
        {
          err = semtimedop(semId,&sembuf,1,&timeout);
        } while ((err<0)&&(errno==EINTR));
      if (err<0)
        {
          int err = errno;
          if (err == EAGAIN) return false;
          else
            {
              perror("timed_lock");
            assert(0);
            }
        }
      return true;
    }

  template<class bstMutT> void tMutex<bstMutT>::wake(int amt,void* cookie)
  {
    unlock();
  };

  // Instantiate these templates
  template class tMutex<boost::timed_mutex>;
  template class tMutex<boost::recursive_timed_mutex>;
  
  /**
   * Implement class ThreadCondition
   */
  ThreadCondition::ThreadCondition() {};

   void ThreadCondition::notify_one()
   {
       waitCondition.notify_one();
   }

   void ThreadCondition::notify_all()
   {
       waitCondition.notify_all();
   }

  void ThreadCondition::wake(int amt,void* cookie)
   {
       waitCondition.notify_all();
   }

   void ThreadCondition::wait(SAFplus::Mutex &mutex)
   {
       waitCondition.wait(mutex);
   }

   bool ThreadCondition::timed_wait(SAFplus::Mutex &mutex, int duration)
   {
     //boost::system_time const timeout = boost::get_system_time() + boost::posix_time::milliseconds(duration);
     // return waitCondition.timed_wait(mutex, timeout);
     auto timeout = boost::posix_time::milliseconds(duration);
     return waitCondition.timed_wait(mutex, timeout);
   }

  ThreadSem::ThreadSem(int initialValue)
  {
  countv = initialValue;
  }

#if 0
  ThreadSem::ThreadSem()
  {
  countv = 0;
  }
#endif

  void ThreadSem::init(int initialValue)
  {
  countv = initialValue;
  }

  void ThreadSem::lock(int amt)
  {
  mutex.lock();
  while (countv<amt)
    {
    cond.wait(mutex);
    }
  countv -= amt;
  mutex.unlock();
  }

  void ThreadSem::wake(int amt,void* cookie) { unlock(amt); }  

  void ThreadSem::unlock(int amt)
  {
  mutex.lock();
  countv += amt;
  cond.notify_all();
  mutex.unlock();
  }

bool ThreadSem::try_lock(int amt)
  {
  mutex.lock();
  if (countv<amt)
    {
    mutex.unlock();
    return false;
    }
  countv -= amt;
  cond.notify_all();  // Notifying here because the count was decreased, and some people may be blocking until zero
  mutex.unlock();
  return true;
  }

bool ThreadSem::timed_lock(uint64_t mSec,int amt)
  {
  ScopedLock<> lock(mutex);
  while (countv<amt)
    {
    // TODO: take into account elapsed time going around the while loop more than once
    if (!cond.timed_wait(mutex,mSec)) return false;
    }
  countv -= amt;
  cond.notify_all(); // Notifying here because the count was decreased, and some people may be blocking until zero
  return true;
  }

bool ThreadSem::blockUntil(uint amt,uint mSec)
  {
  ScopedLock<> lock(mutex);
  int64_t start = timerMs();
  while (countv > amt)
    {
    if (!cond.timed_wait(mutex,mSec)) return false;
    int64_t diff = timerMs()-start; // take into account elapsed time going around the while loop more than once
    if (diff > 0)  // this check avoids weird issues like integer overflow and inconsistent timerMs()
      {
        if (diff >= mSec) mSec -= diff;
        else return false;
      }
    }
  }

  ThreadSem::~ThreadSem()
  {
  countv = -1;  // Indicate that this object was deleted by putting an impossible value in count
  }


ProcGate::ProcGate(unsigned int key,int initialValue)
  {
  init(key,initialValue);
  }

ProcGate::ProcGate(const char* key,int initialValue)
  {
  ClUint32T realKey;
  int keyLen = strlen(key);
  realKey = computeCrc32((ClUint8T*) key, keyLen);
  init(realKey,initialValue);
  }

enum
  {
    LockSem = 0,
    GateSem = 1,

    SEM_NO_FLAG = 0,
  };
  
  void ProcGate::init(unsigned int key, int initialValue)
    {
    locked = false;
    if (initialValue != 0) initialValue = 1;  // Make it boolean
    uint_t retry;
    uint_t flags = 0666;
    do  // open the semaphore, creating it if it does not exist.
      {
      retry = 0;
      semId = semget(key, 2, flags);
      if(semId < 0 )
        {
        int err = errno;
        if(err == EINTR) retry = 1;
        // The IPC_EXCL is used because I need to KNOW whether I created this sem or not so that 
        // the creator is the only entity that initializes it
        else if (err == ENOENT) { flags |= IPC_CREAT | IPC_EXCL; retry = 1; }
        else if (err == EEXIST) { flags ^= IPC_CREAT | IPC_EXCL; retry = 1; }
        else
          {
          assert(0);  // Later raise exception
          }
        }
      } while(retry);

    if( (flags & IPC_CREAT) )
      {
      int err;
      CosSemCtl_t arg = {0};
      arg.val = 0; // initialValue;
      retry = 0;
      do
        {
        err = semctl(semId,LockSem,SETVAL,0);
        if(err < 0 )
          {
          if(errno == EINTR) retry = 1;
          else
            {
            assert(0);
            }
          }
        arg.val = initialValue;  // The gate starts open or closed?
        err = semctl(semId,GateSem,SETVAL,arg);
        if(err < 0 )
          {
          if(errno == EINTR) retry = 1;
          else
            {
            assert(0);
            }
        
          }
        } while(retry);
      }    
    }
  

    void ProcGate::wake(int amt,void* cookie) { open(); }
    void ProcGate::lock(int amt)   // This is not exclusive -- multiple entities can hold the lock at the same time.
      {
        assert(!locked);  // A recursive lock when the gate closes between lock calls will deadlock
      // Block until the gate is open (= zero), then this lock will increment the semaphore
      struct sembuf sembuf[] = {{GateSem, 0,SEM_NO_FLAG},{LockSem, (short int)(1*amt),SEM_UNDO }};  // semadj -= amt
      int error;
      do
        {
          error = semop(semId,sembuf,2);
        } while ((error<0)&&(errno==EINTR));
      if (error<0)
        {
          int err = errno;
          assert(errno);  // Sem does not exist, or you don't have permissions.  Did you remember to initialize the service?
        }
      locked=true;
      }
  void ProcGate::unlock(int amt)
      {
        assert(locked);
        struct sembuf sembuf = {LockSem, (short int)(-1*amt),SEM_UNDO };  // semadj += amt: "undo"ing this operation actually undoes the lock() resulting in a zero adjustment if the process then fails.
      int err;
      do
        {
          err = semop(semId,&sembuf,1);
        } while ((err<0)&&(errno==EINTR));
      if (err<0)
        {
          int err = errno;
          assert(err<0);
        }
      locked=false;
      }

    bool ProcGate::try_lock(int amt)
    {
    assert(0);
    }

    bool ProcGate::timed_lock(uint64_t mSec,int amt)
      {
      assert(0);
      }

    void ProcGate::close()  // close the gate so all lockers block on lock, returns when no entity has a lock.
      {
	//  printf("GATE %d closed\n", semId);
      if (1)  // First, close the gate
        {
        struct sembuf sembuf[] = { {GateSem, (short int)1,SEM_UNDO }  };
        int err;
        do
          {
          err = semop(semId,sembuf,1);
          } while ((err<0)&&(errno==EINTR));
        if (err<0)
          {
          int err = errno;
          assert(err<0);
          }
        }

      if (1)  // now wait for all racers to leave or be blocked by the gate (wait for zero)
        {
        struct sembuf sembuf =  {LockSem, 0,SEM_NO_FLAG };
        int err;
        do
          {
          err = semop(semId,&sembuf,1);
          } while ((err<0)&&(errno==EINTR));
        if (err<0)
          {
          int err = errno;
          assert(err<0);
          }
        }
      }

void ProcGate::open()   // open the gate to allow lockers to proceed.
  {  
    //printf("GATE %d opened\n", semId);
      
  struct sembuf sembuf[] = { {GateSem, (short int) -1,SEM_UNDO }  };  // semadj += 1: "undo"ing this operation actually undoes the close() resulting in a zero adjustment if the process then fails.
  int error;
  do
    {
    error = semop(semId,sembuf,1);
    } while ((error<0)&&(errno==EINTR));
  if (error<0)
    {
    int err = errno;
    assert(err<0);
    }
  }

  };

