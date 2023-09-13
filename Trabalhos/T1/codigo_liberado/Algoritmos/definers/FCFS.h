#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <iostream>
#include <vector>
// #include "read_file.cc"
#include "../definers/Process.h"

class FCFS_Scheduler : public Process {
    public:
        FCFS_Scheduler();
        ~FCFS_Scheduler();
 
        void escalonate(); // método para realizar o escalonamento do processo
        void endscalonate(); // método para finalizar o escalonamento do processo
        void print(); // método para printar o escalonamento
        FCFS_Scheduler *pointer;

        int getTimer() {return Timer;};
        void setTimer() {Timer++;};

    private:
        std::list<std::pair<int, std::pair<int, int>>> dictList; // dicionário de processos
        int Timer = 0; // 
};

#endif // FCFS_SCHEDULER_H
