#include "../include/Extended_stack.h"

Error_code Extended_stack::pop()
{
    Error_code outcome = success;
    if (count == 0)
    {
        outcome = underflow;
    }
    else
    {
        --count;
    }
    return outcome;
}

Error_code Extended_stack::push(const Stack_entry &item)
{
    Error_code outcome = success;
    if (count >= maxstack)
    {
        outcome = overflow;
    }
    else
    {
        entry[count++] = item;
    }
    return outcome;
}

Error_code Extended_stack::top(Stack_entry &item) const
{
    Error_code outcome = success;
    if (count == 0)
    {
        outcome = underflow;
    }
    else
    {
        item = entry[count - 1];
    }
    return outcome;
}

bool Extended_stack::empty() const
{
    bool outcome = true;
    if (count > 0)
    {
        outcome = false;
    }
    return outcome;
}

void Extended_stack::clear()
{
    while (count > 0)
    {
        pop();
    }
}

bool Extended_stack::full() const
{
    return count >= maxstack;
}

int Extended_stack::size() const
{
    return count;
}

