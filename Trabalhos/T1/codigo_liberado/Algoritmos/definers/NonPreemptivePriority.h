#ifndef NONPPRIORITY_SCHEDULER_H
#define NONPPRIORITY_SCHEDULER_H

#include <vector>
#include <algorithm>
#include "Process.h"

class NonPriorityScheduler: public Process{
    public:
        NonPriorityScheduler();
        ~NonPriorityScheduler();

        void escalonate(std::vector<Process*> processVector, int flag);
        void exec(Process *process, int flag); // metodo de execucao do escalonador, flag de execucao
        void tick(){timer_++;}; // tick do relogio do processador, sinalizando que ocorreu uma execucao
        int calculatedynamicpriority(int TempoExecTotal, int tempodequantum);

    private:
        int timer_; // timer do escalonador

        Process* getHighestPriorityProcess(std::list<Process*>& readyQueue) {
            if (readyQueue.empty()) {
                return nullptr; // Retorna nullptr se a fila estiver vazia
            }

            // Inicialize o processo com o primeiro da fila
            Process* highestPriorityProcess = readyQueue.front();

            // Percorre a fila para encontrar o processo com prioridade mais alta
            for (Process* process : readyQueue) {
                if (process->getpriority() > highestPriorityProcess->getpriority()) {
                    highestPriorityProcess = process;
                }
            }

            return highestPriorityProcess;
        }

        void updatePriorityQueue(std::list<Process*>& priorityQueue, Process* process) {
            // Encontre a posição atual do processo na fila
            auto currentPos = std::find(priorityQueue.begin(), priorityQueue.end(), process);

            if (currentPos != priorityQueue.end()) {
                // Remova o processo da posição atual
                priorityQueue.erase(currentPos);

                // Encontre a posição correta com base na nova prioridade
                auto newPos = std::find_if(priorityQueue.begin(), priorityQueue.end(),
                    [process](Process* p) {
                        return process->getpriority() > p->getpriority();
                    }
                );

                // Insira o processo na nova posição
                priorityQueue.insert(newPos, process);
            }
        }

        void removeProcessFromQueue(std::list<Process*>& Ready_queue, int targetDuration) {
            auto it = Ready_queue.begin();

            while (it != Ready_queue.end()) {
                if ((*it)->getduration() == targetDuration) {
                    it = Ready_queue.erase(it); // Remove o processo da fila e atualiza o iterador
                } else {
                    ++it; // Avança para o próximo elemento
                };
            };
        };
};

#endif
