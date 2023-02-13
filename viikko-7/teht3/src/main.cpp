#include <iostream>
#include "../include/Extended_queue.h"
#include "../include/Extended_stack.h"

const int JANUARY_PRICE = 10;
const int APRIL_PRICE = 30;
const int JUNE_PRICE = 20;
const int SEPTEMBER_PRICE = 50;
const int NOVEMBER_PRICE = 30;

int fifo_method();

int lifo_method();

using std::cout;

int main()
{
    cout << "\nProfit using FIFO method: " << fifo_method() << " dollars\n";
    cout << "Profit using LIFO method: " << lifo_method() << " dollars\n";
    return 0;
}

int fifo_method()
{
    Extended_queue shares;

    // Buying in January
    for (int i = 0; i < 100; i++)
    {
        shares.append(JANUARY_PRICE);
    }

    // Buying in April
    for (int i = 0; i < 100; i++)
    {
        shares.append(APRIL_PRICE);
    }

    // Buying in September
    for (int i = 0; i < 100; i++)
    {
        shares.append(SEPTEMBER_PRICE);
    }

    int profit{}, boughtFor{};

    // Selling in June
    for (int i = 0; i < 100; i++)
    {
        shares.serve_and_retrieve(boughtFor);
        profit += (JUNE_PRICE - boughtFor);
    }

    // Selling in November
    for (int i = 0; i < 100; i++)
    {
        shares.serve_and_retrieve(boughtFor);
        profit += (NOVEMBER_PRICE - boughtFor);
    }

    return profit;
}

int lifo_method()
{
    Extended_stack shares;

    // Buying in January
    for (int i = 0; i < 100; i++)
    {
        shares.push(JANUARY_PRICE);
    }

    // Buying in April
    for (int i = 0; i < 100; i++)
    {
        shares.push(APRIL_PRICE);
    }

    // Buying in September
    for (int i = 0; i < 100; i++)
    {
        shares.push(SEPTEMBER_PRICE);
    }

    int profit{}, boughtFor{};

    // Selling in June
    for (int i = 0; i < 100; i++)
    {
        shares.top(boughtFor);
        profit += (JUNE_PRICE - boughtFor);
        shares.pop();
    }

    // Selling in November
    for (int i = 0; i < 100; i++)
    {
        shares.top(boughtFor);
        profit += (NOVEMBER_PRICE - boughtFor);
        shares.pop();
    }

    return profit;
}

