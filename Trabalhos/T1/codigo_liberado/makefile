CXX = g++
CXXFLAGS = -std=c++11

SRC = read_file.cc

all: program

program: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

run:
	./program

clean:
	rm -f program
