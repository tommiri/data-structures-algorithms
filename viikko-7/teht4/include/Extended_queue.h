#pragma once

#include "./Queue.h"

class Extended_queue : public Queue
{
public:
    Extended_queue();

    int size() const;

    void clear();

    bool full() const;

    Error_code serve_and_retrieve(Queue_entry &item);
};
