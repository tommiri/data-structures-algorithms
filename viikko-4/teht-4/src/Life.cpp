#include "../include/Life.h"
#include <iostream>
#include <string>

using std::cout, std::cin, std::string;

void Life::initialize()
{
    string input{};
    cout << "Enter the initial grid configuration (x for alive, blank for "
            "dead):\n";

    for (int row = 0; row < maxRow; row++)
    {
        cout << "Enter row " << row + 1 << ": ";
        getline(cin, input);
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
}

void Life::update()
{
    int row, col;
    vector<vector<int>> new_grid(maxRow, vector<int>(maxCol, 0));

    for (row = 0; row < maxRow; row++)
    {
        for (col = 0; col < maxCol; col++)
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
    int i, j;
    int count = 0;

    int lowerRow = row == 0 ? row : row - 1;
    int upperRow = row == maxRow - 1 ? row : row + 1;
    int lowerCol = col == 0 ? col : col - 1;
    int upperCol = col == maxCol - 1 ? col : col + 1;

    for (i = lowerRow; i <= upperRow; i++)
    {
        for (j = lowerCol; j <= upperCol; j++)
        {
            count += grid[i][j];
        }
    } //  Increase the count if neighbor is alive.
    count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
    return count;
}

void Life::askRowsAndCols()
{
    int rows, cols;
    cout << "How many rows?\n";
    cin >> rows;
    cout << "How many columns?\n";
    cin >> cols;
    cin.ignore();

    grid.resize(rows, vector<int>(cols, 0));

    maxRow = rows;
    maxCol = cols;
}

void Life::print()
{
    int row, col;
    cout << "\nThe current Life configuration is:\n";
    for (row = 0; row < maxRow; row++)
    {
        for (col = 0; col < maxCol; col++)
        {
            if (grid[row][col] == 1)
            {
                cout << 'x';
            }
            else
            {
                cout << ' ';
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

void Life::instructions()
{
    cout << "Welcome to Conway's game of Life.\n";
    cout << "This game uses a grid of size " << maxRow << " by " << maxCol
         << " in which\n";
    cout << "each cell can either be occupied by an organism or not.\n";
    cout << "The occupied cells change from generation to generation\n";
    cout << "according to the number of neighboring cells which are alive.\n";
}


