#include <iostream>
#include <vector>

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
    
    cout << "\n--- Testing Graph (ii) ---" << endl;
    CycleDetector graph2(4);
    
    graph2.addEdge(0, 1);
    graph2.addEdge(1, 3);
    graph2.addEdge(3, 2);
    graph2.addEdge(2, 0);
    graph2.addEdge(0, 3);
    graph2.addEdge(1, 2);
    
    graph2.printGraph();
    
    return 0;
}