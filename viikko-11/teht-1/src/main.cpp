#include <iostream>
#include "../include/Queue.h"

int main()
{
    Queue q{};
    q.append(1);
    q.append(2);
    q.append(3);

    Queue q2;
    q2 = q;
    q2.append(4);

    Node n{};
    while (!q.empty())
    {
        q.retrieve(n);
        std::cout << n.entry << std::endl;
        q.serve();
    }
    while (!q2.empty())
    {
        q2.retrieve(n);
        std::cout << n.entry << std::endl;
        q2.serve();
    }

    return 0;
}
