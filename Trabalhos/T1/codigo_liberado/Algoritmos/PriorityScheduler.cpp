#include "../definers/PriorityScheduler.h"


PriorityScheduler::PriorityScheduler() {
    std::cout << "Inicializando o Escalonador de prioridades \n";
    tick();
};
PriorityScheduler::~PriorityScheduler() {
    std::cout << "Finalizando o escalonador \n";
}; //destrutor

// calculo de prioridades baseada no Livro do Tanembaum sobre prioridades dinamicas pg.111
int PriorityScheduler::calculatedynamicpriority(int TempoExecTotal, int tempodequantum ){
    // Calcula a fracao de processamento do ultimo processo
    double fraction = (double) TempoExecTotal / tempodequantum;

    int dynamicPriority = (int) (1.0/fraction);

    return dynamicPriority;
};

void PriorityScheduler::exec(Process *process, int time){
    std::cout << "executou no tempo: " << time << "\n";
    process->dectime(); // decrementa a duração restante
};


void PriorityScheduler::escalonate(std::vector<Process*> processVector, int flag) {
    while (Process::Blocked_queue.size() > 0 || Process::Ready_queue.size() > 0 || running_process != nullptr) {
        sleep(1);

        for (int i = 0; i < Process::Blocked_queue.size(); i++) {
            Process* blocked_process = Process::Blocked_queue.front();
            if (blocked_process->gettime() == clock_counter) {
                blocked_process->makeready(blocked_process->getid()); // coloca processo na lista de pronto
            }
        }
        Process::Ready_queue = sortbypriority(Process::Ready_queue); // ordena
        Process* process;

        if (flag == 1) {
            // execução SEM preempção
            std::cout << "Modo de execucao do escalonador sem preempcao \n";
            if (running_process == nullptr) {
                process = Process::Ready_queue.front();
                process->start();
                running_process = process;
            }

            if (process->getduration() > 0) {
                exec(process, clock_counter);
            }

            if (process->getduration() == 0) {
                process->stop();
                process->endprocess();
                running_process = nullptr;
            }
        }
        clock_counter++;
    }
    // percorre a lista de prioridades e organiza pelos processos de maior e menor prioridade de forma decrescente
    // for(auto &process: processVector){
    //     std::cout << "Id: " << process->getid() <<" Prioridade :" << process->getpriority() << " \n";
    //     process->sortbypriority();

    //     // std::cout << "Lista de Bloqueados ordenada pela prioridade \n";
    //     makeready(process->getid());

    //     // verifica o modo de execucao do escalonador
    //     if(flag == 1){
    //         std::cout << "Modo de execucao do escalonador sem preempcao \n";
    //             // tira o processo das listas de prontos
    //             process->setTurnarroundTimer();        
    //             process->start();
    //             // inicia a execucao do processo no modo 1....
    //             exec(process,1);
    //     } else{
    //         std::cout << "Modo de execucao do escalonador com preempcao";
    //             // a ideia eh inciair a execucao aqui....
    //             process->start();

    //             // execucao eh inciada
    //             exec(process,2);

    //             // Apos a execucao, verifica se ha processos na fila de bloqueados
    //             if(!Process::Blocked_queue.empty()){
    //                 // tirar o processo que esta no topo da fila de bloqueados, e os insere na fila de prontos
    //                 process->makeready(Process::Blocked_queue.front()->getid());
    //             }else{
    //                 std::cout << "Fila de bloqueados vazia !\n";
    //             };
    //     };
    //     // Incrementa o timer do relogio
    //     tick();
    // };
};

std::vector<Process*> PriorityScheduler::sortbypriority(std::vector<Process*> process_list)
{
    // ordena em prioridades decrescentes (maior prioridade primeiro)
    int size = process_list.size();
    for (int step = 1; step < size; step++) {
        Process* key = process_list[step];
        int j = step - 1;

        while (j >= 0 && key->getpriority() > process_list.at(j)->getpriority()) {
            process_list[j + 1] = process_list[j];
            --j;
        };
        process_list[j + 1] = key;
    }
    return process_list;
}
