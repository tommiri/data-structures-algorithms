#include <iostream>
#include "../include/Extended_queue.h"

void help();

using std::cout, std::cin;

int main()
{
    Extended_queue queue;
    help();
    bool isRunning{true};

    while (isRunning)
    {
        char option{};
        cout << "Enter command: ";
        cin >> option;

        switch (tolower(option))
        {
            case 'a':
                char c;
                cout << "Character to append: ";
                cin >> c;
                queue.append(c);
                break;
            case 's':
                cout << "Serving front of queue...\n";
                queue.serve();
                break;
            case 'r':
                char retrievedChar;
                queue.retrieve(retrievedChar);
                cout << "Retrieved entry from queue: " << retrievedChar << '\n';
                break;
            case '#':
                cout << "The current size of the queue is " << queue.size() << '\n';
                break;
            case 'c':
                cout << "Clearing queue...\n";
                queue.clear();
                break;
            case 'p':
                for (int i = 0; i < queue.size(); i++)
                {
                    char entry;
                    queue.serve_and_retrieve(entry);
                    cout << entry << ' ';
                    queue.append(entry);
                }
                cout << '\n';

                break;
            case 'h':
                help();
                break;
            case 'q':
                isRunning = false;
                break;
            default:
                cout << "Invalid option!\n";
        }
    }

    return 0;
}

void help()
/*
Post: A help screen for the program is printed, giving the meaning of each
      command that the user may enter.
*/

{
    cout << "\nThis program allows the user to enter one command\n"
         << "(but only one) on each input line.\n"
         << "For example, if the command S is entered, then\n"
         << "the program will serve the front of the queue.\n"

         << "\n The valid commands are:\n"
         << "A - Append the next input character to the extended queue\n"
         << "S - Serve the front of the extended queue\n"
         << "R - Retrieve and print the front entry.\n"
         << "# - The current size of the extended queue\n"
         << "C - Clear the extended queue (same as delete)\n"
         << "P - Print the extended queue\n"
         << "H - This help screen\n"
         << "Q - Quit\n"

         << "\nPress <Enter> to continue." << std::endl;

    char c;
    do
    {
        cin.get(c);
    } while (c != '\n');
}
