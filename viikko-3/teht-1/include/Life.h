#ifndef VIIKKO_3_LIFE_HPP
#define VIIKKO_3_LIFE_H

const int maxrow = 20, maxcol = 60; //  grid dimensions

class Life
{
public:
//    Life() = default;
//    ~Life() = default;
    void initialize();
    void print();
    void update();
    void askUser();

private:
    int grid[maxrow + 2][maxcol + 2]; //  allows for two extra rows and columns
    int neighbor_count(int row, int col);
};

#endif //VIIKKO_3_LIFE_HPP
