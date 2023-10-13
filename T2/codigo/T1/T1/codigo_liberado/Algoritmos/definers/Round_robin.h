#ifndef ROUND_ROBIN
#define ROUND_ROBIN

#include <vector>
#include <memory>
#include "Process.h"
#include "GenericScheduler.h"


class Round_robin: private Generic_Scheduler
{
    public:
        Round_robin();
        ~Round_robin();

        void escalonate();

    private:
        const int quantum = 2; // valor do quantum em segundos
};

#endif