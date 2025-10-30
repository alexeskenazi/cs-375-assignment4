# B1 Graph Assignment Algorithm Guide

## Problem
Find the minimum number of semesters needed to complete all 15 CS courses given prerequisite constraints.

## Key Algorithms Used

### **Topological Sorting (Kahn's Algorithm)**
- **Purpose**: Find valid course ordering respecting prerequisites
- **Time Complexity**: O(V + E)
- **Algorithm Steps**:
  1. Count incoming edges (prerequisites) for each course
  2. Add courses with 0 prerequisites to queue
  3. Process courses from queue, removing them as prerequisites
  4. Add newly available courses to queue
  5. Continue until all courses processed

### **Implicit Cycle Detection**
- **Purpose**: Verify prerequisite structure is feasible (no circular dependencies)
- **Method**: Topological sort inherently detects cycles
- **Logic**: If topological sort can't process all courses, cycles exist

### **Minimum Semester Calculation**
- **Purpose**: Find the longest path in the DAG (critical path)
- **Algorithm**:
  1. Process courses in topological order
  2. For each course: semester = 1 + max(prerequisite semesters)
  3. Return maximum semester among all courses

## Results
- **Minimum Semesters**: 5
- **Time Complexity**: O(V + E)
- **Running Time**: ~0.16 ms

## Usage
```bash
./B1_graph_assignment [input_file] [output_file]
# Default: B1_input.txt → B1_output.txt
```

## Input Format
```
//** Directed Graph with N course (CSi --> CSj) **//
CS2 CS4
CS4 CS5
CS1 CS6
...
```

## Output Format
- Cycle detection result
- Topological sorted sequence  
- Edge type classification
- Minimum semesters needed
- Bipartite check (N/A for DAG)
- Running time

## Detailed Algorithm Implementation

### 1. **Topological Sort (Kahn's Algorithm)** - Graph.h:58-94
**Purpose**: Find a valid ordering of courses that respects prerequisites

```cpp
vector<int> topSort() {
    vector<int> prereqs(numCourses, 0);  // Count incoming edges (prerequisites)
    queue<int> ready;                    // Courses with no prerequisites
    
    // Step 1: Count prerequisites for each course
    for (int i = 0; i < numCourses; i++) {
        for (int course : adj[i]) {
            prereqs[course]++;  // Increment prerequisite count
        }
    }
    
    // Step 2: Add courses with 0 prerequisites to queue
    for (int i = 0; i < numCourses; i++) {
        if (prereqs[i] == 0) {
            ready.push(i);
        }
    }
    
    // Step 3: Process courses level by level
    while (!ready.empty()) {
        int course = ready.front();
        ready.pop();
        result.push_back(course);
        
        // Remove this course as a prerequisite
        for (int next : adj[course]) {
            prereqs[next]--;
            if (prereqs[next] == 0) {
                ready.push(next);  // Course now available
            }
        }
    }
}
```

### 2. **Minimum Semester Calculation** - Graph.h:96-132
**Purpose**: Find the longest path in the DAG (critical path scheduling)

```cpp
int calculateMinSemesters() {
    vector<int> semester(numCourses, 0);
    vector<int> order = topSort();  // Get valid course ordering
    
    // Process courses in topological order
    for (int course : order) {
        int maxPrereqSemester = 0;
        
        // Find the latest semester among all prerequisites
        for (int i = 0; i < numCourses; i++) {
            for (int prereqOf : adj[i]) {
                if (prereqOf == course) {  // i is prerequisite of course
                    maxPrereqSemester = max(maxPrereqSemester, semester[i]);
                }
            }
        }
        
        // This course goes in the semester after its latest prerequisite
        semester[course] = maxPrereqSemester + 1;
    }
    
    // Return the maximum semester needed
    return max_element(semester.begin(), semester.end());
}
```

## Key Insights

1. **DAG Structure**: Course prerequisites form a Directed Acyclic Graph (DAG)
2. **Topological Sort**: Ensures we process courses in dependency order
3. **Critical Path**: The minimum semesters = length of longest dependency chain
4. **Level Scheduling**: Each course is scheduled one semester after its latest prerequisite

## Example Walkthrough
For prerequisites: CS2→CS4, CS4→CS5, CS1→CS6, CS3→CS6

1. **Topological Order**: CS1, CS2, CS3, CS4, CS6, CS5
2. **Semester Assignment**:
   - CS1, CS2, CS3: semester 1 (no prerequisites)
   - CS4: semester 2 (needs CS2 from semester 1)
   - CS6: semester 2 (needs CS1, CS3 from semester 1)  
   - CS5: semester 3 (needs CS4 from semester 2)

**Result**: 3 minimum semesters needed

## Algorithm Complexity
- **Topological Sort**: O(V + E)
- **Semester Calculation**: O(V + E)  
- **Overall**: O(V + E) where V = courses, E = prerequisite edges