#ifndef PROCESS_H
#define PROCESS_H

class Process{
    public:
        Process(int data, int time, int priority);
        ~Process();
        
        void stop();
        void load();

    private:
        int id; // identificador
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
        };

};


#endif