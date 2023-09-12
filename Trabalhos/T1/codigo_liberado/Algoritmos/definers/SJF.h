#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include <vector>
#include "../definers/Process.h"

using namespace std;


class ShortestJobFirst_Scheduler
{
    public:
        ShortestJobFirst_Scheduler();
        ~ShortestJobFirst_Scheduler();


        void add_process(int process_ready);
        int schedule();
        void sort();

    private:
        vector<int> process_list; // lista de processos

};

#endif