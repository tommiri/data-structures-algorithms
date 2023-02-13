#include <iostream>
#include "../include/Extended_queue.h"
#include "../include/Extended_stack.h"

Extended_queue stack_to_queue(Extended_stack stack);

Extended_stack queue_to_stack(Extended_queue queue);

Extended_stack addup_stacks_relative(Extended_stack stack1, Extended_stack stack2);

Extended_stack addup_stacks_reverse(Extended_stack stack1, Extended_stack stack2);

void reverseQueue(Extended_queue queue);

void reverseStack(Extended_stack stack);

using std::cout;

int main()
{
    Extended_stack stack;

    // Fill stack with numbers 0-99
    for (int i = 0; i < 10; i++)
    {
        stack.push(i);
    }

    Extended_queue queue_from_stack = stack_to_queue(stack);

    Extended_stack stack1;
    Extended_stack stack2;

    // Fill stack1 with numbers 0-99
    for (int i = 0; i < 10; i++)
    {
        stack1.push(i);
    }

    // Fill stack2 with numbers 99-0
    for (int i = 9; i >= 0; i--)
    {
        stack2.push(i);
    }

    return 0;
}

// Move all the entries from a Stack into a Queue.
Extended_queue stack_to_queue(Extended_stack stack)
{
    Extended_queue queue;
    while (!stack.empty())
    {
        int stack_entry{};
        stack.top(stack_entry);
        stack.pop();
        queue.append(stack_entry);
    }

    return queue;
}

// Move all the entries from a Queue onto a Stack.
Extended_stack queue_to_stack(Extended_queue queue)
{
    Extended_stack stack;
    while (!queue.empty())
    {
        int queue_entry{};
        queue.serve_and_retrieve(queue_entry);
        stack.push(queue_entry);
    }

    return stack;
}

/*  Empty one Stack onto the top of another Stack in such a way that the entries
    that were in the first Stack keep the same relative order. */
Extended_stack addup_stacks_relative(Extended_stack stack1, Extended_stack stack2)
{
    // Not sure how to implement this
}

/*  Empty one Stack onto the top of another Stack in such a way that the entries
    that were in the first Stack are in the reverse of their original order. */
Extended_stack addup_stacks_reverse(Extended_stack stack1, Extended_stack stack2)
{
    while (!stack1.empty())
    {
        int stack_entry{};
        stack1.top(stack_entry);
        stack1.pop();
        stack2.push(stack_entry);
    }

    return stack2;
}

// Use a local Stack to reverse the order of all the entries in a Queue.
void reverseQueue(Extended_queue &queue)
{
    Extended_stack stack = queue_to_stack(queue);
    queue = stack_to_queue(stack);
}

// Use a local Queue to reverse the order of all the entries in a Stack.
void reverseStack(Extended_stack &stack)
{
    Extended_queue queue = stack_to_queue(stack);
    stack = queue_to_stack(queue); // Don't think this works?
}