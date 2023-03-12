#pragma once

class Node
{
public:
    int data;
    Node *next;

    Node()
    {
    };

    Node(int d)
    {
        data = d;
        next = nullptr;
    }
};