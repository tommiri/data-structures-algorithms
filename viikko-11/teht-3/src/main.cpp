#include <iostream>
#include "../include/Extended_queue.h"

int main()
{
    Extended_queue q{};
    q.append(1);
    q.append(2);
    q.append(3);

    Node front;
    q.retrieve(front);
    Node *p = new Node(front);

    while (p)
    {
        std::cout << p->entry << std::endl;
        p = p->next;
    }

    q.clear();

    return 0;
}
