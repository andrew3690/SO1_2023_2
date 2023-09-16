#include "../definers/NonPreemptivePriority.h"



NonPriorityScheduler::NonPriorityScheduler() {
    std::cout << "Inicializando o Escalonador de prioridades \n";
    tick();
};
NonPriorityScheduler::~NonPriorityScheduler() {
    std::cout << "Finalizando o escalonador \n";
}; //destrutor

// calculo de prioridades baseada no Livro do Tanembaum sobre prioridades dinamicas pg.111
int NonPriorityScheduler::calculatedynamicpriority(int TempoExecTotal, int tempodequantum ){
    // Calcula a fracao de processamento do ultimo processo
    double fraction = (double) TempoExecTotal / tempodequantum;

    int dynamicPriority = (int) (1.0/fraction);

    return dynamicPriority;
};

void NonPriorityScheduler::exec(Process *process, int flag){
    if(flag == 1){
         while(process->state == Running & process->getduration() > 0){
            // primeiro decrementa o tempo de existencia do processo....
            // std::cout <<"Duracao atual do processo: " << this->getduration() <<"\n";
            process->dectime();
            
            // segundo: é necessário decrementar o tempo de existencia do processo
            process->setTurnarroundTimer();
            // std::cout <<"Duracao atual do processo: " << this->getduration() <<"\n";
            // se o tempo de duracao do processo tiver acabado...

            if(process->getduration() == 0){
                // ... chama o destrutor do processo
                process->stop();
                process->endprocess();
            }
        }
    }
    else
    {
        // // enquanto houver tempo para execução do processo e este estiver no estado Running....
        // while(process->state == Running & process->getduration() > 0){
        //     // se a nova prioridade do processo for menor que 2....  
        //     if(calculatedynamicpriority(process->getduration(),process->gettime()) < 2){
        //         // ....realiza a parada do processo
        //         process->stop();
        //         process->endprocess();
        //     }
        // }
        // Modo de execução com preempção
        std::cout << "Modo de execução com preempção\n";

        while (!Ready_queue.empty()) {
            Process* nextProcess = getHighestPriorityProcess(Ready_queue);

            while (nextProcess->getduration() > 0) {
                int initialPriority = nextProcess->getpriority();
                int TempoExecTotal = nextProcess->getduration(); // Calcula o tempo total de execução do processo
                int tempodequantum = 2; // Define o tamanho do quantum

                // Calcula a prioridade dinâmica
                int dynamicPriority = calculatedynamicpriority(TempoExecTotal, tempodequantum);
                nextProcess->sepriority(dynamicPriority);

                // Se a prioridade diminuiu, atualize a fila de prontos
                if (nextProcess->getpriority() < initialPriority) {
                    updatePriorityQueue(Process::Ready_queue, nextProcess);
                }

                // Verifique se um novo processo com prioridade mais alta chegou
                Process* newHighPriorityProcess = getHighestPriorityProcess(Ready_queue);
                if (newHighPriorityProcess->getpriority() > nextProcess->getpriority()) {
                    // Preemptar o processo atual
                    nextProcess->stop();
                    break;
                }

                nextProcess->dectime();
            }

            // Remove o processo da fila de prontos quando ele terminar
            // removeProcessFromQueue(Ready_queue, nextProcess);
            if(nextProcess->getduration() == 0){
                nextProcess->stop();
                nextProcess->endprocess();
            }
        }
    }
}


void NonPriorityScheduler::escalonate(std::vector<Process*> processVector, int flag) {    
    // percorre a lista de prioridades e organiza pelos processos de maior e menor prioridade de forma decrescente
    for(auto &process: processVector){
        std::cout << "Id: " << process->getid() <<" Prioridade :" << process->getpriority() << " \n";
        process->sortbypriority();

        // std::cout << "Lista de Bloqueados ordenada pela prioridade \n";
        makeready(process->getid());

        // verifica o modo de execucao do escalonador
        if(flag == 1){
            std::cout << "Modo de execucao do escalonador sem preempcao \n";
                // tira o processo das listas de prontos
                process->setTurnarroundTimer();        
                process->start();
                // inicia a execucao do processo no modo 1....
                exec(process,1);
        } else{
            std::cout << "Modo de execucao do escalonador com preempcao";
                // a ideia eh inciair a execucao aqui....
                process->start();

                // execucao eh inciada
                exec(process,2);

                // Apos a execucao, verifica se ha processos na fila de bloqueados
                if(!Process::Blocked_queue.empty()){
                    // tirar o processo que esta no topo da fila de bloqueados, e os insere na fila de prontos
                    process->makeready(Process::Blocked_queue.front()->getid());
                }else{
                    std::cout << "Fila de bloqueados vazia !\n";
                };
        };
        // Incrementa o timer do relogio
        tick();
    };
};