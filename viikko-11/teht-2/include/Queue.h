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

    Error_code append(const Queue_entry &item);

    Error_code serve();

    Error_code retrieve(Queue_entry &item) const;

    //  safety features for linked structures
    ~Queue();

    Queue(const Queue &original);

    Queue &operator=(const Queue &original);

protected:
    Node *front, *rear;
};