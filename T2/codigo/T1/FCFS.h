#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <iostream>
#include <vector>
// #include "read_file.cc"
#include "definers/Process.h"

class FCFS_Scheduler : public Process {
    public:
        FCFS_Scheduler(int id, int data_int, int time, int priority)
            : Process(id, data_int, time, priority){};
 
        void escalonate(); // método para realizar o escalonamento do processo
        void endscalonate(); // método para finalizar o escalonamento do processo
        void print(); // método para printar o escalonamento
    FCFS_Scheduler *pointer;

    private:
        std::list<std::pair<int, std::pair<int, int>>> dictList; // dicionário de processos
};

#endif // FCFS_SCHEDULER_H
