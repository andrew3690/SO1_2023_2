#include "definers/FCFS.h"

FCFS_Scheduler::FCFS_Scheduler(const std::vector<std::shared_ptr<Process>>& processes): processQueue(processes) {
    std::cout << "Iniciando o escalonador FCFS" << "\n";
    escalonate();
}

void FCFS_Scheduler::escalonate() {
    if (!processQueue.empty()) {
        // Get the first process from the queue
        std::shared_ptr<Process> firstProcess = processQueue.front();

        // Start processing the first process
        firstProcess->start();

        // Remove the first process from the queue
        processQueue.erase(processQueue.begin());
    } else {
        // Chama a finalização do escalonador
        std::cout << "Lista de prontos vazia ! \n";
    }
}

FCFS_Scheduler::~FCFS_Scheduler(){
    std::cout << "Finalizando o escalonador \n";
}