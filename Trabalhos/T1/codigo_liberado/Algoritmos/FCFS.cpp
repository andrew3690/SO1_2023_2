#include "definers/FCFS.h"
#include <iostream>

FCFS_Scheduler::FCFS_Scheduler() {
}

void FCFS_Scheduler::addTask(int arrivalTime, int burstTime) {
    tasks.push_back(std::make_pair(arrivalTime, burstTime));
}

void FCFS_Scheduler::execute() {
    int currentTime = 0;

    for (const auto& task : tasks) {
        if (task.first > currentTime) {
            currentTime = task.first;
        }

        std::cout << "Task executed: Arrival Time = " << task.first << ", Burst Time = " << task.second << std::endl;
        
        currentTime += task.second;
    }
}

int main() {
    FCFS_Scheduler scheduler;
    scheduler.addTask(0, 6);
    scheduler.addTask(2, 4);
    scheduler.addTask(4, 3);
    scheduler.execute();

    return 0;
}
