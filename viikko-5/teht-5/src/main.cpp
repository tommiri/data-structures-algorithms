#include "../include/Extended_stack.h"
#include <iostream>

int main()
{
    Extended_stack stack;

    while (!stack.full())
    {
        stack.push(1);
    }

    std::cout << "Stack size when full: " << stack.size() << "\n";
    stack.clear();
    std::cout << "Stack size after clearing: " << stack.size() << "\n";

    return EXIT_SUCCESS;
}