CC = g++
CFLAGS = -std=c++11 -Wall -g

all: program

program: main.o Simulador.o SubsAlgorithm.o OPT.o LRU.o FIFO.o
	$(CC) $(CFLAGS) main.o Simulador.o SubsAlgorithm.o OPT.o LRU.o FIFO.o -o program

main.o:	main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o -c

Simulador.o: Simulador.cpp
	$(CC) $(CFLAGS) Simulador.cpp -o Simulador.o -c

SubsAlgorithm.o: SubsAlgorithm.cpp
	$(CC) $(CFLAGS) SubsAlgorithm.cpp -o SubsAlgorithm.o -c

OPT.o: OPT.cpp
	$(CC) $(CFLAGS) OPT.cpp -o OPT.o -c

LRU.o: LRU.cpp
	$(CC) $(CFLAGS) LRU.cpp -o LRU.o -c

FIFO.o: FIFO.cpp
	$(CC) $(CFLAGS) FIFO.cpp -o FIFO.o -c

run:
	./program 4 ./input/vsim-exemplo.txt

clean:
	rm -rf *.o *~ program