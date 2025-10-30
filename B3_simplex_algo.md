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