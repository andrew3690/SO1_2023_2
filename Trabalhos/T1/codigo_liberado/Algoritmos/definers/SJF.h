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

        void escalonate(); // execuçao do escalonamento

    private:
        vector<Process> process_list; // lista de processos

};

#endif