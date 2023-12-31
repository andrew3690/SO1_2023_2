#include "definers/Process.h"
#include "unistd.h"

std::vector<Process*> Process::Ready_queue;
std::vector<Process*> Process::Blocked_queue;
int Process::id_counter = 0;

// construtor da classe de processo
Process::Process(int data, int time, int priority){
    // incrementa o id do contador de processos
    _id = ++id_counter;
    // obtém o tempo de criação do processo
    this->settime(time);
    this->setdata(data);
    this->sepriority(priority);

    // std::cout << "Tempo de criacao do processo: "<< this->gettime() << "\n";
    
    // Seta o estado do contexto e insere na fila de processos prontos
    this->state = Ready;

    // Prints de debug
    // std::cout << "Processo Criado\n";
    std::cout << "id: " << this->getid() << " time: " << this->gettime() << " prioridade: "<< this->getpriority() <<" \n";
    
    // Salva o contexto e insere o processo na fila de prontos, insere o processo no fim da fila de prontos 
    Blocked_queue.push_back(this);
    
    // incrementa o tempo de permaencia do processo na lista de processos prontos
    //this->setTurnarroundTimer();
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
int Process::makeready(int id, int time){
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
            processToMove->setTurnarroundTimer(time);
            
            // Indica sucesso
            return 0;
        }
    }
    return -1; // Indica que o processo não foi encontrado
}

void Process::preempt()
{
    Ready_queue.push_back(this);
    this->state = Ready;
}

// Método para parar o processo especificado pelo id
void Process::stop(){
    // verifica se o process o está rodando
    if(this->state == Running){
        // Troca o estado do processo para bloqueado
        this->state = Blocked;

        // realiza troca de contexto aqui para a cpu
        // cpu->switch_context(this->pointer,cpu->pointer);

        // incrementa contador de trocas de contexto do processo
        this->setswitchcontextcounter();
        //this->setTurnarroundTimer();
    }
}

// inicaliza o processo
void Process::start(){
    // Retira da fila de prontos
    std::cout << "Vou retirar da fila de prontos" << "\n";
    for (auto it = Ready_queue.begin(); it != Ready_queue.end(); ++it) {
        if ((*it)->getid() == this->getid()) {
            running = *it;
            Ready_queue.erase(it);
            break;
        }
    }
    std::cout << "Retirei o processo da lista de prontos " << running->getid() << "\n";

    // realiza a troca do contexto da cpu para o contexto atual
    // cpu->switch_context(cpu->pointer,running->pointer);

    std::cout << "Troca de contexto realizada pelo processo " << running->getid() << "\n";

    // incrementa a contagem de troca de processos
    running->setswitchcontextcounter();

    // troca o estado do processo para rodando
    running->state = Running;

    // incrementa o tempo de existencia do processo
   // running->setTurnarroundTimer(time);

}

void Process::endprocess(int time){
    // Printa os dados requisitados
    int temp = time - this->getTurnarroundTime();
    this->setTurnarroundTimer(temp);
    std::cout << "Turnarround Time: " << this->getTurnarroundTime() << " Tempo médio  de espera: "<< this->getreadlistavgcounter() <<" Total de trocas de contexto: " << this->getswitchcontextcounter() <<" \n";
    // Chama o destrutor do Processo
    delete this;
}