#include "definers/FCFS.h"

FCFS_Scheduler::FCFS_Scheduler(){
    // inserindo o processo na lista de processos do algoritmo
    // dado que o algoritmo não possui prioridades setadas, é só inserir o par na lista
    // ao escalonar é só obter o processo mais recente
    std::cout << "Iniciando o escalonador FCFS" << "\n";
    escalonate();
};

void FCFS_Scheduler::escalonate(){
    // Verfica se a lista de prontos está vazia..
    std::cout << "Iniciando o escalonamento" << "\n";
    if (!Ready_queue.empty()) {
        // std::cout << "Retirando o primeiro elemento da lista de prontos" << "\n";
        // Obtendo o primeiro elemento da lista de prontos ....
        Process * firstProcess = Ready_queue.front();

        // ...Inicia o processamento
        firstProcess->start();

    } else {
        // caso a fila esteja vazia, chama-se o destrutor da classe, sinalizando a finalização do escalonamento
        FCFS_Scheduler::~FCFS_Scheduler();
    }
};

void FCFS_Scheduler::endscalonate(){
    // Realizar chamadas dos processos e chamar o destrutor
    this->~FCFS_Scheduler();
}

FCFS_Scheduler::~FCFS_Scheduler(){
    delete this;
}