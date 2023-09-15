#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include <vector>
#include <memory>
#include "../definers/Process.h"

using namespace std;


class SJF_Scheduler{
    public:
        SJF_Scheduler();
        ~SJF_Scheduler();

        void escalonate(std::vector<Process*> processVector); // execuçao do escalonamento
        void sort();
        
    private:
        vector<Process*> process_list; // lista de processos

};

#endif