#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include <vector>
#include <memory>
#include "../definers/Process.h"

using namespace std;


class SJF_Scheduler{
    public:
        SJF_Scheduler(const std::vector<std::shared_ptr<Process>>& processes);
        ~SJF_Scheduler();
        void add_process(Process *process1);

        void escalonate(); // execuçao do escalonamento
        void sort();
        
    private:
        vector<Process> process_list; // lista de processos

};

#endif