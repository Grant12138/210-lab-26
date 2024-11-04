/***************************************************************************
* COMSC-210 | Lab 26 | Grant Luo
* Editor: CLion
* Compiler: Apple clang version 16.0.0
*/
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iomanip>
using namespace std;

// const int SZ = 20000, COLS = 3, ROWS = 4, TESTS = 4;
const int STRUCTURES = 3;
const int ROWS = 4, COLS = 3;
const int W1 = 10;
const int RUNS = 15; // Run the experiment 15 times

int main()
{

    string labels [] {"Read", "Sort", "Insert", "Delete"};
    string structureLabels[] {"Vector", "List", "Set"};

    // Perform the experiment RUNS times
    for (int run = 0; run < RUNS; run++)
    {
        for (int i = 0; i < STRUCTURES; i++)
        {

        }
    }

    return 0;
}