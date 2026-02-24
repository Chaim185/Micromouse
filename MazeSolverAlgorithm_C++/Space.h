#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
using namespace std;

ifstream input_file;
ofstream output_file("output.txt");
//ofstream output_file2("output2.txt")

class Space {
public:
    Space();
    Space(char, int);
    void setColumn(char);
    void setRow(int);
    char getColumn() const;
    int getRow() const;

    void incrementVisits();
    void incrementUpwardVisits();
    void incrementDownwardVisits();
    void incrementRightwardVisits();
    void incrementLeftwardVisits();

    void resetVisits();
    void resetUpwardVisits();
    void resetDownwardVisits();
    void resetRightwardVisits();
    void resetLeftwardVisits();

    void incrementExits();
    void incrementUpwardExits();
    void incrementDownwardExits();
    void incrementRightwardExits();
    void incrementLeftwardExits();

    void resetExits();
    void resetUpwardExits();
    void resetDownwardExits();
    void resetRightwardExits();
    void resetLeftwardExits();

    int getVisits() const;
    int getUpwardVisits() const;
    int getDownwardVisits() const;
    int getRightwardVisits() const;
    int getLeftwardVisits() const;

    int getExits() const;
    int getUpwardExits() const;
    int getDownwardExits() const;
    int getRightwardExits() const;
    int getLeftwardExits() const;

    bool operator == (Space);
    bool operator != (Space);
    void display();

private:
    char column;
    int row;

    int visits;
    int upwardVisits;
    int downwardVisits;
    int rightwardVisits;
    int leftwardVisits;

    int exits;
    int upwardExits;
    int downwardExits;
    int rightwardExits;
    int leftwardExits;
};

Space::Space() : column('A'), row(1), visits(0), upwardVisits(0), downwardVisits(0), rightwardVisits(0), leftwardVisits(0),
exits(0), upwardExits(0), downwardExits(0), rightwardExits(0), leftwardExits(0)
{
    // empty
}

Space::Space(char c, int r) : column(c), row(r), visits(0), upwardVisits(0), downwardVisits(0), rightwardVisits(0), leftwardVisits(0),
exits(0), upwardExits(0), downwardExits(0), rightwardExits(0), leftwardExits(0)
{
    // empty
}

void Space::display()
{
    output_file << "Space " << column << row << endl;
}

void Space::setColumn(char c)
{
    column = c;
}

void Space::setRow(int r)
{
    row = r;
}

char Space::getColumn() const
{
    return column;
}

int Space::getRow() const
{
    return row;
}

bool Space::operator == (Space other)
{
    if ((column == other.column) && (row == other.row))
        return true;

    return false;
}

bool Space::operator != (Space other)
{
    if ((column == other.column) && (row == other.row))
        return false;

    return true;
}

void Space::incrementVisits()
{
    visits++;
}

void Space::incrementUpwardVisits()
{
    upwardVisits++;
}

void Space::incrementDownwardVisits()
{
    downwardVisits++;
}

void Space::incrementRightwardVisits()
{
    rightwardVisits++;
}

void Space::incrementLeftwardVisits()
{
    leftwardVisits++;
}

void Space::resetVisits()
{
    visits = 0;
}

void Space::resetUpwardVisits()
{
    upwardVisits = 0;
}

void Space::resetDownwardVisits()
{
    downwardVisits = 0;
}

void Space::resetRightwardVisits()
{
    rightwardVisits = 0;
}

void Space::resetLeftwardVisits()
{
    leftwardVisits = 0;
}

void Space::incrementExits()
{
    exits++;
}

void Space::incrementUpwardExits()
{
    upwardExits++;
}

void Space::incrementDownwardExits()
{
    downwardExits++;
}

void Space::incrementRightwardExits()
{
    rightwardExits++;
}
void Space::incrementLeftwardExits()
{
    leftwardExits++;
}

void Space::resetExits()
{
    exits = 0;
}

void Space::resetUpwardExits()
{
    upwardExits = 0;
}

void Space::resetDownwardExits()
{
    downwardExits = 0;
}

void Space::resetRightwardExits()
{
    rightwardExits = 0;
}

void Space::resetLeftwardExits()
{
    leftwardExits = 0;
}

int Space::getVisits() const
{
    return visits;
}

int Space::getUpwardVisits() const
{
    return upwardVisits;
}

int Space::getDownwardVisits() const
{
    return downwardVisits;
}

int Space::getRightwardVisits() const
{
    return rightwardVisits;
}

int Space::getLeftwardVisits() const
{
    return leftwardVisits;
}

int Space::getExits() const
{
    return exits;
}

int Space::getUpwardExits() const
{
    return upwardExits;
}

int Space::getDownwardExits() const
{
    return downwardExits;
}

int Space::getRightwardExits() const
{
    return rightwardExits;
}

int Space::getLeftwardExits() const
{
    return leftwardExits;
}