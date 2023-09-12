#include "Alg/SJF.h"


ShortestJobFirst_Scheduler::ShortestJobFirst_Scheduler(){} //constructor

ShortestJobFirst_Scheduler::~ShortestJobFirst_Scheduler(){} //destructor

void ShortestJobFirst_Scheduler::add_process(Process *process1)
{
    process_list.push_back(*process1);
    this->sort();
    
}

void ShortestJobFirst_Scheduler::schedule()
{
    Process process = process_list[0]; // pega o primeiro elemento do array, com tempo de ex menor
    process.start();
    

}

void ShortestJobFirst_Scheduler::sort() 
{
    int size = process_list.size();
    for (int i = 1; i < size; i++) {
        Process key = process_list[i];
        int j = i-1;

        while (key.getDuration() < process_list[j].getDuration() && j >= 0) {
            process_list[j + 1] = process_list[j];
            j--;
        }
        process_list[j+1] = key;
    }
}