#include "../definers/NonPreemptivePriority.h"


NonPPriorityScheduler::NonPPriorityScheduler() {

}; //construtor
NonPPriorityScheduler::~NonPPriorityScheduler() {}; //destrutor

void NonPPriorityScheduler::escalonate() {
    
};

void NonPPriorityScheduler::sort()
{
    // ordenar em ordem decrescente de prioridade (prioridade maior -> inicio do vetor)
    int size = process_list.size();
    for (int i = 1; i < size; i++) {
        Process key = process_list[i];
        int j = i-1;

        while (key.getpriority() > process_list[j].getpriority() && j >= 0) {
            process_list[j + 1] = process_list[j];
            j--;
        }
        process_list[j+1] = key;
    }
}
