#include <iostream>
#include "Graph.h"

using namespace std;

// Assignment 4 - Graph Algorithm
// Need to find minimum semesters for course prerequisites

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
    } else {
        cout << "Success! All 15 courses processed." << endl;
    }
    
    return 0;
}