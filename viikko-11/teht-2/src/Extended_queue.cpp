#include "../include/Extended_queue.h"

int Extended_queue::size() const
/*
Post: Return the number of entries in the Extended_queue.
*/
{
    Node *window = front;
    int count = 0;
    while (window != nullptr)
    {
        window = window->next;
        count++;
    }
    return count;
}

bool Extended_queue::full() const
{
    return false; // Queue can never be full since using a linked list
}
