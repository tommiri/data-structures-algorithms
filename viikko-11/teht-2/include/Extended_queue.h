#pragma once

#include "Queue.h"

class Extended_queue : public Queue
{
public:
    bool full() const;

    int size() const;
};
