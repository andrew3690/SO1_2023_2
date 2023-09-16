#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include <vector>
#include <algorithm>
#include "Process.h"
#include "GenericScheduler.h"

class PriorityScheduler: public Process, private Generic_Scheduler{
    public:
        PriorityScheduler();
        ~PriorityScheduler();

        void escalonate(std::vector<Process*> processVector, int flag);
        void exec(Process *process, int flag); // metodo de execucao do escalonador, flag de execucao
        void tick(){timer_++;}; // tick do relogio do processador, sinalizando que ocorreu uma execucao
        int calculatedynamicpriority(int TempoExecTotal, int tempodequantum);
        std::vector<Process*> sortbypriority(std::vector<Process*> process_list);

    private:
        int timer_; // timer do escalonador

};

#endif
