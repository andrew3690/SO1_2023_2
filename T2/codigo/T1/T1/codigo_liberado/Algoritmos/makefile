CXX = g++
CXXFLAGS = -std=c++11 -Idefiners -g

SRCS = $(wildcard *.cpp)   # This will include all .cpp files in the current directory
HDRS = $(wildcard definers/*.h)   # This will include all .h files in the 'definers' directory

all: program

program: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

run:
	./program

clean:
	rm -f program
