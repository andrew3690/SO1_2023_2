#include "definers/Round_robin.h"

Round_robin::Round_robin(){
    std::cout << "Chamada do escalonador Round-Robin \n";
}

Round_robin::~Round_robin(){}

void Round_robin::escalonate(){
    std::cout << "Iniciando o escalonamento \n";
    while (Process::Blocked_queue.size() > 0 || Process::Ready_queue.size() > 0 || running_process != nullptr) {
        sleep(1); // unidade de tempo (1 segundo)

        for (int i = 0; i < Process::Blocked_queue.size(); i++) {
            Process* blocked_process = Process::Blocked_queue.front();
            if (blocked_process->gettime() == clock_counter) {
                blocked_process->makeready(blocked_process->getid()); // coloca processo na lista de pronto
            }
        }
        Process* process;

        if (running_process == nullptr) {
            process = Process::Ready_queue.front();
            process->start();
            running_process = process;
        }

        if (process->getduration() > 0 and process->getquantum() < quantum) {
            exec(process, clock_counter); // executa o processo por 1 unidade de tempo
            process->increasequantum(); // incrementa o quantum do processo
        }

        if (process->getduration() == 0) {
            // processo atual terminou suas instruções
            process->stop();
            process->endprocess();
            running_process = nullptr;
        } else if (process->getquantum() == quantum) {
            // processo ja executou por 2 segundos e deve ser preemptado
            process->preempt(); // volta para o final da lista de prontos
            process->resetquantum();
            running_process = nullptr;
        }
        clock_counter++; // incrementa o relógio
    }
}