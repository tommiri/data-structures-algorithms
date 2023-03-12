#pragma once

#include "LinkedList.h"

class Stack_LL
{
private:
    Node *top;

public:
    Stack_LL()
    {
        top = nullptr;
    }

    void push(int num);

    int pop();

    void display();
};