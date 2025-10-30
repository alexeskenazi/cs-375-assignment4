# Problem 2b Cycle Detection Algorithm Guide

## Problem 2b Solution

### **Part A & B: Cycle Detection Algorithm**
- **Data Structure**: Adjacency list representation
- **Algorithm**: DFS with parent tracking
- **Logic**: If we visit a node that's already visited and it's not our parent → cycle found

### **Part C: BFS Traversal**
- **Algorithm**: Standard BFS using queue
- **Starting Node**: Node 1
- **Result**: Breadth-first traversal order

## Algorithm Details

### Cycle Detection (Undirected Graphs)
```cpp
bool hasCycle(int node, int parent, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (hasCycle(neighbor, node, visited))
                return true;
        } else if (neighbor != parent) {
            return true; // Back edge found = cycle
        }
    }
    return false;
}
```

### BFS Traversal
```cpp
void bfs(int start) {
    queue<int> q;
    vector<bool> visited(numNodes, false);
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << (node + 1) << " ";
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

## Results
- **Graph (i)**: Has cycle ✓
- **Graph (ii)**: Has cycle ✓  
- **BFS from node 1**: 1 2 5 3 4 6 7
- **Time Complexity**: O(V + E)
- **Running Time**: ~0.004 ms

## Usage
```bash
./2b_cycle_detection
# Uses hardcoded test graphs
```