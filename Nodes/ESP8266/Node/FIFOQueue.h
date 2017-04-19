
// IMPORTANT: Will drop old messages.

// TODO : Make this use char* instead of String. Help avoid stack fragmentation.

#include "Arduino.h"

#ifndef FIFOQueue_h
#define FIFOQueue_h

class FIFOQueue
{
  public:
    FIFOQueue();

    _Bool hasNext();
    String getNext();
    void add(String data);

  private:
    static const int _length = 8;
    static const int _size = 16;

    String _data[_length];

    int _head;
    int _tail;
    int _lastTail;

};

#endif
