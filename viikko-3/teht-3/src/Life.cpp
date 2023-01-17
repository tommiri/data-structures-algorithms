#include "../include/Life.h"
#include <iostream>
using namespace std;

void Life::initialize()
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/
{
    int row, col;
    cout << "List the coordinates for living cells." << endl;
    cout << "Terminate the list with the special pair -1 -1" << endl;
    cin >> row >> col;

    while (row != -1 || col != -1)
    {
        if (row >= 0 && row < maxRow)
            if (col >= 0 && col < maxCol)
                grid[row][col] = 1;
            else
                cout << "Column " << col << " is out of range." << endl;
        else
            cout << "Row " << row << " is out of range." << endl;
        cin >> row >> col;
    }
}

void Life::update()
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/

{
    int row, col;
    vector<vector<int>>new_grid(maxRow, vector<int>(maxCol, 0));

    for (row = 0; row < maxRow; row++)
        for (col = 0; col < maxCol; col++)
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

    grid = new_grid;
}

int Life::neighbor_count(int row, int col)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/

{
    int i, j;
    int count = 0;

    int lowerRow = row == 0 ? row : row - 1;
    int upperRow = row == maxRow - 1? row : row + 1;
    int lowerCol = col == 0 ? col : col - 1;
    int upperCol = col == maxCol - 1 ? col : col + 1;

    for (i = lowerRow; i <= upperRow; i++)
        for (j = lowerCol; j <= upperCol; j++)
            count += grid[i][j]; //  Increase the count if neighbor is alive.
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

    grid.resize(rows, vector<int>(cols, 0));

    maxRow = rows;
    maxCol = cols;
}

void Life::print()
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
    int row, col;
    cout << "\nThe current Life configuration is:" << endl;
    for (row = 0; row < maxRow; row++)
    {
        for (col = 0; col < maxCol; col++)
            if (grid[row][col] == 1)
                cout << '*';
            else
                cout << ' ';
        cout << endl;
    }
    cout << endl;
}

void Life::instructions()
{
    cout << "Welcome to Conway's game of Life." << endl;
    cout << "This game uses a grid of size "
         << maxRow << " by " << maxCol << " in which" << endl;
    cout << "each cell can either be occupied by an organism or not." << endl;
    cout << "The occupied cells change from generation to generation" << endl;
    cout << "according to the number of neighboring cells which are alive."
         << endl;
}
