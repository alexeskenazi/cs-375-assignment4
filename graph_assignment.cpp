#include <iostream>
#include "Graph.h"

using namespace std;

// Assignment 4 - Graph Algorithm
// Need to find minimum semesters for course prerequisites

int main() {
    cout << "CS 375 Assignment 4 - Graph Algorithm" << endl;
    
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
    
    // Test cycle detection by adding a cycle temporarily
    // g.addEdge(14, 13); // This would create cs14 -> cs15 -> cs14 cycle 
    
    g.printGraph();
    g.printPrereqCount();
    
    // Check for cycles first
    cout << "\n--- Checking for Cycles ---" << endl;
    if (g.hasCycle()) {
        cout << "CYCLE FOUND! This prerequisite structure is impossible." << endl;
        return 1;
    } else {
        cout << "No cycles found - prerequisite structure is valid." << endl;
    }
    
    // Try topological sorting
    cout << "\n--- Testing Topological Sort ---" << endl;
    vector<int> order = g.topSort();
    
    cout << "Course order: ";
    for (int i = 0; i < (int)order.size(); i++) {
        cout << g.courseNames[order[i]];
        if (i < (int)order.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    
    if (order.size() != 15) {
        cout << "ERROR: Only processed " << order.size() << " courses! Graph might have cycles." << endl;
        return 1;
    } else {
        cout << "Success! All 15 courses processed." << endl;
    }
    
    cout << "\n--- Minimum Semesters Calculation ---" << endl;
    int answer = g.calculateMinSemesters();
    cout << "\nMINIMUM SEMESTERS NEEDED: " << answer << endl;
    
    // Check if graph is bipartite
    cout << "\n--- Bipartite Check ---" << endl;
    vector<int> groups;
    if (g.isBipartite(groups)) {
        cout << "Graph is bipartite!" << endl;
        
        // Show the two groups
        vector<int> group0, group1;
        for (int i = 0; i < 15; i++) {
            if (groups[i] == 0) {
                group0.push_back(i);
            } else {
                group1.push_back(i);
            }
        }
        
        cout << "Group 1: ";
        for (int i = 0; i < (int)group0.size(); i++) {
            cout << g.courseNames[group0[i]];
            if (i < (int)group0.size() - 1) cout << ", ";
        }
        cout << endl;
        
        cout << "Group 2: ";
        for (int i = 0; i < (int)group1.size(); i++) {
            cout << g.courseNames[group1[i]];
            if (i < (int)group1.size() - 1) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "Graph is NOT bipartite." << endl;
    }
    
    return 0;
}