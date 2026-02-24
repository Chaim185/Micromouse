#include "Space.h"

class Board {
public:
    Board();
    Board(int, int);
    void testRange();
    void display();

protected:
    int numRows;
    int numColumns;
    Space s[8][8];
};

Board::Board() : numRows(8), numColumns(8)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            s[i][j].setColumn(char('A' + j));
            s[i][j].setRow(i + 1);
        }
    }
}

Board::Board(int r, int c) : numRows(r), numColumns(c)
{
    testRange();

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            s[i][j].setColumn(char('A' + j));
            s[i][j].setRow(i + 1);
        }
    }
}

void Board::display()
{
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numColumns; j++)
            s[i][j].display();
}

void Board::testRange()
{
    if ((numColumns <= 0) || (numColumns >= 9) || (numRows <= 0) || (numRows >= 9))
    {
        output_file << "Out of Range" << endl;
        exit(1);
    }
}
