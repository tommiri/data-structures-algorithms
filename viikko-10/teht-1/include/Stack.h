#pragma once

#include "Error_code.h"

const int maxstack = 20;
typedef double Stack_entry;

class Stack
{
public:
    Stack() : count(0), entry{}
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
