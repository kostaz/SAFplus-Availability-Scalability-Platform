
#include "logcfg.hxx"
#include <clNameApi.hxx>
#include <Replicate.hxx>
#include <clLogIpi.hxx>
#include <syslog.h>
#include <boost/container/map.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <boost/lexical_cast.hpp>

#include <ServerConfig.hxx>
#include <StreamConfig.hxx>
#include <FileFullAction.hxx>
#include <Stream.hxx>
#include <StreamScope.hxx>
#include <SAFplusLogModule.hxx>

#define Dbg printf

using namespace std;
using namespace SAFplusLog;
using namespace SAFplus;
namespace fs = boost::filesystem;

typedef boost::container::multimap<std::time_t, fs::path> file_result_set_t;

#if 0
LogCfg::LogCfg():MgtContainer("SAFplusLog")
{
  this->addChildObject(&serverConfig, "serverConfig");
  this->addChildObject(&streamConfig, "streamConfig");
}

#endif
SAFplusLog::SAFplusLogModule logCfg;

HandleStreamMap hsMap;
Stream* sysStreamCfg;
Stream* appStreamCfg;

#if (CL_LOG_SEV_EMERGENCY == LOG_EMERG)  // If the numbers line up we do not need to transform them
inline int logLevel2SyslogLevel(int ocll)
{
  return ocll;  // Note openclovis severity levels go to LOG_DEBUG+9, but via trial syslog on Linux accepts these higher levels
}
#else
#warning SAFplus and syslog log severity constants are not the same. Using slow translation table to convert them.
int logLevel2SyslogLevel(int ocll)
{
  switch (ocll)
    {
    case CL_LOG_SEV_EMERGENCY: return LOG_EMERG;
    case CL_LOG_SEV_ALERT: return LOG_ALERT;
    case CL_LOG_SEV_CRITICAL: return LOG_CRIT;
    case CL_LOG_SEV_ERROR: return LOG_ERR;
    case CL_LOG_SEV_WARNING: return LOG_WARNING;
    case CL_LOG_SEV_NOTICE: return LOG_NOTICE;
    case CL_LOG_SEV_INFO: return LOG_INFO;
    case CL_LOG_SEV_DEBUG: return LOG_DEBUG:
    default: return LOG_DEBUG;      
    }
}
#endif

int getFileIdx(std::string filePath, std::string fileName)
{
  int fileIdx = 0;
  int lastSlashPos,extLogPos,fnIdx;
  std::string strIdx;  
  int foundIdx = filePath.rfind(fileName);
  if (foundIdx>=0 && foundIdx<filePath.length())
  {                
    lastSlashPos = filePath.rfind("/");
    extLogPos = filePath.rfind(".log");
    fnIdx = filePath.find(fileName, lastSlashPos);
    if (fnIdx >= 0 && fnIdx < filePath.length())
    {
      strIdx = filePath.substr(fnIdx+fileName.length(), extLogPos-(fnIdx+fileName.length()));
    }
    fileIdx = atoi(strIdx.c_str());      
  }
  return fileIdx;
}

void streamRotationInit(Stream* s)
{
    file_result_set_t file_result_set;
    string fpath = s->fileLocation.value;
    if (fpath[0] != '/')  // If the location begins with a /, it is an absolute directory.  
    { // If it is a relative directory, prepend ASP_LOGDIR
      Dbg("path [%s] is invalid. Trying to use ASP_LOGDIR or current directory\n", fpath.c_str());
      if (SAFplus::ASP_LOGDIR[0] != 0)
        s->filePath = SAFplus::ASP_LOGDIR;
      else
        {
        char tmp[1024];
        s->filePath = getcwd(tmp,1024);
        }
      if ((s->filePath.length()>0)&& (s->filePath.at( s->filePath.length() - 1 ) != '/')) s->filePath.append("/");  // Be tolerant of filepath ending in / or not.
      s->filePath.append(fpath);
    }
    else
    {
      s->filePath = fpath;
    }

    // Now make sure that the log directory exists.  If it does not exist, create it.  If it cannot be created, give up logging to this stream.
    std::string& pathToFile = s->filePath;
    if (!fs::exists(pathToFile))
    {
      try
        {
        fs::create_directories(pathToFile);
        }
      catch (boost::filesystem::filesystem_error &ex)
        {
        Dbg("path [%s] is invalid; ASP_LOGDIR may not be set. System error [%s]\n", pathToFile.c_str(), ex.what());
        s->fp = NULL;
        s->fileIdx = -1;
        s->earliestIdx = -1;
        s->numFiles = -1;
        return; // if this filepath is invalid, pass it by and continue handling other streams
        }
    }

    /* The purpose is to find the last modified log file, get its index then calculate the next index for a new file.  

       First we need to separate out the log files that are associated with this stream (verses other streams or random files).  Logs associated with this stream have a name with the following format <pathname><fileName><Index>.log.  We search the directory for all filenames matching this format.  Next, these files are put in the file_result_set.  This map will sort all elements automatically based on modified time.  We use this set to do things like delete the oldest file and create a new one.
    */
    int fileIdx = 0;
    int lastSlashPos,extLogPos,fnIdx;
    std::string strIdx;
    int foundIdx;

    if (s->fileFullAction == FileFullAction::ROTATE || s->fileFullAction == FileFullAction::WRAP)
      {
        fs::directory_iterator end_iter;
        for( fs::directory_iterator dir_iter(pathToFile) ; dir_iter != end_iter ; ++dir_iter)
        {
          if (!fs::is_regular_file(dir_iter->status())) continue;  // skip any sym links, etc.  These can't be log files.

          // Extract just the file name by bracketing it between the preceding / and the file extension
          std::string filePath = dir_iter->path().string();
          // skip ahead to the last / so a name like /var/log/log1.log works
          lastSlashPos = filePath.rfind("/");
          fnIdx = filePath.find(s->fileName, lastSlashPos);
          if (fnIdx >= 0 && fnIdx < filePath.length())
          {
            extLogPos = filePath.rfind(".log"); // Find the extension because the file index is bracketed between the fnIdx and the extension.
            strIdx = filePath.substr(fnIdx+s->fileName.value.length(), extLogPos-(fnIdx+s->fileName.value.length()));
          }
          if (strIdx.length()>0)  // The file has an index
          {
            try 
            {
              fileIdx = boost::lexical_cast<unsigned>(strIdx);
              file_result_set.insert(file_result_set_t::value_type(fs::last_write_time(dir_iter->path()), dir_iter->path()));
            }
            catch(...)
            {
              Dbg("[%s] is not safplus log, ignore it\n", filePath.c_str());
            }
            strIdx.clear();
          }              
        }
#if 0 // for debugging
            {
             file_result_set_t::iterator it;
             for (it=file_result_set.begin(); it!=file_result_set.end(); ++it)
             std::cout << (*it).first << " => " << (*it).second << '\n';
            }
#endif

      s->numFiles = file_result_set.size();
      if (s->numFiles > 0)
        {
        file_result_set_t::iterator it = file_result_set.begin();
        s->earliestIdx = getFileIdx((*it).second.string(), s->fileName);
        file_result_set_t::reverse_iterator rit = file_result_set.rbegin();
        std::string temp = (*rit).second.string();
        s->fileIdx = getFileIdx(temp, s->fileName);
        }
      else
        {
          s->earliestIdx = 0;
          s->fileIdx = 0;
        }
      
    }
    // reset the map for processing other log stream
    file_result_set.clear();
}

void initializeStream(Stream* s)
{
    s->lastUpdate = beat;
    streamRotationInit(s);
    //Dbg("Initializing stream %s file: %s location: %s\n", s->name.value.c_str(),s->fileName.value.c_str(),s->fileLocation.value.c_str());

    if (s->filePath.length() > 0)
    {
      std::string fname(s->filePath +  "/" + s->fileName.value + boost::lexical_cast<std::string>(s->fileIdx) + ".log");

      // Due to a strange quirk of C, opening a file with mode "a" causes fseek to never work (write pointer is ALWAYS at the end of the file).
      // So we have to open the file using this 2 step mechanism.
      if (fs::exists(fname))
        {
        s->fp = fopen(fname.c_str(),"r+");
        fseek(s->fp, 0L, SEEK_END);  // Append new logs onto the end of the file
        }
      else
        {
        s->fp = fopen(fname.c_str(),"w");
        if (s->fp)
          {
          s->numFiles++;
          }
        }

      //Dbg("Opening file: %s %s\n", fname.c_str(), (s->fp) ? "OK":"FAILED");
      if (!s->fp)
      {
        //Dbg("Opening file: %s FAILED. Errno [%d]. Error message [%s]\n", fname.c_str(), errno, strerror(errno));
      }
    }
}

void addStreamObjMapping(const char* streamName, Stream* s, Handle strmHdl)
{
  // sys and app stream have their own wellknown handle, so other streams must register a handle
  Handle streamHdl;
  // GAS TODO: do we have to register with name so other processes can access this stream?
  bool registerWithName = (s->streamScope != StreamScope::LOCAL);
  
  if (strcmp(streamName,"sys") == 0)
  {
    streamHdl = SYS_LOG;  
  }
  else if (strcmp(streamName,"app") == 0)
  {
    streamHdl = APP_LOG;  
  }
  else
  {
    if (strmHdl==INVALID_HDL) // user doesn't provide streamHandle, so create a new one
    {
      streamHdl = Handle::create();
    }
    else
    {
#ifdef SAFPLUS_CLUSTERWIDE_LOG
      streamHdl = strmHdl;
      // check whether the handle provided registered with Name or not
      try 
      {
        Handle& temp = name.getHandle(streamName);
        if (streamHdl == temp) // Handle was registered with Name, so don't need to register again
        {
          registerWithName = false;
        }
      }
      catch(NameException& e)
      {
        Dbg("addStreamObjMapping > getHandle got exception [%s]\n", e.what());
      }
#endif
    }
  }

#ifdef SAFPLUS_CLUSTERWIDE_LOG
  // Register the stream handle with Name, so that user can use stream name to look up the stream handle by using Name
  if (registerWithName)
  {
    name.append(streamName, streamHdl, NameRegistrar::MappingMode::MODE_NO_CHANGE);
  }
  // Create group for this log stream, so that any app can subscribe to receive logs from this stream
  if (s->replicate != Replicate::NONE)
  {
    Handle grpHdl = streamHdl.getSubHandle(1);
    s->group.init(grpHdl);
    // Make a mapping of this stream with handle so that it can be used later
    hsMap[streamHdl] = s;
  }
#endif
}

Stream* createStreamCfg(const char* nam, const char* filename, const char* location, unsigned long int fileSize, unsigned long int logRecSize, SAFplusLog::FileFullAction fullAction, int numFilesRotate, int flushQSize, int flushInterval,bool syslog,SAFplusLog::StreamScope scope, Replicate repMode=Replicate::NONE, Handle strmHdl=INVALID_HDL)
{
  Stream* s = new Stream();
  s->setName(nam);
  s->setFileName(filename);
  s->setFileLocation(location);
  s->fileUnitSize = fileSize;
  s->recordSize = logRecSize;
  s->setFileFullAction(fullAction);
  s->maximumFilesRotated = numFilesRotate;
  s->flushFreq = flushQSize;
  s->flushInterval = flushInterval;
  s->syslog = syslog;
  s->setStreamScope(scope);
  s->setReplicate(repMode);  
  s->numLogs = 0;
  addStreamObjMapping(nam, s, strmHdl);
  return s;
}

void loadStreamConfigs()
{
  logCfg.read();
}

/* Initialization code would load the configuration from the database rather than setting it by hand.
 */
SAFplusLog::SAFplusLogModule* loadLogCfg(MgtDatabase* db)
{
  logCfg.setDatabase(db);
  loadStreamConfigs();

  Stream* s =  dynamic_cast<Stream*>(logCfg.safplusLog.streamConfig.streamList.getChildObject("sys"));
  if (!s)  // The sys log is an Openclovis system log.  So if its config does not exist, or was deleted, recreate the log.
    {
      s = createStreamCfg("sys","sys","/var/log/safplus",32*1024*1024, 2048, FileFullAction::ROTATE, 10, 200, 500, false, StreamScope::LOCAL);
      std::string cfgName("sys");
      logCfg.safplusLog.streamConfig.streamList.addChildObject(s,cfgName);
    }
  else
    {
      addStreamObjMapping("sys", s, SYS_LOG);
    }
  s =  dynamic_cast<Stream*>(logCfg.safplusLog.streamConfig.streamList.getChildObject("app"));
  if (!s)  // The all log is an Openclovis system log.  So if its config does not exist, or was deleted, recreate the log.
    {
      s = createStreamCfg("app","app","/var/log/safplus",1024*1024/4, 2048, FileFullAction::ROTATE, 4, 200, 500, false, StreamScope::LOCAL);
      std::string cfgName("app");
      logCfg.safplusLog.streamConfig.streamList.addChildObject(s,cfgName);
    }
  else
    {
      addStreamObjMapping("app", s, APP_LOG);
    }

  return &logCfg;
}

Stream* loadOrCreateNewStream(const char* streamName, Replicate repMode=Replicate::NONE, Handle strmHdl=INVALID_HDL)
{
  Stream* s =  dynamic_cast<Stream*>(logCfg.safplusLog.streamConfig.streamList.getChildObject(streamName));
  if (!s)  // The sys log is an Openclovis system log.  So if its config does not exist, or was deleted, recreate the log.
    {
      s = createStreamCfg(streamName,streamName,"/var/log/safplus",32*1024*1024, 2048, FileFullAction::ROTATE, 10, 200, 500, false, StreamScope::GLOBAL, repMode, strmHdl);
      std::string cfgName(streamName);
      logCfg.safplusLog.streamConfig.streamList.addChildObject(s,cfgName);
    }
  else
    {
      addStreamObjMapping(streamName, s, strmHdl);
    }
  return s;
}

/*
On receiving log from other node, call this function with logRecv=true.
logRecv parameter indicates that this log is received from other nodes (true).
if logRecv==true, log must be written to this node AND do not forward it to others, 
otherwise, write to this node AND forward it to others
*/
void postRecord(SAFplusI::LogBufferEntry* rec, char* msg, SAFplusLog::SAFplusLogModule* cfg)
{
  if (rec->severity > SAFplus::logSeverity) return;  // don't log if the severity cutoff is lower than that of the log.  Note that the client also does this check.
  //Dbg("%s\n",msg);

  // Determine the stream
  Stream* strmCfg = NULL;
  // First check well known streams by hand
  if (rec->stream == APP_LOG) strmCfg = appStreamCfg;
  else if (rec->stream == SYS_LOG) strmCfg = sysStreamCfg;
  else  // Find it if its a dynamic stream
    {
      // The Stream configuration uses string names, but the shared memory uses handles.
      // The Name service will hold the name to handle mapping.  During Log service initialization, a handle to Stream* hash table should
      // be created using data in the Name service.  This hash table can be used to look up the data.
      // lookup the handle in the hastable to find the stream
      // Dbg("Dynamic stream: handle gotten from hashmap\n");
      strmCfg = hsMap[rec->stream];
      if (!strmCfg)
      {
        // Stream object not found. Load or create new string with the specified handle
        //Dbg("Stream object not found. Load or create new stream with the specified handle\n");
        // Try to get the stream name associated with this handle from Name
        try 
        {
          char* strmName = name.getName(rec->stream);
          //Dbg("Load or create new stream [%s]; handle [%" PRIx64 ":%" PRIx64 "]\n", strmName, rec->stream.id[0], rec->stream.id[1]);
          strmCfg = loadOrCreateNewStream(strmName, Replicate::ANY, rec->stream); // do we need to create new stream with the handle specified? Yes. But this stream may come from other process, the log server does not know about it, so how does the log server know if the stream's replicate config is NONE or other values? Here, Replicate::ANY is hardcoded.
          initializeStream(strmCfg);
          hsMap[rec->stream] = strmCfg;
        }
        catch(NameException& e)
        {
          Dbg("postRecord > getName got exception [%s]\n", e.what());
        }
      }
    }
  if (strmCfg == NULL)  // Stream is not identified
    {
      return;
    }

  strmCfg->dirty = true;  // We wrote something to this stream
  
  if (strmCfg->syslog)  // output this log to syslog
    {
      syslog(logLevel2SyslogLevel(rec->severity),"%s",msg);
    }

  if (strmCfg->fp)  // If the file handle is non zero, write the log to that file
    {
      // Dbg("DEBUG: %s\n",msg);  
      // Dbg("DEBUG: msgLen [%d]\n",(int) strlen(msg));  
      strmCfg->fileBuffer += msg;
      strmCfg->fileBuffer += "\n";
    }
  if (strmCfg->sendMsg)
    {
      strmCfg->msgBuffer += msg;
      strmCfg->msgBuffer += "\n";
    }
#if 0
  if ((strmCfg->replicate != Replicate::NONE) && (!logRecv) && (lastRec)) // This log is my own log and there is no record in our processing, so forward them to others
  {
    Dbg("Replicate to other nodes\n");
    logRep.logReplicate(rec->stream);
  }
#endif
}
