#ifndef ROUND_ROBIN
#define ROUND_ROBIN

#include <vector>
#include <memory>
#include "Process.h"


class Round_robin
{
    public:
        Round_robin();
        ~Round_robin();

        void escalonate();
        void schedule();
        void sort();

    private:
        vector<Process> process_list;
};

#endif