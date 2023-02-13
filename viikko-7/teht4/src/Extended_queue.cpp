#include "../include/Extended_queue.h"

Extended_queue::Extended_queue()
{
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}

int Extended_queue::size() const
{
    return count;
}

void Extended_queue::clear()
{
    while (!empty())
    {
        serve();
    }
}

bool Extended_queue::full() const
{
    return count >= maxqueue;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
{
    if (count <= 0)
    {
        return underflow;
    }
    item = entry[front];
    count--;
    entry[front] = 0;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}
