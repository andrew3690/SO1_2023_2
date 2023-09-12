#ifndef NONPPRIORITY_SCHEDULER_H
#define NONPPRIORITY_SCHEDULER_H

#include <vector>
#include "../definers/Process.h"


class NonPPriorityScheduler
{
    public:
        NonPPriorityScheduler();
        ~NonPPriorityScheduler();

        void schedule();
        void sort();

    private:
        vector<Process> process_list;
};

#endif
