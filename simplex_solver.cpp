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
        
        table[0][0] = 3; 
        table[0][1] = 2; 
        table[0][2] = 5; 
        table[0][3] = 1; 
        table[0][7] = 55;
        
        table[1][0] = 2; 
        table[1][1] = 1; 
        table[1][2] = 1; 
        table[1][4] = 1; 
        table[1][7] = 26;
        
        table[2][0] = 1; 
        table[2][1] = 1; 
        table[2][2] = 3; 
        table[2][5] = 1; 
        table[2][7] = 30;
        
        table[3][0] = 5; 
        table[3][1] = 2; 
        table[3][2] = 4; 
        table[3][6] = 1; 
        table[3][7] = 57;
        
        table[4][0] = -20; 
        table[4][1] = -10; 
        table[4][2] = -15; 
        table[4][7] = 0;
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
    
    void doPivotOperations(int pivotRow, int pivotCol) {
        double pivotElement = table[pivotRow][pivotCol];
        cout << "Making pivot element 1 by dividing row " << pivotRow 
             << " by " << pivotElement << endl;
        
        for (int j = 0; j < cols; j++) {
            table[pivotRow][j] = table[pivotRow][j] / pivotElement;
        }
        
        for (int i = 0; i < rows; i++) {
            if (i != pivotRow) {
                double factor = table[i][pivotCol];
                cout << "Making row " << i << " element 0 using factor " << factor << endl;
                
                for (int j = 0; j < cols; j++) {
                    table[i][j] = table[i][j] - factor * table[pivotRow][j];
                }
            }
        }
    }
    
    void solve() {
        cout << "Solving using Simplex Method..." << endl;
        cout << "Initial table:" << endl;
        printTable();
        
        int iteration = 1;
        
        while (iteration <= 3) {
            cout << "\n--- Iteration " << iteration << " ---" << endl;
            
            double mostNegative = 0;
            int pivotCol = -1;
            for (int j = 0; j < cols - 1; j++) {
                if (table[4][j] < mostNegative) {
                    mostNegative = table[4][j];
                    pivotCol = j;
                }
            }
            
            if (pivotCol == -1) {
                cout << "No negative coefficients - optimal solution found!" << endl;
                break;
            }
            
            cout << "Entering variable: column " << pivotCol 
                 << " (coefficient " << mostNegative << ")" << endl;
            
            double minRatio = 999999;
            int pivotRow = -1;
            cout << "Ratio test:" << endl;
            for (int i = 0; i < 4; i++) {
                if (table[i][pivotCol] > 0) {
                    double ratio = table[i][7] / table[i][pivotCol];
                    cout << "  Row " << i << ": " << table[i][7] << "/" 
                         << table[i][pivotCol] << " = " << ratio << endl;
                    if (ratio < minRatio) {
                        minRatio = ratio;
                        pivotRow = i;
                    }
                }
            }
            
            if (pivotRow == -1) {
                cout << "Unbounded solution!" << endl;
                return;
            }
            
            cout << "Leaving variable: row " << pivotRow << endl;
            cout << "Pivot element: " << table[pivotRow][pivotCol] << endl;
            
            doPivotOperations(pivotRow, pivotCol);
            
            cout << "\nAfter pivot operations:" << endl;
            printTable();
            
            iteration++;
        }
        
        cout << "\n=== FINAL SOLUTION ===" << endl;
        cout << "Objective value (P): " << table[4][7] << endl;
        
        cout << "Need to extract variable values from final table..." << endl;
        cout << "(This is the hardest part!)" << endl;
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