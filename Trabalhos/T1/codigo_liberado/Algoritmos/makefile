CXX = g++
CXXFLAGS = -std=c++11

SRCS = Exec.cpp Process.cpp  CPU.cpp# Add Process.cpp here

all: program

program: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run:
	./program

clean:
	rm -f program

