# B2 Linear Programming Algorithm Guide

## Problem
Minimize cost of drinks X and Y while meeting nutritional requirements:
- Minimize: 0.12X + 0.15Y
- Subject to: Calories ≥ 300, Vitamin A ≥ 36, Vitamin C ≥ 90

## **Corner Point Method**
- **Theory**: Optimal solution occurs at vertices of feasible region
- **Algorithm Steps**:
  1. Convert constraints to standard form
  2. Find intersection points of constraint boundaries
  3. Evaluate objective function at each corner point
  4. Select minimum cost solution

## **Mathematical Solution Process**:
1. **Constraint Simplification**:
   - 60X + 60Y ≥ 300 → X + Y ≥ 5
   - 12X + 6Y ≥ 36 → 2X + Y ≥ 6
   - 10X + 30Y ≥ 90 → X + 3Y ≥ 9

2. **Corner Points Found**:
   - (1, 4): Cost = $0.72
   - (3, 2): Cost = $0.66 ← **Optimal**
   - (1.8, 2.4): Cost = $0.576 (not feasible)

## Results
- **Optimal Solution**: 3 cups X, 2 cups Y
- **Minimum Cost**: $0.66
- **Time Complexity**: O(n²)
- **Running Time**: ~0.014 ms

## Usage
```bash
./B2_lp_assignment [input_file] [output_file]
# Default: B2_input.txt → B2_output.txt
```

## Input Format
```
//** Linear Programming with n decision variables and m constraints **//
<=

//* object function coefficients Cj *//
0.12 0.15

//* constraint coefficients Aij and constraint level Bi *//
60 60 300
12 6 36
10 30 90
```

## Output Format
- Minimum cost and drink quantities
- Maximum profit section (N/A for minimization)
- Running time