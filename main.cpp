/***************************************************************************
* COMSC-210 | Lab 26 | Grant Luo
* Editor: CLion
* Compiler: Apple clang version 16.0.0
*/
#include <iostream>
#include <fstream>
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

void print_id(string const& lab_desc);

int main()
{
    print_id("Lab 26: Data Structures Olympics");

    // Use long long to prevent overflow
    long long results[RUNS][ROWS][COLS] {};
    long long subtotals[ROWS][COLS] {};

    string labels[] {"Read", "Sort", "Insert", "Delete"};

    // Perform the experiment RUNS times
    for (int run = 0; run < RUNS; run++)
    {
        string cd;
        vector<string> vectorData {};
        list<string> listData {};
        set<string> setData {};

        // READing race
        for (int i = 0; i < STRUCTURES; i++)
        {
            ifstream fin("codes.txt");
            auto start = chrono::high_resolution_clock::now();
            switch (i)
            {
                case 0: // Read into vector
                {
                    while (fin >> cd)
                        vectorData.push_back(cd);
                    break;
                }

                case 1: // Read into list
                {
                    while (fin >> cd)
                        listData.push_back(cd);
                    break;
                }

                case 2: // Read into set
                {
                    while (fin >> cd)
                        setData.insert(cd);
                    break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][0][i] = duration.count();
            fin.close();
        }

        // SORTing race
        for (int i = 0; i < STRUCTURES; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            switch (i)
            {
                case 0: // Sort vector
                {
                    sort(vectorData.begin(), vectorData.end());
                    break;
                }

                case 1: // Sort list
                {
                    listData.sort();
                    break;
                }

                case 2: // Sort set (a set is already sorted upon creation)
                {
                    break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][1][i] = duration.count();
        }

        // INSERTing race
        for (int i = 0; i < STRUCTURES; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            switch (i)
            {
                case 0: // Insert into vector
                {
                    int ind_v = vectorData.size() / 2;
                    vectorData.insert(vectorData.begin() + ind_v, "TESTCODE");
                    break;
                }
                case 1: // Insert into list
                {
                    int ind_l = listData.size() / 2;
                    auto it = listData.begin();
                    advance(it, ind_l);
                    listData.insert(it, "TESTCODE");
                    break;
                }
                case 2: // Insert into set
                {
                    setData.insert("TESTCODE");
                    break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][2][i] = duration.count();
        }

        // DELETing race
        for (int i = 0; i < STRUCTURES; i++)
        {
            string target_v = vectorData[ vectorData.size() / 2 ];

            auto it1 = listData.begin();
            int ind1 = listData.size() / 2;
            advance(it1, ind1);
            string target_l = *it1;

            auto it2 = setData.begin();
            int ind2 = setData.size() / 2;
            advance(it2, ind2);
            string target_s = *it2;

            auto start = chrono::high_resolution_clock::now();
            switch (i)
            {
                case 0: // Delete from vector
                {
                    vectorData.erase(remove(vectorData.begin(), vectorData.end(), target_v));
                    break;
                }

                case 1: // Delete from list
                {
                    listData.remove(target_l);
                    break;
                }

                case 2: // Delete from set
                {
                    setData.erase(target_s);
                    break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            results[run][3][i] = duration.count();
        }
    }

    // Compute Subtotals
    for (int run = 0; run < RUNS; run++)
    {
        for (int op = 0; op < ROWS; op++)
        {
            for (int ds = 0; ds < COLS; ds++)
                subtotals[op][ds] += results[run][op][ds];
        }
    }

    // Compute Averages
    double averages[ROWS][COLS] {};
    for (int op = 0; op < ROWS; op++)
    {
        for (int ds = 0; ds < COLS; ds++)
            averages[op][ds] = subtotals[op][ds] / (double) RUNS;
    }

    // Display the averaged results
    cout << setw(W1) << "Operations";
    cout << setw(W1) << "Vector" << setw(W1) << "List" << setw(W1) << "Set\n";
    for (int op = 0; op < ROWS; op++)
    {
        cout << setw(W1) << labels[op];
        for (int ds = 0; ds < COLS; ds++)
        {
            if (averages[op][ds] == -1)
                cout << setw(W1) << "-";
            else
                cout << setw(W1) << averages[op][ds];
        }
        cout << "\n";
    }
    cout << "\n";

    return 0;
}

void print_id(string const& lab_desc)
{
    cout << "\nCOMSC210 | Grant Luo | " << lab_desc << "\n";
    cout << "Editor: CLion\n";
    cout << "Compiler: Apple clang version 16.0.0\n";
    cout << "File: " << __FILE__ << "\n";
    cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}