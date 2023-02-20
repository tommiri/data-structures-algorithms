#include <iostream>
#include <string>

#include "../include/Extended_queue.h"

using std::cout, std::cin, std::string;

char checkString(const string &);

int main()
{
    string input{};

    cout << "Please enter two strings separated by a colon (e.g. 'Left:Right').\n";

    getline(cin, input);

    cout << input << ' ' << checkString(input);

    return 0;
}

char checkString(const string &str)
{
    // If no colon is found in string
    if (str.find(':') == string::npos)
    {
        return 'N';
    }

    string leftString = str.substr(0, str.find(':'));
    string rightString = str.substr(str.find(':') + 1, string::npos);
    Extended_queue leftPortion{};
    char queue_entry{};
    bool matching = true;

    for (char c: leftString)
    {
        // Append left string's characters to queue
        leftPortion.append(c);
    }

    for (char c: rightString)
    {
        // If queue is empty while string still has characters left
        if (leftPortion.empty())
        {
            return 'R'; // Right is longer than left
        }

        leftPortion.serve_and_retrieve(queue_entry);

        // If at any point c doesnt match queue_entry, strings can't be matching
        if (c != queue_entry)
        {
            matching = false;
        }
    }

    // If after loop matching is still true
    if (matching)
    {
        return 'S'; // Strings are matching
    }

    // If queue is empty after loop ending
    if (leftPortion.empty())
    {
        return 'D'; // Both strings are the same length
    }
    else
    {
        // If queue is not empty, left string is longer
        return 'L';
    }
}