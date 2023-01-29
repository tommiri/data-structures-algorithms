#include <stack>
#include <iostream>

using std::cout, std::cin, std::endl, std::stack;

int main()
{
    int n;
    double item;
    stack<double> numbers;
    cout << " Type in an integer n followed by n decimal numbers."
         << endl
         << " The numbers will be printed in reverse order."
         << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> item;
        numbers.push(item);
    }
    cout << endl << endl;
    while (!numbers.empty())
    {
        cout << numbers.top() << " ";
        numbers.pop();
    }
    cout << endl;
}