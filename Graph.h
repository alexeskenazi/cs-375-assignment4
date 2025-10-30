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
    
    // Calculate minimum semesters - each course semester = 1 + max of prerequisite semesters
    int calculateMinSemesters(int maxCourse = -1) {
        if (maxCourse == -1) maxCourse = numCourses - 1;
        vector<int> semester(numCourses, 0);
        vector<int> order = topSort();
        
        // Process in topological order
        for (int course : order) {
            int maxPrereqSemester = 0;
            
            // Find max semester of all prerequisites
            for (int i = 0; i < numCourses; i++) {
                for (int next : adj[i]) {
                    if (next == course) {
                        // i is a prerequisite of course
                        maxPrereqSemester = max(maxPrereqSemester, semester[i]);
                    }
                }
            }
            
            semester[course] = maxPrereqSemester + 1;
        }
        
        // Show when each course can be taken
        cout << "Course scheduling:" << endl;
        for (int i = 0; i <= maxCourse; i++) {
            cout << courseNames[i] << " - semester " << semester[i] << endl;
        }
        
        // Find maximum semester
        int maxSem = 0;
        for (int i = 0; i <= maxCourse; i++) {
            maxSem = max(maxSem, semester[i]);
        }
        
        return maxSem;
    }
    
    // Check for cycles using DFS - learned about white/gray/black nodes
    bool hasCycleDFS(int node, vector<int>& color) {
        color[node] = 1; // gray - visiting
        
        for (int neighbor : adj[node]) {
            if (color[neighbor] == 1) {
                // Found back edge - cycle!
                return true;
            }
            if (color[neighbor] == 0 && hasCycleDFS(neighbor, color)) {
                return true;
            }
        }
        
        color[node] = 2; // black - finished
        return false;
    }
    
    bool hasCycle() {
        vector<int> color(numCourses, 0); // 0=white, 1=gray, 2=black
        
        for (int i = 0; i < numCourses; i++) {
            if (color[i] == 0) {
                if (hasCycleDFS(i, color)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // Check if graph is bipartite - can color with 2 colors
    bool isBipartite(vector<int>& group) {
        group.assign(numCourses, -1);
        queue<int> q;
        
        // Check each connected component
        for (int start = 0; start < numCourses; start++) {
            if (group[start] == -1) {
                // Start BFS from this node
                group[start] = 0;
                q.push(start);
                
                while (!q.empty()) {
                    int current = q.front();
                    q.pop();
                    
                    for (int next : adj[current]) {
                        if (group[next] == -1) {
                            // Color with opposite color
                            group[next] = 1 - group[current];
                            q.push(next);
                        } else if (group[next] == group[current]) {
                            // Same color - not bipartite
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

#endif