#include "definers/SJF.h"


ShortestJobFirst_Scheduler::ShortestJobFirst_Scheduler(){} //constructor

ShortestJobFirst_Scheduler::~ShortestJobFirst_Scheduler(){} //destructor

void ShortestJobFirst_Scheduler::add_process(int process1)
{
    process_list.push_back(process1); 
    
}

int ShortestJobFirst_Scheduler::schedule()
{
    return *process_list.begin(); // retorna o primeiro elemento do array, com tempo de ex menor
}

void ShortestJobFirst_Scheduler::sort() 
{
    int size = process_list.size();
    for (int i = 1; i < size; i++) {
        int key = process_list[i];
        int j = i-1;

        while (key < process_list[j] && j >= 0) {
            process_list[j + 1] = process_list[j];
            j--;
        }
        process_list[j+1] = key;
    }
}