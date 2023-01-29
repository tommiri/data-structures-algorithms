#include <stack>
#include <iostream>

using std::cout, std::cin, std::stack;

int main()
{
    int num{};
    int previousNum{};
    stack<int> nums{};
    cout << "Type in a sequence of integers of increasing value.\n"
         << "The sequence will be printed out in decreasing order of value.\n"
         << "Input will terminate as soon as an integer that does not exceed its\n"
         << "predecessor in value is read.\n";

    while (true)
    {
        if (!nums.empty())
        {
            previousNum = nums.top();
        }

        cin >> num;

        if (num <= previousNum)
        {
            break;
        }

        nums.push(num);
    }

    while (!nums.empty())
    {
        cout << nums.top() << " ";
        nums.pop();
    }

    cout << "\n";

    return EXIT_SUCCESS;
}