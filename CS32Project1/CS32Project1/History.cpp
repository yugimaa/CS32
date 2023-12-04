#include<iostream>
#include"History.h"
#include"Arena.h"
#include"globals.h"
using namespace std;

History::History(int nRows, int nCols)
{
    mRows = nRows;
    mCols = nCols;

    int r, c;

    // Fill historyGrid with dots (for initial blank history)
    for (r = 1; r <= mRows; r++)
    {
        for (c = 1; c <= mCols; c++)
        {
            historyGrid[r - 1][c - 1] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    //invalid range
    if (r > mRows || c > mCols)
    {
        return false;
    }
    
    char girdContent = historyGrid[r - 1][c - 1];
    //case starting with first time. If the point is already recordede previously (if it is already A, B, then it moves to next letter)
    switch (girdContent)
    {
    case '.':  
        historyGrid[r - 1][c - 1] = 'A';
        break;
    case 'A':  
        historyGrid[r - 1][c - 1] = 'B';
        break;
    case 'B':
        historyGrid[r - 1][c - 1] = 'C';
        break;
    case 'C':
        historyGrid[r - 1][c - 1] = 'D';
        break;
    case 'D':
        historyGrid[r - 1][c - 1] = 'E';
        break;
    case 'E':
        historyGrid[r - 1][c - 1] = 'F';
        break;
    case 'F':
        historyGrid[r - 1][c - 1] = 'G';
        break;
    case 'G':
        historyGrid[r - 1][c - 1] = 'h';
        break;
    case 'H':
        historyGrid[r - 1][c - 1] = 'I';
        break;
    case 'I':
        historyGrid[r - 1][c - 1] = 'J';
        break;
    case 'J':
        historyGrid[r - 1][c - 1] = 'K';
        break;
    case 'K':
        historyGrid[r - 1][c - 1] = 'L';
        break;
    case 'L':
        historyGrid[r - 1][c - 1] = 'M';
        break;
    case 'M':
        historyGrid[r - 1][c - 1] = 'N';
        break;
    case 'N':
        historyGrid[r - 1][c - 1] = 'O';
        break;
    case 'O':
        historyGrid[r - 1][c - 1] = 'P';
        break;
    case 'P':
        historyGrid[r - 1][c - 1] = 'Q';
        break;
    case 'Q':
        historyGrid[r - 1][c - 1] = 'R';
        break;
    case 'R':
        historyGrid[r - 1][c - 1] = 'S';
        break;
    case 'S':
        historyGrid[r - 1][c - 1] = 'T';
        break;
    case 'T':
        historyGrid[r - 1][c - 1] = 'U';
        break;
    case 'U':
        historyGrid[r - 1][c - 1] = 'V';
        break;
    case 'V':
        historyGrid[r - 1][c - 1] = 'W';
        break;
    case 'W':
        historyGrid[r - 1][c - 1] = 'X';
        break;
    case 'X':
        historyGrid[r - 1][c - 1] = 'Y';
        break;
    case 'Y':
        historyGrid[r - 1][c - 1] = 'Z';
        break;
    case 'Z':
        historyGrid[r - 1][c - 1] = 'Z';
        break;
    }
    return true;
}

void History::display() const
{
    clearScreen();
    for (int r = 1; r <= mRows; r++)
    {
        for (int c = 1; c <= mCols; c++)
        {
            cout << historyGrid[r - 1][c - 1];
        }
        cout << endl;
    }
    cout << endl;
}
