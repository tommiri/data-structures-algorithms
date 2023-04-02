#pragma once
#include "Error_code.h"
#include "Node.h"

typedef Node Queue_entry;

class Queue
{
public:
  //  standard Queue methods
  Queue();
  bool empty() const;
  int size() const;
  Error_code append(const Queue_entry &item);
  Error_code serve();
  Error_code retrieve(Queue_entry &item) const;
  //  safety features for linked structures
  ~Queue();
  Queue(const Queue &original);
  void operator=(const Queue &original);

protected:
  Node *front, *rear;
};