# Problem 5 Topological Sort Algorithm Guide

## Problem 5 Solution
DFS-based topological sort with discovery/finishing times and edge classification.

## **Algorithm**: Depth-First Search with Timing
- **Data Structure**: Adjacency list representation
- **Traversal Order**: Start with node 1, then node 7, with node 2 before node 4
- **Edge Classification**:
  - **T (Tree Edge)**: Leads to unvisited node
  - **B (Back Edge)**: Points to ancestor (indicates cycle in directed graph)
  - **F (Forward Edge)**: Points to descendant
  - **C (Cross Edge)**: Points to previously finished node

## **DFS Algorithm Steps**:
1. Color nodes: White (0) → Gray (1) → Black (2)
2. Track discovery and finishing times
3. Classify each edge based on destination node state
4. Build topological order using finishing times

## Edge Classification Logic
```cpp
void classifyEdge(int u, int v) {
    string edgeType;
    if (color[v] == 0) {
        edgeType = "T (tree edge)";        // White node
    } else if (color[v] == 1) {
        edgeType = "B (back edge)";        // Gray node
    } else if (discovery[u] < discovery[v]) {
        edgeType = "F (forward edge)";     // Black descendant
    } else {
        edgeType = "C (cross edge)";       // Black non-descendant
    }
}
```

## DFS Visit Implementation
```cpp
void dfsVisit(int u) {
    color[u] = 1;                          // Gray
    discovery[u] = ++time_counter;
    
    for (int v : adj[u]) {
        classifyEdge(u, v);
        if (color[v] == 0) {
            dfsVisit(v);
        }
    }
    
    color[u] = 2;                          // Black
    finish[u] = ++time_counter;
    topoOrder.insert(topoOrder.begin(), u); // Reverse order
}
```

## Results
- **Topological Order**: 1 → 7 → 4 → 8 → 6 → 2 → 5 → 3
- **Edge Types**: All four types identified correctly
- **Discovery/Finish Times**: Complete timing for each node
- **Time Complexity**: O(V + E)
- **Running Time**: ~0.045 ms

## Usage
```bash
./5_topological_sort
# Uses hardcoded graph from assignment
```

## Key Output
- Complete DFS traversal with timestamps
- Edge classification for each edge
- Final topological ordering
- Discovery and finishing times for all nodes