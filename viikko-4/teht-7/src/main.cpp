#include <iostream>

#include "../include/Life.h"

int main() //  Program to play Conway's game of Life.
{
    Life configuration;
    configuration.instructions();
    configuration.askRowsAndCols();
    configuration.initialize();
    configuration.animate();

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
