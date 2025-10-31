#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cmath>

using namespace std;

// B.3 Extra Credit - Simplex Algorithm for Question #9
// Maximize P = 20x1 + 10x2 + 15x3
// Subject to:
//   3x1 + 2x2 + 5x3 <= 55
//   2x1 + 1x2 + 1x3 <= 26  
//   1x1 + 1x2 + 3x3 <= 30
//   5x1 + 2x2 + 4x3 <= 57
//   x1, x2, x3 >= 0

// Class to solve linear programming problems using simplex method
class SimplexSolver {
private:
    vector<vector<double>> table;  // The simplex table
    int rows, cols;
    
public:
    // Constructor sets up the initial simplex table
    SimplexSolver() {
        rows = 5;  // 4 constraints + 1 objective function
        cols = 8;  // 3 variables + 4 slack variables + RHS
        
        table.resize(rows);
        for (int i = 0; i < rows; i++) {
            table[i].resize(cols, 0);
        }
        
        // Set up constraint equations with slack variables
        // 3x1 + 2x2 + 5x3 + s1 = 55
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
        
        // Objective function: maximize P = 20x1 + 10x2 + 15x3
        // Convert to standard form by negating coefficients
        table[4][0] = -20; 
        table[4][1] = -10; 
        table[4][2] = -15; 
        table[4][7] = 0;
    }
    
    void printTable() {
        cout << "    x1      x2      x3      s1      s2      s3      s4      RHS" << endl;
        cout << "-------------------------------------------------------" << endl;
        
        for (int i = 0; i < rows; i++) {
            if (i < 4) {
                cout << "s" << (i+1) << " ";
            } else {
                cout << "P  ";
            }
            
            for (int j = 0; j < cols; j++) {
                double val = table[i][j];
                if (abs(val) < 1e-10) val = 0;
                cout << val << "\t";
            }
            cout << endl;
        }
        cout << "-------------------------------------------------------" << endl;
    }
    
    // Perform row operations to make pivot element = 1 and other column elements = 0
    void doPivotOperations(int pivotRow, int pivotCol) {
        double pivotElement = table[pivotRow][pivotCol];
        cout << "Making pivot element 1 by dividing row " << pivotRow 
             << " by " << pivotElement << endl;
        
        // Make pivot element equal to 1
        for (int j = 0; j < cols; j++) {
            table[pivotRow][j] = table[pivotRow][j] / pivotElement;
        }
        
        // Make all other elements in pivot column equal to 0
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
    
    // Check if we have reached optimal solution
    // Optimal when all coefficients in objective row are non-negative
    bool isOptimal() {
        for (int j = 0; j < cols - 1; j++) {
            if (table[rows-1][j] < 0) {
                return false;
            }
        }
        return true;
    }
    
    void solve() {
        cout << "Solving using Simplex Method..." << endl;
        cout << "Problem: Maximize P = 20x1 + 10x2 + 15x3" << endl;
        cout << "Initial table:" << endl;
        printTable();
        
        int iteration = 0;
        
        while (!isOptimal()) {
            iteration++;
            cout << "\n--- Iteration " << iteration << " ---" << endl;
            
            // Find entering variable (most negative coefficient)
            double mostNegative = 0;
            int pivotCol = -1;
            for (int j = 0; j < cols - 1; j++) {
                if (table[4][j] < mostNegative) {
                    mostNegative = table[4][j];
                    pivotCol = j;
                }
            }
            
            if (pivotCol == -1) {
                cout << "Optimal solution found!" << endl;
                break;
            }
            
            cout << "Entering variable: x" << (pivotCol + 1) << endl;
            
            // Find leaving variable using minimum ratio test
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
            
            cout << "Leaving variable: s" << (pivotRow + 1) << endl;
            cout << "Pivot element: " << table[pivotRow][pivotCol] << endl;
            
            doPivotOperations(pivotRow, pivotCol);
            
            cout << "\nAfter pivot operations:" << endl;
            printTable();
        }
        
        cout << "\n=== OPTIMAL SOLUTION ===" << endl;
        
        // Extract solution values from final table
        double x1 = 0, x2 = 0, x3 = 0;
        
        // Look for basic variables (coefficient = 1 in their column)
        for (int i = 0; i < 4; i++) {
            if (table[i][0] == 1) {
                x1 = table[i][7];
            }
            if (table[i][1] == 1) {
                x2 = table[i][7];
            }
            if (table[i][2] == 1) {
                x3 = table[i][7];
            }
        }
        
        double maxProfit = table[rows-1][7];
        
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;  
        cout << "x3 = " << x3 << endl;
        cout << "Maximum P = " << maxProfit << endl;
    }
};

int main() {
    cout << "CS 375 Assignment 4 - Part B.3" << endl;
    cout << "Simplex Algorithm for Question #9" << endl;
    cout << "==================================" << endl;
    
    // Start timing
    clock_t start = clock();
    
    SimplexSolver solver;
    solver.solve();
    
    // Calculate and display running time
    clock_t end = clock();
    double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    
    cout << "\nRunning time: " << time << " milliseconds" << endl;
    cout << "==================================" << endl;
    
    return 0;
}