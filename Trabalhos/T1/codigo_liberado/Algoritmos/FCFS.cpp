#include "definers/FCFS.h"

FCFS_Scheduler::FCFS_Scheduler() {
    std::cout << "Iniciando o escalonador FCFS" << "\n";
    incrementtimer();
}

void FCFS_Scheduler::escalonate(std::vector<Process*> processVector) {
    std::cout << "Entrei no escalonador ! timer:" << gettimer() << "\n";

    while (Process::Blocked_queue.size() > 0 || Process::Ready_queue.size() > 0 || running_process != nullptr) {
        sleep(1);

        for (int i = 0; i < Process::Blocked_queue.size(); i++) {
            Process* blocked_process = Process::Blocked_queue.front();
            if (blocked_process->gettime() == clock_counter) {
                blocked_process->makeready(blocked_process->getid(), clock_counter); // coloca processo na lista de pronto
            }
        }
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
            process->endprocess(clock_counter);
            running_process = nullptr;
        }
        clock_counter++;
    }
    // for (auto& process: processVector) {
    //     std::cout << "Entrei no loop dos processos ! \n";
    //     std::cout << "Id: " << process->getid() << "\n";

    //     process->start();
    // }

    std::cout << "Sai do loop dos processos ! Timer:" << gettimer() << "\n";
}

FCFS_Scheduler::~FCFS_Scheduler(){
    std::cout << "Finalizando o escalonador \n";
}