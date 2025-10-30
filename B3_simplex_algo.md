# B3 Simplex Algorithm Guide

## Problem
Maximize P = 20x₁ + 10x₂ + 15x₃ subject to:
- 3x₁ + 2x₂ + 5x₃ ≤ 55
- 2x₁ + 1x₂ + 1x₃ ≤ 26
- x₁ + x₂ + 3x₃ ≤ 30
- 5x₁ + 2x₂ + 4x₃ ≤ 57

## **Simplex Method Algorithm**
1. **Convert to Standard Form**:
   - Add slack variables s₁, s₂, s₃, s₄
   - Create initial simplex table
   - Objective row with negative coefficients

2. **Iterative Process**:
   - **Entering Variable**: Most negative coefficient in objective row
   - **Leaving Variable**: Minimum ratio test (RHS/pivot column)
   - **Pivot Operations**: Make pivot element = 1, others in column = 0

3. **Optimality Test**: All objective row coefficients ≥ 0

4. **Solution Extraction**: Read basic variables from final table

## Algorithm Steps
1. **Iteration 1**: x₁ enters, s₄ leaves
2. **Iteration 2**: x₂ enters, s₂ leaves  
3. **Iteration 3**: x₃ enters, s₁ leaves
4. **Optimal**: All coefficients ≥ 0

## Results
- **Optimal Solution**: x₁ = 1.80, x₂ = 20.80, x₃ = 1.60
- **Maximum P**: 268.00
- **Time Complexity**: Exponential (worst case)
- **Running Time**: ~0.309 ms

## Usage
```bash
./B3_simplex_solver
# Uses hardcoded problem data
```

## Key Features
- Complete simplex table operations
- Pivot element selection and operations
- Optimality checking
- Solution extraction from final table

## Detailed Algorithm Implementation

### 1. **Initial Simplex Table Setup** - B3_simplex_solver.cpp:28-66
**Purpose**: Convert the LP problem to standard form with slack variables

```cpp
void setupInitialTable() {
    // Constraint 1: 3x₁ + 2x₂ + 5x₃ + s₁ = 55
    table[0][0] = 3; table[0][1] = 2; table[0][2] = 5; 
    table[0][3] = 1; table[0][7] = 55;
    
    // Constraint 2: 2x₁ + 1x₂ + 1x₃ + s₂ = 26  
    table[1][0] = 2; table[1][1] = 1; table[1][2] = 1;
    table[1][4] = 1; table[1][7] = 26;
    
    // Constraint 3: x₁ + x₂ + 3x₃ + s₃ = 30
    table[2][0] = 1; table[2][1] = 1; table[2][2] = 3;
    table[2][5] = 1; table[2][7] = 30;
    
    // Constraint 4: 5x₁ + 2x₂ + 4x₃ + s₄ = 57
    table[3][0] = 5; table[3][1] = 2; table[3][2] = 4;
    table[3][6] = 1; table[3][7] = 57;
    
    // Objective: Maximize P = 20x₁ + 10x₂ + 15x₃
    // Standard form: -20x₁ - 10x₂ - 15x₃ + P = 0
    table[4][0] = -20; table[4][1] = -10; table[4][2] = -15; table[4][7] = 0;
}
```

### 2. **Pivot Element Selection** - B3_simplex_solver.cpp:113-146
**Purpose**: Choose entering and leaving variables for optimization

```cpp
bool isOptimal() {
    // Check if all coefficients in objective row are non-negative
    for (int j = 0; j < cols-1; j++) {
        if (table[rows-1][j] < 0) {
            return false;  // Still have negative coefficients
        }
    }
    return true;  // Optimal solution found
}

int findEnteringVariable() {
    // Find most negative coefficient in objective row
    int enteringCol = -1;
    double mostNegative = 0;
    
    for (int j = 0; j < cols-1; j++) {
        if (table[rows-1][j] < mostNegative) {
            mostNegative = table[rows-1][j];
            enteringCol = j;
        }
    }
    return enteringCol;
}

int findLeavingVariable(int enteringCol) {
    // Minimum ratio test: min(RHS / pivot_column) for positive ratios
    int leavingRow = -1;
    double minRatio = 999999;
    
    for (int i = 0; i < rows-1; i++) {
        if (table[i][enteringCol] > 0) {
            double ratio = table[i][cols-1] / table[i][enteringCol];
            if (ratio < minRatio) {
                minRatio = ratio;
                leavingRow = i;
            }
        }
    }
    return leavingRow;
}
```

### 3. **Pivot Operations** - B3_simplex_solver.cpp:88-112
**Purpose**: Perform row operations to make pivot element = 1, others in column = 0

```cpp
void doPivotOperations(int pivotRow, int pivotCol) {
    double pivotElement = table[pivotRow][pivotCol];
    
    // Step 1: Make pivot element equal to 1
    for (int j = 0; j < cols; j++) {
        table[pivotRow][j] = table[pivotRow][j] / pivotElement;
    }
    
    // Step 2: Make all other elements in pivot column equal to 0
    for (int i = 0; i < rows; i++) {
        if (i != pivotRow && table[i][pivotCol] != 0) {
            double factor = table[i][pivotCol];
            
            // Row[i] = Row[i] - factor × pivotRow
            for (int j = 0; j < cols; j++) {
                table[i][j] = table[i][j] - factor * table[pivotRow][j];
            }
        }
    }
}
```

### 4. **Main Simplex Algorithm** - B3_simplex_solver.cpp:148-206
**Purpose**: Iterate until optimal solution is found

```cpp
void solve() {
    int iteration = 1;
    
    while (!isOptimal()) {
        cout << "--- Iteration " << iteration << " ---" << endl;
        
        // Step 1: Find entering variable (most negative in objective row)
        int enteringCol = findEnteringVariable();
        cout << "Entering variable: x" << (enteringCol + 1) << endl;
        
        // Step 2: Find leaving variable (minimum ratio test)  
        int leavingRow = findLeavingVariable(enteringCol);
        cout << "Leaving variable: s" << (leavingRow + 1) << endl;
        
        // Step 3: Perform pivot operations
        doPivotOperations(leavingRow, enteringCol);
        
        printTable();
        iteration++;
    }
    
    // Extract solution from final table
    extractSolution();
}
```

## Key Simplex Method Concepts

1. **Standard Form**: Convert inequalities to equalities using slack variables
2. **Basic vs Non-Basic Variables**: Basic variables have values, non-basic = 0
3. **Entering Variable**: Variable with most negative coefficient (steepest ascent)
4. **Leaving Variable**: Determined by minimum ratio test (maintain feasibility)
5. **Pivot Operations**: Gaussian elimination to update the table
6. **Optimality**: All objective row coefficients ≥ 0

## Example Iteration Walkthrough

**Initial Table**:
```
    x₁   x₂   x₃   s₁   s₂   s₃   s₄   RHS
s₁   3    2    5    1    0    0    0    55
s₂   2    1    1    0    1    0    0    26  
s₃   1    1    3    0    0    1    0    30
s₄   5    2    4    0    0    0    1    57
P  -20  -10  -15    0    0    0    0     0
```

**Iteration 1**:
- **Entering**: x₁ (most negative: -20)
- **Leaving**: s₄ (minimum ratio: 57/5 = 11.4)
- **Pivot**: Element at (3,0) = 5
- **Operations**: Make pivot = 1, other column elements = 0

**Result**: Continue until no negative coefficients in objective row

## Algorithm Complexity
- **Best Case**: O(m) iterations where m = number of constraints
- **Average Case**: O(m) to O(m²) iterations  
- **Worst Case**: Exponential (very rare in practice)
- **Per Iteration**: O(mn) operations where n = number of variables