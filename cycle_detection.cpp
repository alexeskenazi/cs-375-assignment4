#include <iostream>
#include <vector>
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
    
    return 0;
}