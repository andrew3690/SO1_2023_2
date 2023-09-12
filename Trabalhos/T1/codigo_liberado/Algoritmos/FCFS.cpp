#include "definers/FCFS.h"

FCFS_Scheduler::FCFS_Scheduler(int id, int data_int, int time, int priority): Process(id, data_int, time, priority){

    // inserindo o processo na lista de processos do algoritmo
    // dado que o algoritmo não possui prioridades setadas, é só inserir o par na lista
    // ao escalonar é só obter o processo mais recente
    std::cout << "Iniciando o escalonador FCFS" << "\n";

    //Cria o processo e o insere na fila de prontos
    Process* process = new Process(id, data_int, time, priority);    
    // dictList.push_back(std::make_pair(id,std::make_pair(data_int,time)));
};

void FCFS_Scheduler::escalonate(){
    // Verfica se a lista de prontos está vazia..
    if (!Ready_queue.empty()) {
        // Obtendo o primeiro elemento da lista de prontos ....
        Process * firstProcess = Ready_queue.front();
        
        //...retira o elemento da fila...
        Ready_queue.pop_front();

        // ...Inicia o processamento
        firstProcess->start();

    } else{
        // caso a fila esteja vazia, chama-se o destrutor da classe, sinalizando a finalização do escalonamento
        FCFS_Scheduler::~FCFS_Scheduler();
    }
};

FCFS_Scheduler::~FCFS_Scheduler(){
    delete this;
}