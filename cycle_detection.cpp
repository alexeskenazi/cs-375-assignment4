#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

// Problem 2: Cycle Detection in Undirected Graphs

class CycleDetector {
private:
    int numVertices;
    vector<vector<int>> adjList;
    
public:
    CycleDetector(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
    }
    
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    
    void printGraph() {
        cout << "Graph representation (adjacency list):" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Node " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    bool dfsHasCycle(int node, vector<bool>& visited, int parent) {
        visited[node] = true;
        
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                if (dfsHasCycle(neighbor, visited, node)) {
                    return true;
                }
            }
            else if (neighbor != parent) {
                cout << "Cycle found: edge (" << node << ", " << neighbor << ")" << endl;
                return true;
            }
        }
        return false;
    }
    
    bool hasCycle() {
        vector<bool> visited(numVertices, false);
        
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                if (dfsHasCycle(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    void bfsTraversal(int startNode) {
        cout << "BFS traversal starting from node " << (startNode + 1) << ": ";
        
        vector<bool> visited(numVertices, false);
        queue<int> q;
        
        visited[startNode] = true;
        q.push(startNode);
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << (current + 1) << " ";
            
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    cout << "CS 375 Problem 2: Cycle Detection" << endl;
    cout << "=================================" << endl;
    
    cout << "\n--- Testing Graph (i) ---" << endl;
    CycleDetector graph1(6);
    
    graph1.addEdge(0, 1);
    graph1.addEdge(1, 2);
    graph1.addEdge(0, 3);
    graph1.addEdge(1, 4);
    graph1.addEdge(3, 4);
    graph1.addEdge(4, 5);
    graph1.addEdge(2, 5);
    
    graph1.printGraph();
    
    clock_t start = clock();
    bool hasCycle1 = graph1.hasCycle();
    clock_t end = clock();
    
    cout << "Graph (i) contains cycle: " << (hasCycle1 ? "YES" : "NO") << endl;
    double time1 = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << time1 << " milliseconds" << endl;
    
    cout << "\n--- Testing Graph (ii) ---" << endl;
    CycleDetector graph2(4);
    
    graph2.addEdge(0, 1);
    graph2.addEdge(1, 3);
    graph2.addEdge(3, 2);
    graph2.addEdge(2, 0);
    graph2.addEdge(0, 3);
    graph2.addEdge(1, 2);
    
    graph2.printGraph();
    
    start = clock();
    bool hasCycle2 = graph2.hasCycle();
    end = clock();
    
    cout << "Graph (ii) contains cycle: " << (hasCycle2 ? "YES" : "NO") << endl;
    double time2 = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << time2 << " milliseconds" << endl;
    
    cout << "\n--- Part (c): BFS Traversal ---" << endl;
    cout << "Building the directed graph from part (c)..." << endl;
    
    CycleDetector directedGraph(7);
    
    directedGraph.addEdge(0, 1);  // 1-2
    directedGraph.addEdge(0, 4);  // 1-5
    directedGraph.addEdge(1, 2);  // 2-3
    directedGraph.addEdge(1, 3);  // 2-4
    directedGraph.addEdge(2, 6);  // 3-7
    directedGraph.addEdge(3, 5);  // 4-6
    directedGraph.addEdge(3, 6);  // 4-7
    directedGraph.addEdge(4, 3);  // 5-4
    directedGraph.addEdge(4, 5);  // 5-6
    directedGraph.addEdge(5, 6);  // 6-7
    
    cout << "Graph structure:" << endl;
    directedGraph.printGraph();
    
    directedGraph.bfsTraversal(0);
    
    return 0;
}