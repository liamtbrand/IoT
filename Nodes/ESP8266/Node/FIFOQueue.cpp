#include "Arduino.h"
#include "FIFOQueue.h"

FIFOQueue::FIFOQueue()
{
  _head = 0;
  _tail = 0;
}

void FIFOQueue::add(String data)
{
  _data[_head] = data;
  _head = (_head+1)%_length;
  if(_head == _tail){
    _tail = (_tail+1)%_length;
  }
}

_Bool FIFOQueue::hasNext()
{
  return _head != _tail;
}

String FIFOQueue::getNext()
{
  _lastTail = _tail;
  _tail = (_tail+1)%_length;
  return _data[_lastTail];
}
