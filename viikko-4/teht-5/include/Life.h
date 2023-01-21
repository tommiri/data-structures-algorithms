#ifndef VIIKKO_3_LIFE_H
#define VIIKKO_3_LIFE_H

#include <vector>
#include <string>

using std::vector, std::string;

class Life
{
public:
    void initialize();

    void print();

    void update();

    void askRowsAndCols();

    void instructions();

private:
    int maxRow;
    int maxCol;
    vector<vector<int>> grid; //  allows for two extra rows and columns

    int neighbor_count(int row, int col);

    void readFromInput();

    void readFromFile();

    void parseLine(string input, const int &row);
};

#endif //VIIKKO_3_LIFE_H
