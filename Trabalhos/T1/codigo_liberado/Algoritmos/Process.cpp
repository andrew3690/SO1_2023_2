#include "definers/Process.h"

int Process::id_increment = 0;
std::list<Process*> Process::Ready_queue;
std::list<Process*> Process::Blocked_queue;
const std::list<Process*>* processList; // Change to pointer

// construtor da classe de processo
Process::Process(int id,int data, int time, int priority){
    // incrementa o id do processo
    _id = id_increment++;

    // cria um o contexto do processo
    ctxtpointer = new CPU::Context();
    
    // cria o ponteiro do processo
    pointer = new Process(id,data, time, priority);

    // obtém o tempo de criação do processo
    pointer->data_init = pointer->gettime();
    
    // Seta o estado do contexto e insere na fila de processos prontos
    pointer->state = Ready;

    // Prints de debug
    std::cout << "Processo Criado\n";
    std::cout << "id: " << pointer->getid() << "time: " << pointer->gettime() << "prioridade: "<< pointer->getpriority() <<" \n";
    
    // Salva o contexto e insere o processo na fila de prontos,
    ctxtpointer->save();

    // insere o processo no fim da fila de prontos 
    Ready_queue.push_back(pointer);
    
    // incrementa o tempo de permaencia do processo na lista de processos prontos
    pointer->setTurnarroundTimer();
}

// destrutor do processo
Process::~Process(){
    // deleta o pointeiro do contexto, bem com o ponteiro do processo, decrementa o contador de id's
    delete ctxtpointer;
    delete pointer;
    // se a fila de processos estiver vazia, deletar ela também
}

// a idéia é ter um método que retira o processo da fila de bloqueados e o insere na fila de prontos
int Process::makeready(int id){
    
    // Retira o processo da fila de processos bloqueados (Consertar isso, retirar o processo da fila de prontos definitivamente)
    // pointer = FindProcessById(Blocked_queue,id);
    for(Process* process: Blocked_queue){
        if(process->getid() == id){
            pointer = process;
        };
    };

    // troca o estado do processo para pronto
    pointer->state = Ready;
    // insere o processo no fim da fila de processos
    Ready_queue.push_back(pointer);

    // incrementa o tempo de permanecia do processo na lista de processos prontos
    pointer->setreadlistavgcounter();
    
    return 0;
}

// Método para parar o processo especificado pelo id
void Process::stop(){
    // verifica se o process o está rodando
    if(this->state == Running){
        // Troca o estado do processo para bloqueado
        this->state = Blocked; 
        // salva o contexto do processo
        pointer->ctxtpointer->save();
        // a idéia é trocar o contexto atual para o contexto da cpu
        // É necessário fazer uma idéia de como decidir se o escalonador ou o processo está esperando uma entrada
            // se o escalonador selecionar outro processo, insere o processo na fila de prontos
            // se o processo está esperando input, insere o processo na fila de bloqueados
        CPU::switch_context(pointer->ctxtpointer, cpu);
        // incrementa contador de trocas de contexto do processo
        pointer->setswitchcontextcounter();
    }
}

// inicaliza o processo
void Process::start(){
    // carrega o contexto

    this->ctxtpointer->load();
    
    // Retira da fila de prontos (Consertar isso, retirar o processo da fila de prontos definitivamente)
    for(Process* process: Ready_queue){
        if(process->getid() == this->getid()){
            running = process;
        };
    };

    // realiza a troca do contexto da cpu para o contexto atual
    CPU::switch_context(cpu,ctxtpointer);

    // incrementa a contagem de troca de processos
    running->setswitchcontextcounter();

    // troca o estado do processo para rodando
    running->state = Running;

    // realiza a execução do processo
    running->exec();
}

void Process::exec(){
    // enquanto houver tempo para execução do processo e este estiver no estado Running....
    while(this->state == Running && this->gettime() != 0){
        // primeiro: é necessário decerementar o tempo de execução do processo
        if(this->timeexec-- == 0){
            this->stop();
        }else{};
    };
}

void Process::endprocess(){
    // Printa os dados requisitados
    std::cout << "Turnarround Time: " << this->getTurnarroundTime() << " Tempo médio  de espera: "<< this->getreadlistavgcounter() <<" Total de trocas de contexto: " << this->getswitchcontextcounter() <<" \n";
    // Chama o destrutor do Processo
    this->~Process();
}

// // método genérico para obter um processo das listas de prontos e lista de bloqueados
// Process* FindProcessById(const std::list<Process*>& processList, int id) {
//     for(Process* process: processList){
//         if(process->getid() == id){
//             return process;
//         };
//     }
//     return nullptr;
// }