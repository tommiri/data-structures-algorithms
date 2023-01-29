#include <stack>
#include <iostream>
#include <string>

using std::cout, std::cin, std::stack, std::string;

int main()
{
    string str{};
    stack<char> characters{};
    cout << "Type in a string of text.\n"
         << "The string will be printed in reverse order.\n";

    getline(cin, str);

    for (const char &c: str)
    {
        characters.push(c);
    }

    cout << "\n\n";

    string reverseStr{};

    while (!characters.empty())
    {
        reverseStr.push_back(characters.top());
        cout << characters.top();
        characters.pop();
    }

    cout << "\n";


    if (str == reverseStr)  // Case-sensitive, could transform both strings to lowercase for case-insensitive comparison
    {
        cout << str << " is a palindrome!\n";
    }

    return EXIT_SUCCESS;
}