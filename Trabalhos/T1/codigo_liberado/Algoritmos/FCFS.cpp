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
    // retira o processo da fila de prontos e utiliza no loop de
    if (!Ready_queue.empty()) {  // Check if the list is not empty
        // Obtendo o primeiro elemento da lista de prontos, e retirando-o da fila de prontos
        Process * firstProcess = Ready_queue.front();
        Ready_queue.pop_front();

        // realizar troca de contexto da CPU para o processo que será utilizado aqui
    }else{
        // caso a fila esteja vazia, chama-se o destrutor da classe, sinalizando a finalização do escalonamento
        ~FCFS_Scheduler();
    }

    // A idéia aqui é criar um loop de utilização do processo, quando ele efetivamente está em uso
    // incrementando o Turnarround time do processo
    // for(int time = 0; time < pointer->gettime(); time++){// }
};

FCFS_Scheduler::~FCFS_Scheduler(){
    delete process;
}