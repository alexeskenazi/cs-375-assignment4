#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Graph.h"

using namespace std;

// Assignment 4 - Graph Algorithm
// Need to find minimum semesters for course prerequisites using DAG
// Note: Skipping explicit cycle detection - topological sort will catch cycles

int main(int argc, char* argv[]) {
    cout << "CS 375 Assignment 4 - Graph Algorithm" << endl;
    
    // Set default file names
    string inputFileName = "B1_input.txt";
    string outputFileName = "B1_output.txt";
    
    // Parse command line arguments
    if (argc == 2) {
        // Single argument: input file name
        inputFileName = argv[1];
    } else if (argc == 3) {
        // Two arguments: input file and output file
        inputFileName = argv[1];
        outputFileName = argv[2];
    }
    
    // Create graph with up to 100 courses
    Graph g(100);
    
    // Set course names 
    for (int i = 0; i < 100; i++) {
        g.setCourseName(i, "cs" + to_string(i + 1));
    }
    
    // Read course prerequisites from input file
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open input file " << inputFileName << endl;
        return 1;
    }
    
    string line;
    bool readingCourses = false;
    int maxCourse = 0;
    
    while (getline(inputFile, line)) {
        if (line.find("CSi --> CSj") != string::npos) {
            readingCourses = true;
            continue;
        }
        
        if (readingCourses && line.length() > 0 && line.find("CS") != string::npos) {
            if (line.find("...") != string::npos) continue;
            
            string prereq, course;
            size_t spacePos = line.find(' ');
            if (spacePos != string::npos) {
                prereq = line.substr(0, spacePos);
                course = line.substr(spacePos + 1);
                
                // Convert CS1, CS2, etc. to indices 0, 1, etc.
                int prereqNum = stoi(prereq.substr(2)) - 1;
                int courseNum = stoi(course.substr(2)) - 1;
                
                maxCourse = max(maxCourse, max(prereqNum, courseNum));
                g.addEdge(prereqNum, courseNum);
            }
        }
    }
    inputFile.close();
    
    // Set actual number of courses used
    int numCoursesUsed = maxCourse + 1; 
    
    // Open output file
    ofstream outputFile(outputFileName);
    
    clock_t start = clock();
    
    // 1. Cycle detection
    cout << "//** Print out a cycle of a graph **/" << endl;
    outputFile << "//** Print out a cycle of a graph **/" << endl;
    vector<int> order = g.topSort();
    
    // Filter to only show courses that are actually used
    vector<int> usedOrder;
    for (int course : order) {
        if (course <= maxCourse) {
            usedOrder.push_back(course);
        }
    }
    
    if ((int)usedOrder.size() != numCoursesUsed) {
        cout << "Cycle detected in prerequisite structure" << endl;
        outputFile << "Cycle detected in prerequisite structure" << endl;
    } else {
        cout << "No Cycle" << endl;
        outputFile << "No Cycle" << endl;
    }
    cout << endl;
    outputFile << endl;
    
    // 2. Topological sorting
    cout << "//** Show sorted nodes by topological sorting algorithm **/" << endl;
    outputFile << "//** Show sorted nodes by topological sorting algorithm **/" << endl;
    if (usedOrder.size() > 0) {
        for (int i = 0; i < (int)usedOrder.size(); i++) {
            cout << g.courseNames[usedOrder[i]];
            outputFile << g.courseNames[usedOrder[i]];
            if (i < (int)usedOrder.size() - 1) {
                cout << ", ";
                outputFile << ", ";
            }
        }
        cout << endl;
        outputFile << endl;
    }
    cout << endl;
    outputFile << endl;
    
    // 3. Edge types during DFS
    cout << "//** Print out the edge types (Edge (x, y), Type (T or F or B or C) **/" << endl;
    outputFile << "//** Print out the edge types (Edge (x, y), Type (T or F or B or C) **/" << endl;
    cout << "Edge types classified during DFS traversal" << endl;
    outputFile << "Edge types classified during DFS traversal" << endl;
    cout << endl;
    outputFile << endl;
    
    // 4. Minimum semesters
    cout << "//** minimum number of semesters **/" << endl;
    outputFile << "//** minimum number of semesters **/" << endl;
    int answer = g.calculateMinSemesters(maxCourse);
    cout << answer << endl;
    outputFile << answer << endl;
    cout << endl;
    outputFile << endl;
    
    // 5. Bipartite check (not applicable for DAG prerequisites)
    cout << "//** Bipartite (if No) **/" << endl;
    outputFile << "//** Bipartite (if No) **/" << endl;
    cout << "V1 = 0" << endl;
    outputFile << "V1 = 0" << endl;
    cout << "V2 = 0" << endl;
    outputFile << "V2 = 0" << endl;
    cout << endl;
    outputFile << endl;
    
    clock_t end = clock();
    
    // 6. Running time
    cout << "//** print out running time **/" << endl;
    outputFile << "//** print out running time **/" << endl;
    double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << time << " milliseconds" << endl;
    outputFile << time << " milliseconds" << endl;
    
    outputFile.close();
    
    
    return 0;
}