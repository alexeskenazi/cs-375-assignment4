#include <iostream>
#include <ctime>
#include "Graph.h"

using namespace std;

// Assignment 4 - Graph Algorithm
// Need to find minimum semesters for course prerequisites using DAG
// Note: Skipping explicit cycle detection - topological sort will catch cycles

int main() {
    cout << "CS 375 Assignment 4 - Graph Algorithm" << endl;
    
    // Create graph with 15 courses (cs1 through cs15)
    Graph g(15);
    
    // Set course names from cs1 to cs15
    for (int i = 0; i < 15; i++) {
        g.setCourseName(i, "cs" + to_string(i + 1));
    }
    
    // Build the prerequisite structure (directed edges from prereq to course)
    // Note: array index starts at 0, so cs1 = index 0, cs2 = index 1, etc.
    
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
    
    // Display the graph structure and prerequisite counts
    g.printGraph();
    g.printPrereqCount();
    
    // Perform topological sorting - this will detect cycles implicitly
    cout << "\n--- Performing Topological Sort ---" << endl;
    vector<int> order = g.topSort();
    
    // Check if all courses were processed (cycle detection)
    if (order.size() != 15) {
        cout << "ERROR: Could only process " << order.size() << " out of 15 courses." << endl;
        cout << "This indicates a CYCLE in the prerequisite structure!" << endl;
        cout << "Impossible to complete all courses." << endl;
        return 1;
    }
    
    cout << "All courses can be scheduled (no cycles detected)." << endl;
    cout << "Valid course order: ";
    for (int i = 0; i < (int)order.size(); i++) {
        cout << g.courseNames[order[i]];
        if (i < (int)order.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    
    // Calculate minimum semesters using level-based topological sort
    // This finds the longest path in the DAG
    cout << "\n--- Minimum Semesters Calculation ---" << endl;
    clock_t start = clock();
    int answer = g.calculateMinSemesters();
    clock_t end = clock();
    
    cout << "\nMINIMUM SEMESTERS NEEDED: " << answer << endl;
    
    // Show timing (required for assignment)
    double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << time << " milliseconds" << endl;
    
    // Check if graph is bipartite using BFS coloring
    // Bipartite means courses can be split into 2 groups with no prereqs within groups
    cout << "\n--- Bipartite Check ---" << endl;
    vector<int> groups;
    if (g.isBipartite(groups)) {
        cout << "Graph is bipartite!" << endl;
        
        // Separate courses into the two groups
        vector<int> group0, group1;
        for (int i = 0; i < 15; i++) {
            if (groups[i] == 0) {
                group0.push_back(i);
            } else {
                group1.push_back(i);
            }
        }
        
        // Display both groups
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