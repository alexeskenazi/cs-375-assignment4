# 2025 Fall – Assignment 4 (CS 375)

## Part B: Programming Part (26%)

### B.1 Graph Algorithm (16%)

Suppose a CS curriculum consists of n courses, all of them mandatory.  
The prerequisite graph G has a node for each course, and an edge from course v to course w if and only if v is a prerequisite for w.

Find an algorithm that works directly with this graph representation, and computes the minimum number of semesters necessary to complete the curriculum.  
(Assume that a student can take any number of courses in one semester.)

#### Example

The CS Department requires fifteen one-semester courses with the prerequisites shown below:

cs1

cs2 

cs3

cs4 requires cs2

cs5 requires cs4

cs6 requires cs1 and cs3

cs7 requires cs4

cs8 requires cs5 and cs6

cs9 requires cs7

cs10 requires cs9

cs11 requires cs8

cs12 requires cs3

cs13 requires cs6

cs14 requires cs4 and cs6

cs15 requires cs14


Your task is to determine the minimum number of semesters needed to finish the degree.

> Hint: Represent the courses and their prerequisites as a DAG. Use an appropriate data structure to represent the graph.

#### Deliverables

1. Manually plot the DAG (3%)  
2. Explain the algorithm you are going to implement by providing pseudocode, and indicate:
   - The minimum number of semesters necessary to finish the degree.  
   - The time complexity and space complexity. (3%)  
3. Write and run your program to print out the result for verification:
   - Minimum number of semesters  
   - Running time (10%)

---

### B.2 Linear Programming (10%)

Design and implement a linear programming algorithm to solve the following minimum cost problem.

The liquid portion of a diet is to provide at least 300 calories, 36 units of vitamin A, and 90 units of vitamin C daily.

A cup of dietary drink X provides:
- 60 calories  
- 12 units of vitamin A  
- 10 units of vitamin C  

A cup of dietary drink Y provides:
- 60 calories  
- 6 units of vitamin A  
- 30 units of vitamin C  

Now, suppose that:
- Drink X costs $0.12 per cup  
- Drink Y costs $0.15 per cup  

How many cups of each drink should be consumed each day to minimize the cost and still meet the stated daily requirements?

Print out:
- The minimum cost  
- The number of cups of drink X  
- The number of cups of drink Y  
- The running time  

---

### B.3 [Optional Extra point 10%]

To answer the Question #9 (Part A), implement the Simplex Algorithm and display the results by your program, and print out the running time.

---
