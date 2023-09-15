#include "definers/SJF.h"
#include "unistd.h"


SJF_Scheduler::SJF_Scheduler(){
    std::cout << "Inciando o escalonador SJF";
} //constructor

SJF_Scheduler::~SJF_Scheduler(){} //destructor


void SJF_Scheduler::escalonate(std::vector<Process*> processVector)
{
    process_list = processVector;
    sort();
    for (auto& process: process_list) {
        process->start();
        //std::cout << "executou no instante " << counter << "-" << counter+1 << " " << process->getid() << std::endl;
    }
}

void SJF_Scheduler::sort()
{
    int size = process_list.size();
    for (int step = 1; step < size; step++) {
        Process* key = process_list[step];
        int j = step - 1;

        while (j >= 0 && key->getduration() < process_list.at(j)->getduration()) {
            process_list[j + 1] = process_list[j];
            --j;
        };
        process_list[j + 1] = key;
    }
};
