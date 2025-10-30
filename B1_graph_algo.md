# B1 Graph Assignment Algorithm Guide

## Problem
Find the minimum number of semesters needed to complete all 15 CS courses given prerequisite constraints.

## Key Algorithms Used

### **Topological Sorting (Kahn's Algorithm)**
- **Purpose**: Find valid course ordering respecting prerequisites
- **Time Complexity**: O(V + E)
- **Algorithm Steps**:
  1. Count incoming edges (prerequisites) for each course
  2. Add courses with 0 prerequisites to queue
  3. Process courses from queue, removing them as prerequisites
  4. Add newly available courses to queue
  5. Continue until all courses processed

### **Implicit Cycle Detection**
- **Purpose**: Verify prerequisite structure is feasible (no circular dependencies)
- **Method**: Topological sort inherently detects cycles
- **Logic**: If topological sort can't process all courses, cycles exist

### **Minimum Semester Calculation**
- **Purpose**: Find the longest path in the DAG (critical path)
- **Algorithm**:
  1. Process courses in topological order
  2. For each course: semester = 1 + max(prerequisite semesters)
  3. Return maximum semester among all courses

## Results
- **Minimum Semesters**: 5
- **Time Complexity**: O(V + E)
- **Running Time**: ~0.16 ms

## Usage
```bash
./B1_graph_assignment [input_file] [output_file]
# Default: B1_input.txt → B1_output.txt
```

## Input Format
```
//** Directed Graph with N course (CSi --> CSj) **//
CS2 CS4
CS4 CS5
CS1 CS6
...
```

## Output Format
- Cycle detection result
- Topological sorted sequence  
- Edge type classification
- Minimum semesters needed
- Bipartite check (N/A for DAG)
- Running time