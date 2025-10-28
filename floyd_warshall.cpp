#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <ctime>
#include <iomanip>

using namespace std;

const int INF = 999999;

// reads the graph from a file or uses hardcoded data if file doesn't work
void readGraph(vector<vector<int>>& graph, int& n, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "Reading graph from file: " << filename << endl;
        file >> n;
        cout << "Number of cities: " << n << endl;
        
        graph.assign(n+1, vector<int>(n+1, INF));
        for (int i = 1; i <= n; i++) {
            graph[i][i] = 0;
        }
        
        int u, v, w;
        int edgeCount = 0;
        while (file >> u >> v >> w) {
            graph[u][v] = w;
            edgeCount++;
        }
        cout << "Successfully loaded " << edgeCount << " edges from file" << endl;
        file.close();
    } else {
        cout << "Could not open file: " << filename << endl;
        cout << "Using hardcoded graph data..." << endl;
        
        n = 11;
        graph.assign(n+1, vector<int>(n+1, INF));
        for (int i = 1; i <= n; i++) {
            graph[i][i] = 0;
        }
        
        vector<vector<int>> edges = {
            {1, 2, 140}, {1, 7, 100}, {1, 8, 70},
            {2, 3, 130}, {2, 5, 100},
            {3, 4, 160},
            {4, 5, 65}, {4, 11, 180},
            {5, 6, 70}, {5, 9, 70},
            {6, 7, 60},
            {7, 8, 65},
            {9, 10, 60},
            {10, 11, 100}
        };
        
        for (auto& edge : edges) {
            graph[edge[0]][edge[1]] = edge[2];
        }
    }
}

// main algorithm: finds shortest paths between all pairs of cities
void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& next, int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

// prints the distance matrix (how far each city is from each other city)
void printDistanceMatrix(const vector<vector<int>>& dist, int n, ofstream* outFile) {
    cout << "\n===============================================" << endl;
    cout << "           FINAL D TABLE (Distance Matrix)" << endl;
    cout << "===============================================" << endl;
    
    if (outFile) {
        *outFile << "//** show final D table **//\n\n";
    }
    
    cout << setw(8) << "";
    for (int j = 1; j <= n; j++) {
        cout << setw(8) << j;
    }
    cout << endl;
    
    for (int i = 1; i <= n; i++) {
        cout << setw(8) << i;
        for (int j = 1; j <= n; j++) {
            cout << setw(8) << dist[i][j];
            if (outFile) {
                *outFile << dist[i][j];
                if (j < n) *outFile << " ";
            }
        }
        cout << endl;
        if (outFile) *outFile << "\n";
    }
    
    if (outFile) *outFile << "\n\n";
    cout << "===============================================" << endl;
}

// prints the next hop matrix (which city to go to next for shortest path)
void printNextMatrix(const vector<vector<int>>& next, int n, ofstream* outFile) {
    cout << "\n===============================================" << endl;
    cout << "           FINAL P TABLE (Next Hop Matrix)" << endl;
    cout << "===============================================" << endl;
    
    if (outFile) {
        *outFile << "//** show final P table **//\n\n";
    }
    
    cout << setw(8) << "";
    for (int j = 1; j <= n; j++) {
        cout << setw(8) << j;
    }
    cout << endl;
    
    for (int i = 1; i <= n; i++) {
        cout << setw(8) << i;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                cout << setw(8) << "-";
                if (outFile) *outFile << "- ";
            } else {
                cout << setw(8) << next[i][j];
                if (outFile) {
                    *outFile << next[i][j];
                    if (j < n) *outFile << " ";
                }
            }
        }
        cout << endl;
        if (outFile) *outFile << "\n";
    }
    
    if (outFile) *outFile << "\n\n";
    cout << "===============================================" << endl;
}

// figures out the actual path from start city to end city
void printPath(int start, int end, const vector<vector<int>>& next, const vector<vector<int>>& dist) {
    if (next[start][end] == 0) {
        cout << "No path exists";
        return;
    }
    
    vector<int> path;
    int current = start;
    path.push_back(current);
    
    while (current != end) {
        current = next[current][end];
        path.push_back(current);
    }
    
    for (int i = 0; i < (int)path.size(); i++) {
        cout << "City " << path[i];
        if (i < (int)path.size() - 1) cout << " -> ";
    }
}

// shows all the shortest paths between every pair of cities
void printAllPaths(const vector<vector<int>>& dist, const vector<vector<int>>& next, int n, ofstream* outFile) {
    cout << "\n===============================================" << endl;
    cout << "        ALL SHORTEST PATHS BETWEEN CITIES" << endl;
    cout << "===============================================" << endl;
    
    if (outFile) {
        *outFile << "//** show the path of the shortest distance between any pair of cities **//\n\n";
    }
    
    int pathCount = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && dist[i][j] != INF) {
                cout << "\n" << pathCount << ". Shortest path from city " << i 
                     << " to city " << j << " (total distance: " << dist[i][j] 
                     << " miles): ";
                
                if (outFile) {
                    *outFile << pathCount << ". From city " << i << " to city " << j << ": path #" << i;
                    
                    // Build path for file output
                    vector<int> path;
                    int current = i;
                    path.push_back(current);
                    
                    while (current != j) {
                        current = next[current][j];
                        path.push_back(current);
                    }
                    
                    for (int k = 1; k < (int)path.size(); k++) {
                        *outFile << ", #" << path[k];
                    }
                    *outFile << "; Distance: " << dist[i][j] << "\n";
                }
                
                printPath(i, j, next, dist);
                pathCount++;
            }
        }
    }
    
    cout << "\n\nTotal paths found: " << pathCount - 1 << endl;
    cout << "===============================================" << endl;
    
    if (outFile) {
        *outFile << "\n\n";
    }
}

int main(int argc, char* argv[]) {
    cout << "======================================================" << endl;
    cout << "         CS 375 Assignment 3" << endl;
    cout << "    SHORTEST PATH PROBLEM - FLOYD WARSHALL" << endl;
    cout << "======================================================" << endl;
    
    string inputFile = "input.txt";
    string outputFile = "";
    ofstream* outFilePtr = nullptr;
    
    if (argc >= 2) {
        inputFile = argv[1];
        cout << "\nUsing input file: " << inputFile << endl;
    }
    
    if (argc >= 3) {
        outputFile = argv[2];
        cout << "Using output file: " << outputFile << endl;
        outFilePtr = new ofstream(outputFile);
        if (!outFilePtr->is_open()) {
            cout << "Warning: Could not open output file. Results will only be displayed on console." << endl;
            delete outFilePtr;
            outFilePtr = nullptr;
        }
    }
    
    vector<vector<int>> graph, dist, next;
    int n;
    
    readGraph(graph, n, inputFile);
    
    dist = graph;
    next.assign(n+1, vector<int>(n+1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && graph[i][j] != INF) {
                next[i][j] = j;
            }
        }
    }
    
    cout << "\nExecuting Floyd-Warshall algorithm..." << endl;
    clock_t start_time = clock();
    floydWarshall(dist, next, n);
    clock_t end_time = clock();
    
    double execution_time = 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Algorithm completed successfully!" << endl;
    cout << "Running time of Floyd-Warshall algorithm: " << fixed << setprecision(3) 
         << execution_time << " milliseconds" << endl;
    
    if (outFilePtr) {
        cout << "\nWriting results to file: " << outputFile << endl;
    }
    
    printDistanceMatrix(dist, n, outFilePtr);
    printNextMatrix(next, n, outFilePtr);
    printAllPaths(dist, next, n, outFilePtr);
    
    if (outFilePtr) {
        *outFilePtr << "//** print out running time **//\n";
        *outFilePtr << fixed << setprecision(3) << execution_time << " milliseconds\n";
    }
    
    if (outFilePtr) {
        cout << "\nResults successfully written to: " << outputFile << endl;
        outFilePtr->close();
        delete outFilePtr;
    }
    
    cout << "\n======================================================" << endl;
    cout << "              PERFORMANCE SUMMARY" << endl;
    cout << "======================================================" << endl;
    cout << "Graph size: " << n << " cities (" << n+1 << "x" << n+1 << " matrix)" << endl;
    cout << "Algorithm complexity: O(n^3) = O(" << n+1 << "^3) = " 
         << (n+1) * (n+1) * (n+1) << " operations" << endl;
    cout << "Actual running time: " << fixed << setprecision(3) << execution_time << " ms" << endl;
    cout << "Space complexity: O(n^2) - using two " << n+1 << "x" << n+1 << " matrices" << endl;
    cout << "======================================================" << endl;
    cout << "              ANALYSIS COMPLETE" << endl;
    cout << "======================================================" << endl;
    
    return 0;
}