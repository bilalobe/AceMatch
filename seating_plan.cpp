#ifndef SEATINGPLAN_H
#define SEATINGPLAN_H

#include <iostream>
#include <vector>

using namespace std;

class SeatingPlan
{
public:
    vector<vector<bool>> seatingPlan;

    SeatingPlan(int numRows, int numCols) : seatingPlan(numRows, vector<bool>(numCols, false)) {}

    void reserveSeat(int row, int col)
    {
        if (row >= 0 && row < seatingPlan.size() && col >= 0 && col < seatingPlan[row].size())
        {
            seatingPlan[row][col] = 'X'; // Mark as reserved
        }
    }

    bool isSeatAvailable(int row, int col)
    {
        if (row >= 0 && row < seatingPlan.size() && col >= 0 && col < seatingPlan[row].size())
        {
            return !seatingPlan[row][col];
        }
        return false;
    }

    void displaySeatingPlan()
    {
        cout << "Seating Plan:" << endl;
        for (int i = 0; i < seatingPlan.size(); i++)
        {
            for (int j = 0; j < seatingPlan[i].size(); j++)
            {
                cout << (seatingPlan[i][j] ? "X" : "O") << " ";
            }
            cout << endl;
        }
    }
    void initializeSeatingPlan(int row, int col)
    {
        seatingPlan.resize(row);
        for (int i = 0; i < row; ++i)
        {
            seatingPlan[i].resize(col, '.'); // Initialize with '.' for available seats
        }
    }

    void releaseSeat(int row, int col)
    {
        if (!isSeatAvailable(row, col))
        {
            seatingPlan[row][col] = '.'; // Mark as available
        }
    }
};

#endif