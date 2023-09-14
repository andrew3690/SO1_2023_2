#include "definers/FCFS.h"

FCFS_Scheduler::FCFS_Scheduler() {
    std::cout << "Iniciando o escalonador FCFS" << "\n";
    incrementtimer();
}

void FCFS_Scheduler::escalonate(std::vector<Process*> processVector) {
    std::cout << "Entrei no escalonador ! timer:" << gettimer() << "\n";

    for (auto& process: processVector) {
        std::cout << "Entrei no loop dos processos ! \n";
        std::cout << "Id: " << process->getid() << "\n";

        process->start();
    }

    std::cout << "Sai do loop dos processos ! Timer:" << gettimer() << "\n";
}

FCFS_Scheduler::~FCFS_Scheduler(){
    std::cout << "Finalizando o escalonador \n";
}