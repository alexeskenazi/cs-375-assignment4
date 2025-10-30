CXX = g++
CXXFLAGS = -Wall -Wsign-compare -g -std=c++11

all: B1_graph_assignment B2_lp_assignment B3_simplex_solver 2b_cycle_detection 5_topological_sort

B1_graph_assignment: B1_graph_assignment.o
	$(CXX) $(CXXFLAGS) B1_graph_assignment.o -o B1_graph_assignment

B1_graph_assignment.o: B1_graph_assignment.cpp
	$(CXX) $(CXXFLAGS) -c B1_graph_assignment.cpp

B2_lp_assignment: B2_lp_assignment.o
	$(CXX) $(CXXFLAGS) B2_lp_assignment.o -o B2_lp_assignment

B2_lp_assignment.o: B2_lp_assignment.cpp
	$(CXX) $(CXXFLAGS) -c B2_lp_assignment.cpp

B3_simplex_solver: B3_simplex_solver.o
	$(CXX) $(CXXFLAGS) B3_simplex_solver.o -o B3_simplex_solver

B3_simplex_solver.o: B3_simplex_solver.cpp
	$(CXX) $(CXXFLAGS) -c B3_simplex_solver.cpp

2b_cycle_detection: 2b_cycle_detection.o
	$(CXX) $(CXXFLAGS) 2b_cycle_detection.o -o 2b_cycle_detection

2b_cycle_detection.o: 2b_cycle_detection.cpp
	$(CXX) $(CXXFLAGS) -c 2b_cycle_detection.cpp

5_topological_sort: 5_topological_sort.o
	$(CXX) $(CXXFLAGS) 5_topological_sort.o -o 5_topological_sort

5_topological_sort.o: 5_topological_sort.cpp
	$(CXX) $(CXXFLAGS) -c 5_topological_sort.cpp

test_graph: B1_graph_assignment
	./B1_graph_assignment

test_lp: B2_lp_assignment
	./B2_lp_assignment

test_simplex: B3_simplex_solver
	./B3_simplex_solver

test_cycle: 2b_cycle_detection
	./2b_cycle_detection

test_topo: 5_topological_sort
	./5_topological_sort

test: B1_graph_assignment B2_lp_assignment B3_simplex_solver 2b_cycle_detection 5_topological_sort
	./B1_graph_assignment
	./B2_lp_assignment
	./B3_simplex_solver
	./2b_cycle_detection
	./5_topological_sort

run: clean test
	./B1_graph_assignment
	./B2_lp_assignment
	./B3_simplex_solver
	./2b_cycle_detection
	./5_topological_sort

clean:
	rm -f *.o B1_graph_assignment B2_lp_assignment B3_simplex_solver 2b_cycle_detection 5_topological_sort