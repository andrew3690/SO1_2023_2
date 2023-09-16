#include "definers/SJF.h"
#include "unistd.h"


SJF_Scheduler::SJF_Scheduler(){
    std::cout << "Inciando o escalonador SJF";
} //constructor

SJF_Scheduler::~SJF_Scheduler(){} //destructor


void SJF_Scheduler::exec(Process* process, int time)
{
    std::cout << "executou no tempo: " << time << "\n";
    process->dectime(); // decrementa a duração restante
}


void SJF_Scheduler::escalonate(std::vector<Process*> processVector) // lista de blocked
{
    while (Process::Blocked_queue.size() > 0 || Process::Ready_queue.size() > 0 || running_process != nullptr) {
        sleep(1);

        for (int i = 0; i < Process::Blocked_queue.size(); i++) {
            Process* blocked_process = Process::Blocked_queue.front();
            if (blocked_process->gettime() == clock_counter) {
                blocked_process->makeready(blocked_process->getid()); // coloca processo na lista de pronto
            }
        }
        Process::Ready_queue = sort(Process::Ready_queue); // ordena
        Process* process;

        if (running_process == nullptr) {
            process = Process::Ready_queue.front();
            process->start();
            running_process = process;
        }

        if (process->getduration() > 0)
        {
            exec(process, clock_counter);
        }

        if (process->getduration() == 0) {
            process->stop();
            process->endprocess();
            running_process = nullptr;
        }
        clock_counter++;
    }
}

vector<Process*> SJF_Scheduler::sort(vector<Process*> process_list)
{
    int size = process_list.size();
    for (int step = 1; step < size; step++) {
        Process* key = process_list[step];
        int j = step - 1;

        while (j >= 0 && key->getduration() < process_list.at(j)->getduration()) {
            process_list[j + 1] = process_list[j];
            --j;
        };
        process_list[j + 1] = key;
    }
    return process_list;
};
