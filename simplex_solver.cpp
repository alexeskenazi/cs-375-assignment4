#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// B.3 Extra Credit - Simplex Algorithm for Question #9
// Maximize P = 20x1 + 10x2 + 15x3
// Subject to:
//   3x1 + 2x2 + 5x3 <= 55
//   2x1 + 1x2 + 1x3 <= 26  
//   1x1 + 1x2 + 3x3 <= 30
//   5x1 + 2x2 + 4x3 <= 57
//   x1, x2, x3 >= 0

class SimplexSolver {
private:
    vector<vector<double>> table;
    int rows, cols;
    
public:
    SimplexSolver() {
        rows = 5;
        cols = 8;
        
        table.resize(rows);
        for (int i = 0; i < rows; i++) {
            table[i].resize(cols, 0);
        }
        
    }
    
    void printTable() {
        cout << "Current table:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << table[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void solve() {
        cout << "Attempting to solve using Simplex Method..." << endl;
        cout << "This is more complex than expected!" << endl;
        printTable();
    }
};

int main() {
    cout << "CS 375 Assignment 4 - Part B.3" << endl;
    cout << "Simplex Algorithm for Question #9" << endl;
    cout << "==================================" << endl;
    
    SimplexSolver solver;
    solver.solve();
    
    return 0;
}