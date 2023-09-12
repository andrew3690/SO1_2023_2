CXX = g++
CXXFLAGS = -std=c++11 -I/definers

SRCS = Exec.cpp Process.cpp  CPU.cpp FCFS.cpp# Add Process.cpp here

all: program

program: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run:
	./program

clean:
	rm -f program

