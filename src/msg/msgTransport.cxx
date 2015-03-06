#include <clMsgTransportPlugin.hxx>


namespace SAFplus
  {

  void Message::setAddress(const Handle& h)
    {
    node = h.getNode();
    port = h.getPort();
    }

  MsgFragment* Message::prepend(uint_t size)
    {
      MsgFragment* f = msgPool->allocMsgFragment(size);
      assert(f);
      f->nextFragment = firstFragment;
      firstFragment = f;
      if (!lastFragment) lastFragment = f;  // If this is the very first message fragment
      return f;
    }

  MsgFragment* Message::append(uint_t size)
    {
      MsgFragment* f = msgPool->allocMsgFragment(size);
      assert(f);
      if (!lastFragment) { lastFragment = f; firstFragment = f; }  // This is the first fragment
      else
        {
        lastFragment->nextFragment = f;
        lastFragment = f;
        }
      return f;
    }

  MsgFragment* MsgPool::allocMsgFragment(uint_t size)
    {
      MsgFragment* ret = NULL;
      if (size == 0)
        {
        ret = (MsgFragment*) SAFplusHeapAlloc(sizeof(MsgFragment));
        assert(ret);
        ret->constructPointerFrag();
        }
      else
        {
        ret = (MsgFragment*) SAFplusHeapAlloc(sizeof(MsgFragment) + size);  // actually could be size - sizeof(void*) because we'll use the buffer variable data itself
        assert(ret);
        ret->constructInlineFrag(size);
        }
      return ret;
    }

  void MsgFragment::set(const char* buf)
    {
    if (flags & PointerFragment)
      {
      start  = 0;
      len    = strlen(buf)+1;  // Include the NULL termination 
      buffer = (void*) buf;
      }
    else if (flags & InlineFragment)
      {
      clDbgNotImplemented("assignment into an inline frag");
      }
    else
      {
      assert(!"Message fragment corrupt");
      }
    }

  void MsgFragment::set(void* buf,uint_t length)
    {
    if (flags & PointerFragment)
      {
      start  = 0;
      len    = length;  // Include the NULL termination 
      buffer = (void*) buf;
      }
    else if (flags & InlineFragment)
      {
      clDbgNotImplemented("assignment into an inline frag");
      }
    else
      {
      assert(!"Message fragment corrupt");
      }
    }



  void* MsgFragment::data(int offset)
    {
    if (flags & PointerFragment)
      {
      return (void*) (((char*) buffer)+offset+start);
      }
    else if (flags & InlineFragment)
      {
      assert(offset+start < allocatedLen);
      return (void*) (((char*) &buffer)+offset+start);
      }
    }

  const void* MsgFragment::read(int offset)
    {
    assert(offset < len);  // not offset+start because the len does not include start
    if (flags & PointerFragment)
      {
      return (void*) (((char*) buffer)+offset+start);
      }
    else if (flags & InlineFragment)
      {
      return (void*) (((char*) &buffer)+offset+start);
      }
    }




  Message* MsgPool::allocMsg()
    {
    Message* msg = (Message*) SAFplusHeapAlloc(sizeof(Message));
    assert(msg);
    msg->initialize();
    msg->msgPool = this;
    return msg;
    }

  void MsgPool::free(Message* next)
    {
    Message* msg;
    MsgFragment* nextFrag;
    MsgFragment* frag;
    do {
       msg = next;
       next = msg->nextMsg;  // Save the next message so we can delete it next

       nextFrag = msg->firstFragment;
       do {
          frag = nextFrag;
          nextFrag = frag->nextFragment;

          // First clean up the buffer if needed
          if (frag->flags & MsgFragment::Flags::DataSAFplusFree) SAFplusHeapFree(frag->buffer);
          else if (frag->flags & MsgFragment::Flags::DataMsgPoolFree) SAFplusHeapFree(frag->buffer);  // TODO: hold the fragments in lists in the message pool
          else if (frag->flags & MsgFragment::Flags::DataCustomFree) { clDbgNotImplemented("custom free logic"); }  // Should the custom free function be per fragment or per message?

          // Next clean up the fragment itself
          if (frag->flags & MsgFragment::Flags::SAFplusFree) SAFplusHeapFree(frag);
          else if (frag->flags & MsgFragment::Flags::MsgPoolFree) SAFplusHeapFree(frag);  // TODO: hold the fragments in lists in the message pool
          else if (frag->flags & MsgFragment::Flags::CustomFree) { clDbgNotImplemented("custom fragment free logic"); }

          } while(nextFrag);

       // Ok all frags cleaned up so delete this message
       SAFplusHeapFree(msg);
      } while (next != NULL);
    }


  MsgSocket::~MsgSocket()
  {}


  void MsgTransportPlugin_1::registerWatcher(Wakeable* watcher)
    {
    // This is implemented as an expanding array of pointers.
    // registration and unregistration occurs rarely so performance is not an issue.
    // But speed iterating thru the notification list is.

    for(int i=0;i<numWatchers;i++)
      {
      if (watchers[i] == nullptr) 
        {
        watchers[i] = watcher;
        return;
        }
      if (watchers[i] == watcher)
        {
        return;
        }
      }
    uint_t newNum = numWatchers + 4;
    Wakeable** tmp = (Wakeable**) SAFplusHeapAlloc(newNum * sizeof(Wakeable*));
    assert(tmp);
    memcpy(tmp,watchers,numWatchers *sizeof(Wakeable**));
    tmp[numWatchers] = watcher;
    for(int i=numWatchers+1;i<newNum;i++)
      {
      tmp[i] = nullptr;
      }
    SAFplusHeapFree(watchers);
    watchers = tmp;
    numWatchers = newNum;
    }

  void MsgTransportPlugin_1::unregisterWatcher(Wakeable* watcher)
    {
    for(int i=0;i<numWatchers;i++)
      {
      if (watchers[i] == watcher)
        {
        watchers[i] = nullptr;
        // It should be impossible for the same watcher to be in the list more than once but I'll look thru the whole list just to be safe.
        }
      }
    }

  };