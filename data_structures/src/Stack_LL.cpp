#include <iostream>

#include "../include/Stack_LL.h"

using std::cout;

void Stack_LL::push(int num)
{
    Node *t = new Node;

    t->data = num;
    t->next = top;
    top = t;
}

int Stack_LL::pop()
{
    int value = -1;
    if (!top)
    {
        cout << "Stack is empty\n";
    }
    else
    {
        value = top->data;
        Node *t = top;
        top = top->next;
        delete t;
    }

    return value;
}

void Stack_LL::display()
{
    Node *p = top;

    while (p)
    {
        cout << p->data << ' ';
        p = p->next;
    }

    cout << '\n';
}