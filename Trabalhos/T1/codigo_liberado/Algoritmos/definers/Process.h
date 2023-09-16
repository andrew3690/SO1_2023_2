#ifndef PROCESS_H
#define PROCESS_H

#include "CPU.h"
#include <iostream>
#include <vector>
using namespace std;

class Process: public CPU::Context{
    
    public:
        Process(){}; // Construtor vazio
        Process(int data, int time, int priority); // Construtor com parametros
        ~Process(); 
        
        // metodos do processo
        void stop();  // interrrupcao do processo
        void start(); // incia ou volta a execucao do processo
        int makeready(int id); // faz o processo sair da fila de bloqueados para a fila de prontos
        void preempt(); // faz o processo em execução retornar para a fila de pronto
        //void exec(); // método para execução do processo
        
        // Printa o diagrama de execução dos processos
        // void printdiagram();
        
        // Finaliza o processo:
        void endprocess();

        // setters das variáveis do trabalho
        int setTurnarroundTimer(){return tunarround_time++;};
        int setswitchcontextcounter(){return switch_context_count++;};
        int setreadlistavgcounter(){return read_list_avg_time++;};
        void increasequantum() {current_quantum++;};
        void resetquantum() {current_quantum = 0;};

        // getters das variaveis do trabalho 
        int getTurnarroundTime(){return tunarround_time;};
        int getswitchcontextcounter(){return switch_context_count;};
        int getreadlistavgcounter(){return read_list_avg_time;};

        // setters de tempo e prioridade
        void settime(int time){duration = time;};
        void setdata(int data){data_init = data;};
        void sepriority(int priority){priority_ = priority;};

        // metodo para decrementar o tempo de existencia do processo
        void dectime(){duration--;};

        // getters de tempo e prioridade
        int getduration(){return duration;};
        int gettime(){return data_init;};
        int getpriority(){return priority_;};
        int getid() {return _id;};
        int getquantum() {return current_quantum;};

        // Filas de processo prontos e pocessos bloqueados
        static std::vector<Process*> Ready_queue;   // Fila de processos prontos
        static std::vector<Process*> Blocked_queue; // Fila de processo bloqueados
        
        CPU *cpu; // ponteiro para a cpu
        Context *ctxtpointer; // ponteiro de contexto do processo
        Process *running; // ponteiro para o processo que está com a cpu no momento

        enum State // Estado atual
        {
            Ready,
            Blocked,
            Running
        } state;
        
    private:

        // Atributos do Processo
        static int id_counter; // Static member variable to keep track of IDs
        int _id;    // ID of the process
        int data_init; // data de inicio
        int data_end; // data de fim
        int duration; // duracao, variável que faz uma estimativa do tempo de exeução do processo 
        int timeexec; // tempo de execucao, variável que acompanha a exeucção do processo
        int priority_; // prioridade do processo
        int current_quantum = 0;


        // Variáveis do trabalho
        int tunarround_time = 0;
        int read_list_avg_time = 0;
        int switch_context_count = 0;
};
#endif