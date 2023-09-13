#ifndef PROCESS_H
#define PROCESS_H

#include "CPU.h"
#include <iostream>
using namespace std;

class Process: public CPU::Context{
    
    public:
        Process(){}; // Construtor vazio
        Process(int id, int data, int time, int priority); // Construtor com parametros
        ~Process(); 
        
        void stop();  // interrrupcao do processo
        void start(); // incia ou volta a execucao do processo
        int makeready(int id); // faz o processo sair da fila de bloqueados para a fila de prontos
        void exec(); // método para execução do processo
        
        // Printa o diagrama de execução dos processos
        void printdiagram();
        // Finaliza o processo:
        void endprocess();

        //setter das variáveis do trabalho
        int setTurnarroundTimer(){return tunarround_time++;};
        int setswitchcontextcounter(){return switch_context_count++;};
        int setreadlistavgcounter(){return read_list_avg_time++;};

        int getTurnarroundTime(){return tunarround_time;};
        int getswitchcontextcounter(){return switch_context_count;};
        int getreadlistavgcounter(){return read_list_avg_time;};

        // setters de tempo e prioridade
        void settime(int time){duration = time;};
        void setdata(int data){data_init = data;};
        void sepriority(int priority){priority_ = priority;};

        // getters de tempo e prioridade
        int gettime(){return data_init;};
        int getpriority(){return priority_;};
        int getid() {return _id;};

        // Filas de processo prontos e pocessos bloqueados
        static std::list<Process*> Ready_queue;   // Fila de processos prontos
        static std::list<Process*> Blocked_queue; // Fila de processo bloqueados
        
        CPU *cpu; // ponteiro para a cpu
        Context *ctxtpointer; // ponteiro de contexto do processo
        Process *pointer; // ponteiro para o processo
        Process *running; // ponteiro para o processo que está com a cpu no momento
        
    private:

        // Atributos do Processo
        int _id; // identificador do processo
        int data_init; // data de inicio
        int data_end; // data de fim
        int duration; // duracao, variável que faz uma estimativa do tempo de exeução do processo 
        int timeexec; // tempo de execucao, variável que acompanha a exeucção do processo
        int priority_; // prioridade do processo

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
};
#endif