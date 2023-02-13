#pragma once

#include "Error_code.h"

const int maxstack = 1000;
typedef int Stack_entry;

class Extended_stack
{
public:
    Extended_stack() : count(0), entry{}
    {
    };

    Error_code pop();

    Error_code push(const Stack_entry &item);

    Error_code top(Stack_entry &item) const;

    bool empty() const;

    void clear();

    bool full() const;

    int size() const;

private:
    int count;
    Stack_entry entry[maxstack];
};
