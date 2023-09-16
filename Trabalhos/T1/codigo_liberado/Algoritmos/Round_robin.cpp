#include "definers/Round_robin.h"

Round_robin::Round_robin(){
    std::cout << "Chamada do escalonador Round-Robin \n";
}

Round_robin::~Round_robin(){}

void Round_robin::escalonate(){
    std::cout << "Iniciando o escalonamento \n";
    while (Process::Blocked_queue.size() > 0 || Process::Ready_queue.size() > 0 || running_process != nullptr) {
        sleep(1);

        for (int i = 0; i < Process::Blocked_queue.size(); i++) {
            Process* blocked_process = Process::Blocked_queue.front();
            if (blocked_process->gettime() == clock_counter) {
                blocked_process->makeready(blocked_process->getid()); // coloca processo na lista de pronto
            }
        }
        //Process::Ready_queue = sort(Process::Ready_queue); // ordena
        Process* process;

        if (running_process == nullptr) {
            process = Process::Ready_queue.front();
            process->start();
            running_process = process;
        }

        if (process->getduration() > 0 and process->getquantum() < quantum) {
            exec(process, clock_counter);
            process->increasequantum();
        }

        if (process->getduration() == 0) {
            process->stop();
            process->endprocess();
            running_process = nullptr;
        } else if (process->getquantum() == 2) {
            process->stop(); // deveria voltar para lista de prontos
        }
        clock_counter++;
    }
}

// void Round_robin::sort(){

// }

// void Round_robin::schedule(){

// }