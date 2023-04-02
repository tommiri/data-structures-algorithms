#include "../include/Queue.h"

Queue::Queue()
{
    front = rear = nullptr;
}

Error_code Queue::append(const Queue_entry &item)
/*
Post: Add item to the rear of the Queue and return a code of success
      or return a code of overflow if dynamic memory is exhausted.
*/
{
    Node *new_rear = new Node(item);
    if (new_rear == nullptr)
    {
        return overflow;
    }
    if (rear == nullptr)
    {
        front = rear = new_rear;
    }
    else
    {
        rear->next = new_rear;
        rear = new_rear;
    }
    return success;
}

Error_code Queue::serve()
/*
Post: The front of the Queue is removed.  If the Queue
      is empty, return an Error_code of underflow.
*/
{
    if (front == nullptr)
    {
        return underflow;
    }
    Node *old_front = front;
    front = old_front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete old_front;
    return success;
}


bool Queue::empty() const
{
    return (front == nullptr && rear == nullptr);
}

Error_code Queue::retrieve(Queue_entry &item) const
{
    if (front)
    {
        item = *front;
        return success;
    }
    else
    {
        return fail;
    }
}

Queue::~Queue()
{
    while (front)
    {
        Node *old_front = front;
        front = old_front->next;
        delete old_front;
    }
}

Queue::Queue(const Queue &original)
{
    front = original.front;
    rear = original.rear;
}

Queue &Queue::operator=(const Queue &original)
{
    front = rear = nullptr;
    Node *p = original.front;
    while (p)
    {
        append(p->entry);
        p = p->next;
    }

    return *this;
}
