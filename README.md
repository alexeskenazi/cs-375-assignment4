# CS 375 Assignment 4

## Overview
This project implements multiple algorithmic solutions for CS 375 Assignment 4:

- **B1_graph_assignment.cpp** - Course prerequisite scheduling using DAG algorithms
- **B2_lp_assignment.cpp** - Diet optimization using linear programming
- **B3_simplex_solver.cpp** - 3-variable LP maximization using Simplex method (extra credit)
- **2b_cycle_detection.cpp** - Cycle detection in undirected graphs with BFS traversal
- **5_topological_sort.cpp** - DFS-based topological sort with edge classification

## How to Run

### Compile All Programs
```bash
make all
```

### Run Individual Programs
```bash
make test_graph    # Run B1 - Graph assignment
make test_lp       # Run B2 - Linear programming
make test_simplex  # Run B3 - Simplex solver
make test_cycle    # Run 2b - Cycle detection
make test_topo     # Run 5 - Topological sort
```

### Run All Programs
```bash
make test
```

### Clean Build Files
```bash
make clean
```

## Expected Results

| Program | Expected Output |
|---------|----------------|
| B1 | 5 minimum semesters needed |
| B2 | Optimal solution: 3 cups X, 2 cups Y, cost $0.66 |
| B3 | Maximum P = 268.00 at x₁=1.80, x₂=20.80, x₃=1.60 |
| 2b | Both test graphs contain cycles, BFS traversal from node 1 |
| 5 | Topological order with discovery/finishing times and edge classification |

## Documentation

- [Assignment Prompt](prompt.md) - Original assignment requirements and problems
- [Algorithm Guide](ALGORITHM_GUIDE.md) - Detailed algorithm explanations and analysis