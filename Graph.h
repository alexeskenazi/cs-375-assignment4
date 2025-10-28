#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

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
    
    // Topological sort - learned this is like BFS but remove prerequisites first
    vector<int> topSort() {
        vector<int> prereqs(numCourses, 0);
        vector<int> result;
        queue<int> ready;
        
        // Count prerequisites 
        for (int i = 0; i < numCourses; i++) {
            for (int course : adj[i]) {
                prereqs[course]++;
            }
        }
        
        // Start with courses that have no prerequisites
        for (int i = 0; i < numCourses; i++) {
            if (prereqs[i] == 0) {
                ready.push(i);
            }
        }
        
        // Keep taking courses until done
        while (!ready.empty()) {
            int current = ready.front();
            ready.pop();
            result.push_back(current);
            
            // Remove this course as a prerequisite for others
            for (int next : adj[current]) {
                prereqs[next]--;
                if (prereqs[next] == 0) {
                    ready.push(next);
                }
            }
        }
        
        return result;
    }
};

#endif