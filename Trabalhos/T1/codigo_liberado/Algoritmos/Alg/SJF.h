#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include <vector>
#include <definers/Process.h>

using namespace std;


class ShortestJobFirst_Scheduler
{
    public:
        ShortestJobFirst_Scheduler();


        void add_process(Process process_ready);
        Process pop_first();

    private:
        vector<Process> process_list; // lista de processos

};

#endif