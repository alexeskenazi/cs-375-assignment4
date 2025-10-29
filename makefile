CXX = g++
CXXFLAGS = -Wall -Wsign-compare -g -std=c++11

all: graph_assignment lp_assignment simplex_solver

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

test_graph: graph_assignment
	./graph_assignment

test_lp: lp_assignment
	./lp_assignment

test_simplex: simplex_solver
	./simplex_solver

test: graph_assignment lp_assignment simplex_solver
	./graph_assignment
	./lp_assignment
	./simplex_solver

run: clean test
	./graph_assignment
	./lp_assignment
	./simplex_solver

clean:
	rm -f *.o graph_assignment lp_assignment simplex_solver