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
    //clock_counter++;
}


void SJF_Scheduler::escalonate(std::vector<Process*> processVector) // lista de blocked
{
    while (Process::Blocked_queue.size() > 0) {
        sleep(1);

        for (int i = 0; i < Process::Blocked_queue.size(); i++) {
            Process* blocked_process = Process::Blocked_queue.front();
            if (blocked_process->gettime() == clock_counter) {
                blocked_process->makeready(blocked_process->getid()); // coloca processo na lista de pronto
            }
        }
        Process::Ready_queue = sort(Process::Ready_queue); // ordena

        Process* process = Process::Ready_queue.front();
        process->start();

        if (process->getduration() > 0)
        {
            exec(process, clock_counter);
        }

        if (process->getduration() == 0) {
            process->stop();
            process->endprocess();
            // Process* process = Process::Ready_queue.front();
        }
        //clock_counter++;

    }
    // process_list = processVector;
    // sort();
    // int counter = 0;
    // Process* process = process_list.front();
    // while (process_list.size() > 0 && process->getduration() > 0) {
    //     sleep(1);
    //     process->exec();
    //     std::cout << "executou no instante " << counter << "-" << counter+1 << " " << process->getid() << std::endl;
    //     if (process->getduration() == 0) {
    //         process->endprocess();
    //         process_list.erase(process_list.begin());
    //         std::cout << "terminou " <<  "\n";
    //         process = process_list.front();
    //     }
    //     counter++;
    // }
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
