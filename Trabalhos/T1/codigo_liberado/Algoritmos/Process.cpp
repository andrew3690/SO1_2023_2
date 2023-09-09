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
    
    // Seta o estado do contexto e insere na fila de processos prontos
    this->state = Ready;

    std::cout << "Processo Criado\n";
    std::cout << "id: " << this->getid() << "time: " << this->gettime() << "prioridade: "<< this->getpriority() <<" \n";
    // Salva o contexto e insere o processo na fila de prontos,
    ctxtpointer->save();
    Ready_queue.push_back(pointer);
    // incrementa o tempo de permaencia do processo na lista de processos prontos
    this->read_list_avg_time++;
}

// destrutor do processo
Process::~Process(){
    // deleta o pointeiro do contexto, bem com o ponteiro do processo, decrementa o contador de id's
    delete ctxtpointer;
    delete pointer;
    // se a fila de processos estiver vazia, deletar ela também
}

// método genérico para obter um processo das listas de prontos e lista de bloqueados
Process* FindProcessById(const std::list<Process*>& processList, int id) {
    for(Process* process: processList){
        if(process->getid() == id){
            return process;
        };
    }
    return nullptr;
}

// a idéia é ter um método que retira o processo da fila de bloqueados e o insere na fila de prontos
int Process::makeready(int id){
    // Retira o processo da fila de processos bloqueados (Consertar isso, retirar o processo da fila de prontos definitivamente)
    pointer = FindProcessById(Blocked_queue,id);
    // troca o estado do processo para pronto
    pointer->state = Ready;
    // insere o processo no fim da fila de processos
    Ready_queue.push_back(pointer);
    // incrementa o tempo de permanecia do processo na lista de processos prontos
    this->read_list_avg_time++;
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
        CPU::switch_context(ctxtpointer, cpu);
    }
}

// inicaliza o processo
void Process::start(){
    // carrega o contexto 
    this->ctxtpointer->load();
    // Retira da fila de prontos (Consertar isso, retirar o processo da fila de prontos definitivamente)
    running = FindProcessById(Ready_queue,this->getid());
    // realiza a troca do contexto da cpu para o contexto atual
    CPU::switch_context(cpu,ctxtpointer);
    // realiza a execução do processo
    this->exec();
}

void Process::exec(){
    // enquanto houver tempo para execução do processo e este estiver no estado Running....
    while(this->state == Running && this->gettime() != 0){
        // primeiro: é necessário decerementar o tempo de execução do processo
        this->timeexec--;
        for(int i = 0; i < Ready_queue.size();i++){
            std::cout <<"tempo" << "P" <<i;
            for(int y = 0; y <this->gettime();y++){
                std::cout <<y <<"-"<<y+1<<"\n";
            };
        };
    };
}