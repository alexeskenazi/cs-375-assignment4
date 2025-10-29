# CS 375 Assignment 4 - Algorithm Guide

## Project Overview
This assignment implements multiple algorithmic solutions:
1. **Graph Algorithm**: Part B.1 - Course prerequisite scheduling using DAG algorithms
2. **Linear Programming**: Part B.2 - Diet optimization using corner point method
3. **Simplex Algorithm**: 3-variable LP maximization (extra credit)
4. **Cycle Detection**: Problem 2b - undirected graph cycle detection with BFS traversal
5. **Topological Sort**: DFS-based topological ordering with edge classification

---

## 1. Graph Assignment (B1_graph_assignment.cpp)

### Problem
Find the minimum number of semesters needed to complete all 15 CS courses given prerequisite constraints.

### Key Algorithms Used

#### **Topological Sorting (Kahn's Algorithm)**
- **Purpose**: Find valid course ordering respecting prerequisites
- **Time Complexity**: O(V + E)
- **Algorithm Steps**:
  1. Count incoming edges (prerequisites) for each course
  2. Add courses with 0 prerequisites to queue
  3. Process courses from queue, removing them as prerequisites
  4. Add newly available courses to queue
  5. Continue until all courses processed

#### **Implicit Cycle Detection**
- **Purpose**: Verify prerequisite structure is feasible (no circular dependencies)
- **Method**: Topological sort inherently detects cycles
- **Logic**: If topological sort can't process all courses, cycles exist

#### **Minimum Semester Calculation**
- **Purpose**: Find the longest path in the DAG (critical path)
- **Algorithm**:
  1. Process courses in topological order
  2. For each course: semester = 1 + max(prerequisite semesters)
  3. Return maximum semester among all courses


### **Results**: 5 semesters needed

---

## 2. Linear Programming Assignment (B2_lp_assignment.cpp)

### Problem
Minimize cost of drinks X and Y while meeting nutritional requirements:
- Minimize: 0.12X + 0.15Y
- Subject to: Calories ≥ 300, Vitamin A ≥ 36, Vitamin C ≥ 90

### **Corner Point Method**
- **Theory**: Optimal solution occurs at vertices of feasible region
- **Algorithm Steps**:
  1. Convert constraints to standard form
  2. Find intersection points of constraint boundaries
  3. Evaluate objective function at each corner point
  4. Select minimum cost solution

### **Mathematical Solution Process**:
1. **Constraint Simplification**:
   - 60X + 60Y ≥ 300 → X + Y ≥ 5
   - 12X + 6Y ≥ 36 → 2X + Y ≥ 6
   - 10X + 30Y ≥ 90 → X + 3Y ≥ 9

2. **Corner Points Found**:
   - (1, 4): Cost = $0.72
   - (3, 2): Cost = $0.66 ← **Optimal**
   - (1.8, 2.4): Cost = $0.576 (not feasible)

### **Results**: 3 cups X, 2 cups Y, minimum cost $0.66

---

## 3. Simplex Algorithm (simplex_solver.cpp)

### Problem
Maximize P = 20x₁ + 10x₂ + 15x₃ subject to:
- 3x₁ + 2x₂ + 5x₃ ≤ 55
- 2x₁ + 1x₂ + 1x₃ ≤ 26
- x₁ + x₂ + 3x₃ ≤ 30
- 5x₁ + 2x₂ + 4x₃ ≤ 57

### **Simplex Method Algorithm**
1. **Convert to Standard Form**:
   - Add slack variables s₁, s₂, s₃, s₄
   - Create initial simplex tableau
   - Objective row with negative coefficients

2. **Iterative Process**:
   - **Entering Variable**: Most negative coefficient in objective row
   - **Leaving Variable**: Minimum ratio test (RHS/pivot column)
   - **Pivot Operations**: Make pivot element = 1, others in column = 0

3. **Optimality Test**: All objective row coefficients ≥ 0

4. **Solution Extraction**: Read basic variables from final tableau

### **Results**: x₁ = 1.80, x₂ = 20.80, x₃ = 1.60, Maximum P = 268.00

---

## 4. Cycle Detection (2b_cycle_detection.cpp)

### Problem 2 Solution

#### **Part A & B: Cycle Detection Algorithm**
- **Data Structure**: Adjacency list representation
- **Algorithm**: DFS with parent tracking
- **Logic**: If we visit a node that's already visited and it's not our parent → cycle found

#### **Part C: BFS Traversal**
- **Algorithm**: Standard BFS using queue
- **Starting Node**: Node 1
- **Result**: Breadth-first traversal order

### **Test Results**:
- Graph (i): Has cycle ✓
- Graph (ii): Has cycle ✓  
- BFS from node 1: 1 2 5 3 4 6 7

---

## 5. Topological Sort (5_topological_sort.cpp)

### Problem 5 Solution
DFS-based topological sort with discovery/finishing times and edge classification.

#### **Algorithm**: Depth-First Search with Timing
- **Data Structure**: Adjacency list representation
- **Traversal Order**: Start with node 1, then node 7, with node 2 before node 4
- **Edge Classification**:
  - **T (Tree Edge)**: Leads to unvisited node
  - **B (Back Edge)**: Points to ancestor (indicates cycle in directed graph)
  - **F (Forward Edge)**: Points to descendant
  - **C (Cross Edge)**: Points to previously finished node

#### **DFS Algorithm Steps**:
1. Color nodes: White (0) → Gray (1) → Black (2)
2. Track discovery and finishing times
3. Classify each edge based on destination node state
4. Build topological order using finishing times

### **Results**:
- **Topological Order**: 1 → 7 → 4 → 8 → 6 → 2 → 5 → 3
- **Edge Types**: All four types identified correctly
- **Discovery/Finish Times**: Complete timing for each node
- **Time Complexity**: O(V + E)

---

## Key Performance Metrics

| Program | Algorithm | Time Complexity | Running Time |
|---------|-----------|----------------|--------------|
| Graph Assignment | Topological Sort + DFS | O(V + E) | ~0.02 ms |
| LP Assignment | Corner Point Method | O(n²) | ~0.02 ms |
| Simplex Algorithm | Simplex Method | Exponential (worst case) | ~0.11 ms |
| Cycle Detection | DFS | O(V + E) | ~0.004 ms |
| Topological Sort (Problem 5) | DFS with Timing | O(V + E) | ~0.04 ms |

---

## Presentation Key Points

### **Technical Highlights**:
1. **Graph Theory**: DAG properties, topological ordering, cycle detection, DFS traversal
2. **Linear Programming**: Feasible regions, corner point theorem, optimization
3. **Algorithm Analysis**: Time/space complexity understanding
4. **Data Structures**: Adjacency lists, queues, vectors
5. **Edge Classification**: Tree, back, forward, and cross edges in DFS

### **Problem-Solving Approach**:
1. **Mathematical Modeling**: Convert real problems to algorithmic solutions
2. **Algorithm Selection**: Choose appropriate methods for each problem type
3. **Implementation**: Clean, readable code with proper data structures
4. **Verification**: Test cases and constraint checking

### **Real-World Applications**:
- **Course Scheduling**: Academic planning systems
- **Resource Optimization**: Diet planning, production optimization
- **Network Analysis**: Social networks, dependency graphs
- **Operations Research**: Supply chain, logistics optimization