#ifndef PROCESS_H
#define PROCESS_H

#include "CPU.h"
#include <iostream>
using namespace std;

class Process: public CPU{
    
    public:
        Process(int id, int data, int time, int priority);
        ~Process(); 
        
        void stop();  // interrrupcao do processo
        void start(); // incia ou volta a execucao do processo
        int makeready(int id); // faz o processo sair da fila de bloqueados para a fila de prontos, DEPENDE DO ESCANLONADOR UTILIZADO
        void exec(); // método para execução do processo
        void escalonate(); // método que os algoritmos de escalonamento chamam para escalonar processos

        // getters de tempo e prioridade
        int gettime(){return data_init;};
        int getpriority(){return priority;};
        int getid() {return _id;};
        // Process* FindProcessById(const std::list<Process*>& processList, int id);

    private:

        CPU::Context *ctxtpointer; // ponteiro de contexto do processo
        Process *pointer; // ponteiro para o processo
        Process *running; // ponteiro para o processo que está com a cpu no momento

        static int id_increment; // incrementador do processo 
        int _id; // identificador do processo

        // Time diference
        int data_init; // data de inicio
        int data_end; // data de fim
        int duration; // duracao, variável que faz uma estimativa do tempo de exeução do processo 
        int timeexec; // tempo de execucao, variável que acompanha a exeucção do processo
        
        // Priority var
        int priority; // prioridade do processo

        enum State // Estado atual
        {
            Ready,
            Blocked,
            Running
        } state;

        // Variáveis do trabalho
        int tunarround_time = 0;
        int read_list_avg_time = 0;
        int switch_context_count = 0;
        
        // Filas de processo prontos e pocessos bloqueados
        static std::list<Process*> Ready_queue;   // Fila de processos prontos
        static std::list<Process*> Blocked_queue; // Fila de processo bloqueados

};


#endif