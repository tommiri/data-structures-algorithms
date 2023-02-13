#pragma once

#include "Utility.h"

const int maxstack = 10;
typedef int Stack_entry;

class Stack
{
public:
    Stack() : count(0), entry{}
    {
    };

    Error_code pop();

    Error_code push(const Stack_entry &item);

    Error_code top(Stack_entry &item) const;

    Error_code copy_stack(Stack &dest, Stack &source);

    bool empty() const;

    void clear();

    bool full() const;

    int size() const;

private:
    int count;
    Stack_entry entry[maxstack];
};
