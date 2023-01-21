#include "../include/Life.h"
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <math.h>

using std::cout, std::cin, std::cerr, std::ifstream, std::ofstream;

void Life::initialize()
{
    char option{};
    bool error{};

    cout << "Animation frames: ";
    cin >> animationFrames;
    cout << "Animation delay (in seconds): ";
    cin >> animationDelay;
    cin.ignore();

    do
    {
        error = false;

        cout << "Select 'i' to input game configuration yourself or select 'r' to "
                "read configuration from a file.\n";
        cin >> option;
        cin.ignore();

        switch (option)
        {
            case 'i':
                readFromInput();
                break;
            case 'r':
                readFromFile();
                break;
            default:
                error = true;
                cout << "ERROR: Invalid option.\n";
        }
    } while (error);
}

void Life::readFromInput()
{
    string input{};
    cout << "Enter the initial grid configuration (x for alive, blank for "
            "dead):\n";

    for (int row = 0; row < maxRow; row++)
    {
        cout << "Enter row " << row + 1 << ": ";
        getline(cin, input);
        parseLine(input, row);
    }
}

void Life::readFromFile()
{
    string fileName{};
    cout << "Enter file path: ";
    getline(cin, fileName);
    cout << fileName << '\n';

    ifstream file(fileName);

    if (!file)
    {
        cerr << "ERROR: File could not be opened\n";
        file.close();
        exit(1);
    }

    string line{};
    getline(file, line); // Skip first line
    for (int row = 0; getline(file, line); row++)
    {
        parseLine(line, row);
    }
    file.close();
}

void Life::parseLine(string input, const int &row)
{
    for (int col = 0; col < maxCol; col++)
    {
        if (col < input.size() && input.at(col) == 'x')
        {
            grid[row][col] = 1;
        }
        else
        {
            grid[row][col] = 0;
        }
    }
}

void Life::update()
{
    vector<vector<int>> new_grid(maxRow, vector<int>(maxCol, 0));

    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            switch (neighbor_count(row, col))
            {
                case 2:
                    new_grid[row][col] = grid[row][col]; //  Status stays the same.
                    break;
                case 3:
                    new_grid[row][col] = 1; //  Cell is now alive.
                    break;
                default:
                    new_grid[row][col] = 0; //  Cell is now dead.
            }
        }
    }

    grid = new_grid;
}

int Life::neighbor_count(int row, int col)
{
    int count = 0;

    int lowerRow = row == 0 ? row : row - 1;
    int upperRow = row == maxRow - 1 ? row : row + 1;
    int lowerCol = col == 0 ? col : col - 1;
    int upperCol = col == maxCol - 1 ? col : col + 1;

    for (int i = lowerRow; i <= upperRow; i++)
    {
        for (int j = lowerCol; j <= upperCol; j++)
        {
            count += grid[i][j];
        }
    } //  Increase the count if neighbor is alive.
    count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
    return count;
}

void Life::askRowsAndCols()
{
    cout << "\nHow many rows?\n";
    cin >> maxRow;
    cout << "How many columns?\n";
    cin >> maxCol;
    cin.ignore();

    grid.resize(maxRow, vector<int>(maxCol, 0));
}

void Life::print()
{
    for (const auto &row: grid)
    {
        for (int col: row)
        {
            cout << (col == 1 ? 'x' : ' ');
        }
        cout << '\n';
    }
    cout << '\n';
}

void Life::instructions()
{
    cout << "Welcome to Conway's Game of Life.\n";
    cout << "This game uses a grid of size in which each cell \n";
    cout << "can either be occupied by an organism or not.\n";
    cout << "The occupied cells change from generation to generation\n";
    cout << "according to the number of neighboring cells which are alive.\n";
}

void Life::writeConfToFile()
{
    string fileName{};
    cout << "What would you like to name your .txt file?\n";
    getline(cin, fileName);
    fileName += ".txt";

    ofstream file(fileName);

    if (!file)
    {
        cout << "ERROR: Opening/creating file failed.\n";
        exit(1);
    }

    file << "Final configuration of Game of Life\n";
    for (const auto &row: grid)
    {
        for (int column: row)
        {
            file << (column == 1 ? 'x' : ' ');
        }
        file << '\n';
    }

    cout << "Successfully saved configuration to " << fileName << "!\n";
}

void Life::animate()
{
    for (int i = 0; i < animationFrames; i++)
    {
        system("clear");
        print();
        update();
        usleep(animationDelay * pow(10, 6));
    }
}


