#include "Board.h"

class Maze : public Board {
public:
    Maze();
    Maze(Space st, Space e); // Constructor that takes different start and end points for the maze
    void display();
    
    void moveCursorToSpace(Space s);
    // Use these functions to create a virtual barrier
    void moveCursorToVerticalBarrier(Space s, int n);
    void moveCursorToHorizontalBarrier(Space s, int n);
    void moveCursorToBottom();
    void changeColor(int desiredColor);


protected:
    Space start;
    Space end;
    int horizontalWall_HorizontalDimension;
    int horizontalWall_VerticalDimension;
    int verticalWall_HorizontalDimension;
    int verticalWall_VerticalDimension;

    string horizontalWalls[9][8];
    char verticalWalls[8][9];

    int numEnds;
    char ends[9];

    bool horizontalBarrier[9][8];
    bool verticalBarrier[8][9];
   
    // Virtual barriers are created upon returning from a dead end
    // so the robot knows not to take that path again 
    bool virtualHorizontalBarrier[9][8];
    bool virtualVerticalBarrier[8][9];

    int endRowIndex;
    int endColIndex;
};

Maze::Maze() : Board(), horizontalWall_HorizontalDimension(numColumns),
horizontalWall_VerticalDimension(numRows + 1), verticalWall_HorizontalDimension(numColumns + 1),
verticalWall_VerticalDimension(numRows), numEnds(numRows + 1), start(s[0][0]), end(s[7][7])
{

    endRowIndex = end.getRow() - 1;        // Subtract rows by 1 and columns by 'A' to attain proper index of arrays
    endColIndex = end.getColumn() - 'A';   // This makes it easier to code maze solver


    input_file.open("input5.txt", ios::in);

    for (int i = 0; i < horizontalWall_VerticalDimension + verticalWall_VerticalDimension; i++)
    {
        if ((i % 2) == 0)
            cout << "  ";
        else
            cout << i / 2 + 1 << " ";

        for (int j = 0; j <= horizontalWall_HorizontalDimension; j++)
        {
            if ((i % 2) == 0) // even values of i will input horizontal rows
            {
                if (j != horizontalWall_HorizontalDimension) // That is, prior to reaching the rightmost + sign
                {
                    input_file >> horizontalWalls[i / 2][j];
                    cout << horizontalWalls[i / 2][j];
                    if (horizontalWalls[i / 2][j] == "+")
                        cout << "   ";
                }
                else
                {
                    input_file >> ends[i / 2];
                    cout << ends[i / 2];
                }
            }
            else // odd values of i will input vertical rows
            {
                input_file >> verticalWalls[i / 2][j];
                if (verticalWalls[i / 2][j] == '|')
                    cout << verticalWalls[i / 2][j] << "   ";
                else if (verticalWalls[i / 2][j] == '.')
                    cout << "    ";
            }
        }
        cout << endl;
    }
    input_file.close();
    input_file.clear();

    cout << " ";
    for (int k = 0; k < horizontalWall_HorizontalDimension; k++)
        cout << "   " << char('A' + k);

    for (int i = 0; i < horizontalWall_VerticalDimension; i++)
    {
        for (int j = 0; j < horizontalWall_HorizontalDimension; j++)
        {
            if (horizontalWalls[i][j] == "+---")
                horizontalBarrier[i][j] = true;
            else if (horizontalWalls[i][j] == "+")
                horizontalBarrier[i][j] = false;

            virtualHorizontalBarrier[i][j] = false;
        }
    }

    for (int i = 0; i < verticalWall_VerticalDimension; i++)
    {
        for (int j = 0; j < verticalWall_HorizontalDimension; j++)
        {
            if (verticalWalls[i][j] == '|')
                verticalBarrier[i][j] = true;
            else if (verticalWalls[i][j] == '.')
                verticalBarrier[i][j] = false;

            virtualVerticalBarrier[i][j] = false;
        }
    }

    // Show start and end of maze
    moveCursorToSpace(end);
    cout << "\bE";
    moveCursorToSpace(start);
    cout << "\bS*";

    output_file << "Starting position is ";
    start.display();
}

Maze::Maze(Space st, Space e) : Board(), horizontalWall_HorizontalDimension(numColumns),
horizontalWall_VerticalDimension(numRows + 1), verticalWall_HorizontalDimension(numColumns + 1),
verticalWall_VerticalDimension(numRows), numEnds(numRows + 1), start(st), end(e)
{

    endRowIndex = end.getRow() - 1;        // Subtract rows by 1 and columns by 'A' to attain proper index of arrays
    endColIndex = end.getColumn() - 'A';   // This makes it easier to code maze solver


    input_file.open("input5.txt", ios::in);

    for (int i = 0; i < horizontalWall_VerticalDimension + verticalWall_VerticalDimension; i++)
    {
        if ((i % 2) == 0)
            cout << "  ";
        else
            cout << i / 2 + 1 << " ";

        for (int j = 0; j <= horizontalWall_HorizontalDimension; j++)
        {
            if ((i % 2) == 0) // even values of i will input horizontal rows
            {
                if (j != horizontalWall_HorizontalDimension) // That is, prior to reaching the rightmost + sign
                {
                    input_file >> horizontalWalls[i / 2][j];
                    cout << horizontalWalls[i / 2][j];
                    if (horizontalWalls[i / 2][j] == "+")
                        cout << "   ";
                }
                else
                {
                    input_file >> ends[i / 2];
                    cout << ends[i / 2];
                }
            }
            else // odd values of i will input vertical rows
            {
                input_file >> verticalWalls[i / 2][j];
                if (verticalWalls[i / 2][j] == '|')
                    cout << verticalWalls[i / 2][j] << "   ";
                else if (verticalWalls[i / 2][j] == '.')
                    cout << "    ";
            }
        }
        cout << endl;
    }
    input_file.close();
    input_file.clear();

    cout << " ";
    for (int k = 0; k < horizontalWall_HorizontalDimension; k++)
        cout << "   " << char('A' + k);

    for (int i = 0; i < horizontalWall_VerticalDimension; i++)
    {
        for (int j = 0; j < horizontalWall_HorizontalDimension; j++)
        {
            if (horizontalWalls[i][j] == "+---")
                horizontalBarrier[i][j] = true;
            else if (horizontalWalls[i][j] == "+")
                horizontalBarrier[i][j] = false;

            virtualHorizontalBarrier[i][j] = false;
        }
    }

    for (int i = 0; i < verticalWall_VerticalDimension; i++)
    {
        for (int j = 0; j < verticalWall_HorizontalDimension; j++)
        {
            if (verticalWalls[i][j] == '|')
                verticalBarrier[i][j] = true;
            else if (verticalWalls[i][j] == '.')
                verticalBarrier[i][j] = false;

            virtualVerticalBarrier[i][j] = false;
        }
    }

    // Show start and end of maze
    moveCursorToSpace(end);
    cout << "\bE";
    moveCursorToSpace(start);   
    cout << "\bS*";

    output_file << "Starting position is ";
    start.display();
}

void Maze::moveCursorToSpace(Space s)
{
    int y = s.getRow() * 2 - 1;
    int x = (s.getColumn() - 'A' + 1) * 4;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

void Maze::moveCursorToVerticalBarrier(Space s, int n)
{
    int y = s.getRow() * 2 - 1;
    int x = (s.getColumn() - 'A' + 1) * 4 - 2*n;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

void Maze::moveCursorToHorizontalBarrier(Space s, int n)
{
    int y = s.getRow() * 2 - 1 + n;
    int x = (s.getColumn() - 'A' + 1) * 4-1;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

void Maze::moveCursorToBottom()
{
    int y = 18;
    int x = 0;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

void Maze::changeColor(int desiredColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}


void Maze::display()
{
    for (int i = 0; i < horizontalWall_VerticalDimension; i++)
    {
        for (int j = 0; j < horizontalWall_HorizontalDimension; j++)
        {
            if (horizontalBarrier[i][j])
                output_file << "wall";
            else
                output_file << "space";

            output_file << "   ";
        }
        output_file << endl;
    }
    output_file << endl;

    for (int i = 0; i < verticalWall_VerticalDimension; i++)
    {
        for (int j = 0; j < verticalWall_HorizontalDimension; j++)
        {
            if (verticalBarrier[i][j])
                output_file << "wall";
            else
                output_file << "space";

            output_file << "   ";
        }
        output_file << endl;
    }
    output_file << endl;

    output_file << "The maze starts at "; 
    start.display();
    output_file << "The maze ends at ";
    end.display();
}
