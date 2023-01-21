#include <iostream>

#include "../include/Utility.h"
#include "../include/Life.h"

int main() //  Program to play Conway's game of Life.
{
    Life configuration;
    configuration.askRowsAndCols();
    configuration.instructions();
    configuration.initialize();
    configuration.print();
    cout << "Continue viewing new generations? " << endl;
    while (user_says_yes())
    {
        configuration.update();
        configuration.print();
        cout << "Continue viewing new generations? " << endl;
    }

    char option{};
    cout << "Would you like to save your configuration to a file? (y/n)\n";
    cin >> option;
    cin.ignore();

    if (option == 'y' || option == 'Y')
    {
        configuration.writeConfToFile();
    }

    return EXIT_SUCCESS;
}
