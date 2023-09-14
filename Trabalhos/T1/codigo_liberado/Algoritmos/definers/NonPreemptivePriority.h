#ifndef NONPPRIORITY_SCHEDULER_H
#define NONPPRIORITY_SCHEDULER_H

#include <vector>
#include "Process.h"
#include <memory>

class NonPPriorityScheduler
{
    public:
        NonPPriorityScheduler(const std::vector<std::shared_ptr<Process>>& processes);
        ~NonPPriorityScheduler();

        void escalonate();
        void sort();

    private:
        vector<Process> process_list;
};

#endif
