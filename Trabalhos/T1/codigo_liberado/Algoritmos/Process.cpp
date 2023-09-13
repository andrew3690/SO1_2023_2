#include "definers/Process.h"

std::list<Process*> Process::Ready_queue;
std::list<Process*> Process::Blocked_queue;

// construtor da classe de processo
Process::Process(int id,int data, int time, int priority){
    
    // obtém o tempo de criação do processo
    this->settime(time);
    this->setdata(data);
    this->sepriority(priority);

    std::cout << "Tempo de criacao do processo: "<< this->gettime() << "\n";
    
    // Seta o estado do contexto e insere na fila de processos prontos
    this->state = Ready;

    // Prints de debug
    std::cout << "Processo Criado\n";
    std::cout << "id: " << this->getid() << " time: " << this->gettime() << "prioridade: "<< this->getpriority() <<" \n";
    
    // Salva o contexto e insere o processo na fila de prontos, insere o processo no fim da fila de prontos 
    Ready_queue.push_back(this);
    
    // incrementa o tempo de permaencia do processo na lista de processos prontos
    this->setreadlistavgcounter();
    this->setTurnarroundTimer();
}

// destrutor do processo
Process::~Process(){
    // deleta o pointeiro do contexto, bem com o ponteiro do processo, decrementa o contador de id's 
     if (ctxtpointer != nullptr) {
        delete ctxtpointer;
    }
    // se a fila de processos estiver vazia, deletar ela também
}

// a idéia é ter um método que retira o processo da fila de bloqueados e o insere na fila de prontos
int Process::makeready(int id){
    // Procurar o processo com o ID especificado na lista de Blocked
    for (auto it = Blocked_queue.begin(); it != Blocked_queue.end(); ++it) {
        if ((*it)->getid() == id) {
            Process* processToMove = *it;
            
            // Remove o processo da fila Blocked
            Blocked_queue.erase(it);
            
            // Define o estado como Ready
            processToMove->state = Ready;
            
            // Adiciona à fila Ready
            Ready_queue.push_back(processToMove);
            
            // Incrementa os contadores
            processToMove->setreadlistavgcounter();
            processToMove->setTurnarroundTimer();
            
            // Indica sucesso
            return 0;
        }
    }
    return -1; // Indica que o processo não foi encontrado
}

// Método para parar o processo especificado pelo id
void Process::stop(){
    // verifica se o process o está rodando
    if(this->state == Running){
        // Troca o estado do processo para bloqueado
        this->state = Blocked;
        
        // realiza troca de contexto aqui para a cpu
        cpu->switch_context(this->pointer,cpu->pointer);

        // incrementa contador de trocas de contexto do processo
        this->setswitchcontextcounter();
        this->setTurnarroundTimer();
    }
}

// inicaliza o processo
void Process::start(){
    // Retira da fila de prontos
    for (auto it = Ready_queue.begin(); it != Ready_queue.end(); ++it) {
        if ((*it)->getid() == this->getid()) {
            running = *it;
            Ready_queue.erase(it);
            break;
        }
    }

    // realiza a troca do contexto da cpu para o contexto atual
    cpu->switch_context(cpu->pointer,running->pointer);

    // incrementa a contagem de troca de processos
    running->setswitchcontextcounter();

    // troca o estado do processo para rodando
    running->state = Running;

    // incrementa o tempo de existencia do processo
    running->setTurnarroundTimer();

    // realiza a execução do processo
    running->exec();
}

void Process::exec(){
    // enquanto houver tempo para execução do processo e este estiver no estado Running....
    while(this->state == Running && this->getduration() != 0){
        // primeiro decrementa o tempo de existencia do processo....
        this->dectime();
        
        // se o tempo de duracao do processo tiver acabado...
        if(this->getduration() == 0){
            // ... chama o destrutor do processo
            this->endprocess();
        }

        // segundo: é necessário decrementar o tempo de existencia do processo
        this->setTurnarroundTimer();
    };
}

void Process::endprocess(){
    // Printa os dados requisitados
    std::cout << "Turnarround Time: " << this->getTurnarroundTime() << " Tempo médio  de espera: "<< this->getreadlistavgcounter() <<" Total de trocas de contexto: " << this->getswitchcontextcounter() <<" \n";
    // Chama o destrutor do Processo
    this->~Process();
}