#pragma once

#include "Plane.h"
#include "Error_code.h"

const int maxqueue = 10;
typedef Plane Queue_entry;

class Queue
{
public:
    Queue ();

    bool empty () const;

    Error_code serve ();

    Error_code append (const Queue_entry &item);

    Error_code retrieve (Queue_entry &item) const;

    int size () const;

    void clear ();

    bool full () const;

    Error_code serve_and_retrieve (Queue_entry &item);

protected:
    int count;
    int front, rear;
    Queue_entry entries[maxqueue];
};