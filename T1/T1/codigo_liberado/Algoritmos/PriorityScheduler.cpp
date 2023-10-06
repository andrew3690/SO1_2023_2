#include "../definers/PriorityScheduler.h"


PriorityScheduler::PriorityScheduler() {
    std::cout << "Inicializando o Escalonador de prioridades \n";
};

PriorityScheduler::~PriorityScheduler() {
    std::cout << "Finalizando o escalonador \n";
}; //destrutor

void PriorityScheduler::exec(Process *process, int time){
    std::cout << "Processo {" << process->getid() << "} executou no tempo: " << time << "\n";
    process->dectime(); // decrementa a duração restante
};


void PriorityScheduler::escalonate(std::vector<Process*> processVector, int flag) {
    while (Process::Blocked_queue.size() > 0 || Process::Ready_queue.size() > 0 || running_process != nullptr) {
        sleep(1);

        for (int i = 0; i < Process::Blocked_queue.size(); i++) {
            Process* blocked_process = Process::Blocked_queue.front();
            if (blocked_process->gettime() == clock_counter) {
                blocked_process->makeready(blocked_process->getid(), clock_counter); // coloca processo na lista de pronto
            }
        }
        Process::Ready_queue = sortbypriority(Process::Ready_queue); // ordena
        Process* process;

        if (flag == 1 || flag == 0 ) {
            // execução SEM preempção
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
                process->endprocess(clock_counter);
                running_process = nullptr;
            }
        } //else {
            // execução COM PREEMPÇÃO - QUANTUM = 2
        //     if (running_process == nullptr) {
        //         process = Process::Ready_queue.front();
        //         process->start();
        //         running_process = process;
        //     }

        //     if (process->getduration() > 0 && process->getquantum() < quantum) {
        //         exec(process, clock_counter); // executa o processo por 1 unidade de tempo
        //         process->increasequantum(); // incrementa o quantum do processo
        //     }

        //     if (process->getduration() == 0) {
        //         // processo atual terminou suas instruções
        //         process->stop();
        //         process->endprocess();
        //         running_process = nullptr;
        //     } else if (process->getquantum() == quantum) {
        //         // processo ja executou por 2 segundos e deve ser preemptado
        //         process->resetquantum();
        //         Process* next_process = Process::Ready_queue.front();
        //         running_process = next_process;
        //         process->preempt(); // volta para a lista de prontos
        //     }
        // }
        clock_counter++;
    }
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
