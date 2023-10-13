#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <iostream>
#include <vector>
#include <memory>
#include "../definers/Process.h"
#include "GenericScheduler.h"

class FCFS_Scheduler: public Process, private Generic_Scheduler {
    public:

        FCFS_Scheduler();
        void escalonate(std::vector<Process*> processVector);
        ~FCFS_Scheduler();

        int gettimer(){return timer;};
        void incrementtimer(){timer++;};

    private:
        int timer;
};

#endif // FCFS_SCHEDULER_H
