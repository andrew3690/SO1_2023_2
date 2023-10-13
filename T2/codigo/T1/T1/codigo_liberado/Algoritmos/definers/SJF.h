#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include <vector>
#include <memory>
#include "../definers/Process.h"
#include "GenericScheduler.h"

using namespace std;


class SJF_Scheduler: private Generic_Scheduler {
    public:
        SJF_Scheduler();
        ~SJF_Scheduler();

        void escalonate(std::vector<Process*> processVector); // execuçao do escalonamento
        vector<Process*> sort(vector<Process*> process_list);
        void exec(Process* process, int time);

};

#endif