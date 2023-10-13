#ifndef GENERIC_SCHEDULER_H
#define GENERIC_SCHEDULER_H

#include <vector>
#include <memory>
#include "../definers/Process.h"
#include "unistd.h"


class Generic_Scheduler{
    public:
        Generic_Scheduler();
        ~Generic_Scheduler();

        //void escalonate(std::vector<Process*> processVector); // execuçao do escalonamento
        void exec(Process* process, int time);
        int clock_counter = 0;
        Process* running_process = nullptr; // ponteiro para o processo atualmente em execução

};

#endif