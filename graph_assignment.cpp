#include <iostream>
#include <vector>

using namespace std;

// Assignment 4 - Graph Algorithm
// Need to find minimum semesters for course prerequisites

class Graph {
public:
    int numCourses;
    vector<vector<int>> adj;
    vector<string> courseNames;
    
    Graph(int n) {
        numCourses = n;
        adj.resize(n);
        courseNames.resize(n);
    }
    
    void addEdge(int from, int to) {
        adj[from].push_back(to);
    }
    
    void setCourseName(int i, string name) {
        courseNames[i] = name;
    }
    
    void printGraph() {
        cout << "Graph structure:" << endl;
        for (int i = 0; i < numCourses; i++) {
            cout << courseNames[i] << " -> ";
            for (int j : adj[i]) {
                cout << courseNames[j] << " ";
            }
            cout << endl;
        }
    }
    
    void printPrereqCount() {
        vector<int> prereqCount(numCourses, 0);
        
        // Count how many prerequisites each course has
        for (int i = 0; i < numCourses; i++) {
            for (int j : adj[i]) {
                prereqCount[j]++;
            }
        }
        
        cout << "\nNumber of prerequisites for each course:" << endl;
        for (int i = 0; i < numCourses; i++) {
            cout << courseNames[i] << ": " << prereqCount[i] << " prerequisites" << endl;
        }
    }
};

int main() {
    cout << "CS 375 Assignment 4 - Graph Algorithm" << endl;
    
    // Create graph with 15 courses (cs1 to cs15)
    Graph g(15);
    
    // Set course names
    for (int i = 0; i < 15; i++) {
        g.setCourseName(i, "cs" + to_string(i + 1));
    }
    
    // Add prerequisites (edges from prerequisite TO course)
    // cs4 requires cs2
    g.addEdge(1, 3); 
    
    // cs5 requires cs4  
    g.addEdge(3, 4);
    
    // cs6 requires cs1 and cs3
    g.addEdge(0, 5); 
    g.addEdge(2, 5); 
    
    // cs7 requires cs4
    g.addEdge(3, 6);
    
    // cs8 requires cs5 and cs6
    g.addEdge(4, 7); 
    g.addEdge(5, 7); 
    
    // cs9 requires cs7
    g.addEdge(6, 8);
    
    // cs10 requires cs9
    g.addEdge(8, 9);
    
    // cs11 requires cs8
    g.addEdge(7, 10);
    
    // cs12 requires cs3
    g.addEdge(2, 11);
    
    // cs13 requires cs6
    g.addEdge(5, 12); 

    // cs14 requires cs4 and cs6
    g.addEdge(3, 13);
    g.addEdge(5, 13); 
    
    // cs15 requires cs14
    g.addEdge(13, 14); 
    
    g.printGraph();
    g.printPrereqCount();
    
    
    return 0;
}