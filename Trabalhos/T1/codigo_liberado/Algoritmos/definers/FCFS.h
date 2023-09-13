#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <iostream>
#include <vector>
#include <memory>
#include "../definers/Process.h"

class FCFS_Scheduler {
    public:

        FCFS_Scheduler(const std::vector<std::shared_ptr<Process>>& processes);
        void escalonate();
        void endescalonate();
        ~FCFS_Scheduler();

    private:
        std::vector<std::shared_ptr<Process>> processQueue;
};

#endif // FCFS_SCHEDULER_H
