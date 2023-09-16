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
        vector<Process*> sort(vector<Process*> process_list);
        void exec(Process* process, int time);
        
    private:
        //vector<Process*> process_list; // lista de processos
        int clock_counter = 0;
        Process* running_process = nullptr;

};

#endif