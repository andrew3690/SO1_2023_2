#include "FCFS.h"

FCFS_Scheduler::FCFS_Scheduler(int id, int data_int, int time, int priority): 
Process(id, data_int, time, priority){
    // inserindo o processo na lista de prioridades do algoritmo
    // dado que o algoritmo não possui prioridades setadas, é só inserir o par na lista
    // ao escalonar é só obter o processo mais recente
    dictList.push_back(std::make_pair(id,std::make_pair(data_int,time)));
};

void FCFS_Scheduler::escalonate(){
    // retira o processo da fila de prontos e utiliza no loop de
    pointer->dictList.pop_front();
    std::cout << "Contexto: "<<pointer->getid();
    
};

void FCFS_Scheduler::endscalonate(){
    // retira o processo 
};