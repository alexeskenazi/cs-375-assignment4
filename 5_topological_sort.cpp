#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class TopologicalSort {
private:
    int numNodes;
    vector<vector<int>> adj;
    vector<int> color;
    vector<int> discovery;
    vector<int> finish;
    vector<int> topoOrder;
    int time_counter;
    
public:
    TopologicalSort(int n) {
        numNodes = n;
        adj.resize(n);
        color.resize(n, 0);
        discovery.resize(n, 0);
        finish.resize(n, 0);
        time_counter = 0;
    }
    
    void addEdge(int from, int to) {
        adj[from].push_back(to);
    }
    
    void printGraph() {
        cout << "Graph edges:" << endl;
        for (int i = 0; i < numNodes; i++) {
            cout << "Node " << (i + 1) << " -> ";
            for (int j : adj[i]) {
                cout << (j + 1) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void dfsVisit(int u) {
        color[u] = 1;
        time_counter++;
        discovery[u] = time_counter;
        cout << "Visiting node " << (u + 1) << " at time " << discovery[u] << endl;
        
        for (int v : adj[u]) {
            classifyEdge(u, v);
            if (color[v] == 0) {
                dfsVisit(v);
            }
        }
        
        color[u] = 2;
        time_counter++;
        finish[u] = time_counter;
        cout << "Finishing node " << (u + 1) << " at time " << finish[u] << endl;
        topoOrder.insert(topoOrder.begin(), u);
    }
    
    void classifyEdge(int u, int v) {
        string edgeType;
        if (color[v] == 0) {
            edgeType = "T (tree edge)";
        } else if (color[v] == 1) {
            edgeType = "B (back edge)";
        } else if (discovery[u] < discovery[v]) {
            edgeType = "F (forward edge)";
        } else {
            edgeType = "C (cross edge)";
        }
        cout << "Edge " << (u + 1) << " -> " << (v + 1) << ": " << edgeType << endl;
    }
    
    void topologicalSort() {
        cout << "Starting DFS traversal..." << endl;
        
        // Start with node 1 (index 0)
        dfsVisit(0);
        
        // Then visit node 7 (index 6) as specified
        if (color[6] == 0) {
            dfsVisit(6);
        }
        
        // Visit remaining nodes, with node 2 before node 4 as specified
        for (int node : {1, 3, 2, 4, 5, 7}) {  // 2,4,3,5,6,8 in 0-indexed
            if (color[node] == 0) {
                dfsVisit(node);
            }
        }
        
        cout << "\nTopological order: ";
        for (int i = 0; i < (int)topoOrder.size(); i++) {
            cout << (topoOrder[i] + 1);
            if (i < (int)topoOrder.size() - 1) cout << " -> ";
        }
        cout << endl;
        
        cout << "\nDiscovery and finishing times:" << endl;
        for (int i = 0; i < numNodes; i++) {
            cout << "Node " << (i + 1) << ": discovery=" << discovery[i] 
                 << ", finish=" << finish[i] << endl;
        }
    }
};

int main() {
    cout << "Problem 5: Topological Sort with DFS" << endl;
    cout << "====================================" << endl;
    
    TopologicalSort graph(8);
    
    // Build the graph from the image
    graph.addEdge(0, 3);  // 1 -> 4
    graph.addEdge(0, 1);  // 1 -> 2
    graph.addEdge(0, 6);  // 1 -> 7
    graph.addEdge(1, 3);  // 2 -> 4
    graph.addEdge(1, 4);  // 2 -> 5
    graph.addEdge(1, 2);  // 2 -> 3
    graph.addEdge(2, 4);  // 3 -> 5
    graph.addEdge(3, 7);  // 4 -> 8
    graph.addEdge(4, 2);  // 5 -> 3
    graph.addEdge(5, 1);  // 6 -> 2
    graph.addEdge(5, 4);  // 6 -> 5
    graph.addEdge(6, 2);  // 7 -> 3
    graph.addEdge(7, 3);  // 8 -> 4
    graph.addEdge(7, 5);  // 8 -> 6
    
    graph.printGraph();
    
    clock_t start = clock();
    graph.topologicalSort();
    clock_t end = clock();
    
    double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << "\nTime complexity: O(V + E)" << endl;
    cout << "Running time: " << time << " milliseconds" << endl;
    
    return 0;
}