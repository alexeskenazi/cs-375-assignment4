CXX = g++
CXXFLAGS = -Wall -Wsign-compare -g -std=c++11

all: graph_assignment lp_assignment simplex_solver cycle_detection 5_topological_sort

graph_assignment: graph_assignment.o
	$(CXX) $(CXXFLAGS) graph_assignment.o -o graph_assignment

graph_assignment.o: graph_assignment.cpp
	$(CXX) $(CXXFLAGS) -c graph_assignment.cpp

lp_assignment: lp_assignment.o
	$(CXX) $(CXXFLAGS) lp_assignment.o -o lp_assignment

lp_assignment.o: lp_assignment.cpp
	$(CXX) $(CXXFLAGS) -c lp_assignment.cpp

simplex_solver: simplex_solver.o
	$(CXX) $(CXXFLAGS) simplex_solver.o -o simplex_solver

simplex_solver.o: simplex_solver.cpp
	$(CXX) $(CXXFLAGS) -c simplex_solver.cpp

cycle_detection: cycle_detection.o
	$(CXX) $(CXXFLAGS) cycle_detection.o -o cycle_detection

cycle_detection.o: cycle_detection.cpp
	$(CXX) $(CXXFLAGS) -c cycle_detection.cpp

5_topological_sort: 5_topological_sort.o
	$(CXX) $(CXXFLAGS) 5_topological_sort.o -o 5_topological_sort

5_topological_sort.o: 5_topological_sort.cpp
	$(CXX) $(CXXFLAGS) -c 5_topological_sort.cpp

test_graph: graph_assignment
	./graph_assignment

test_lp: lp_assignment
	./lp_assignment

test_simplex: simplex_solver
	./simplex_solver

test_cycle: cycle_detection
	./cycle_detection

test_topo: 5_topological_sort
	./5_topological_sort

test: graph_assignment lp_assignment simplex_solver cycle_detection 5_topological_sort
	./graph_assignment
	./lp_assignment
	./simplex_solver
	./cycle_detection
	./5_topological_sort

run: clean test
	./graph_assignment
	./lp_assignment
	./simplex_solver
	./cycle_detection
	./5_topological_sort

clean:
	rm -f *.o graph_assignment lp_assignment simplex_solver cycle_detection 5_topological_sort