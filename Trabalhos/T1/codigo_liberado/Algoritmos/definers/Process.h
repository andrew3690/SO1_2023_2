#ifndef PROCESS_H
#define PROCESS_H
#include "CPU.h"

class Process: public CPU{
    public:
        Process(int data, int time, int priority);
        ~Process(); 
        
        void stop();  // interrrupcao do processo
        void start(); // incia ou volta a execucao do processo 

    int id; // identificador

    private:
        CPU::Context *ctxtpointer; // ponteiro de contexto do processo
        int data_init; // data de inicio
        int data_end; // data de fim
        int duration; // duracao
        int timeexec; // tempo de execucao
        int priority; // prioridade do processo 
        enum State // Estado atual
        {
            Ready,
            Blocked,
            Running
        } state;

};


#endif