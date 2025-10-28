CXX = g++
CXXFLAGS = -Wall -Wsign-compare -g -std=c++11

all: floyd_warshall lcs_three partition_dp lcs_two

floyd_warshall: floyd_warshall.o
	$(CXX) $(CXXFLAGS) floyd_warshall.o -o floyd_warshall

floyd_warshall.o: floyd_warshall.cpp
	$(CXX) $(CXXFLAGS) -c floyd_warshall.cpp

submission: floyd_warshall
	cp floyd_warshall submission

lcs_three: lcs_three.o
	$(CXX) $(CXXFLAGS) lcs_three.o -o lcs_three

lcs_three.o: lcs_three.cpp
	$(CXX) $(CXXFLAGS) -c lcs_three.cpp

partition_dp: partition_dp.o
	$(CXX) $(CXXFLAGS) partition_dp.o -o partition_dp

partition_dp.o: partition_dp.cpp
	$(CXX) $(CXXFLAGS) -c partition_dp.cpp

run: floyd_warshall
	./floyd_warshall input.txt output.txt

test: floyd_warshall
	./floyd_warshall

lcs: lcs_three
	./lcs_three

partition: partition_dp
	./partition_dp

lcs_two: lcs_two.o
	$(CXX) $(CXXFLAGS) lcs_two.o -o lcs_two

lcs_two.o: lcs_two.cpp
	$(CXX) $(CXXFLAGS) -c lcs_two.cpp

lcs2: lcs_two
	./lcs_two

clean:
	rm -f *.o floyd_warshall submission lcs_three partition_dp lcs_two