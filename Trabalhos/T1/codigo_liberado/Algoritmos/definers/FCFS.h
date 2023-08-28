#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <vector>

class FCFS_Scheduler {
public:
    FCFS_Scheduler();

    void addTask(int arrivalTime, int burstTime);
    void execute();

private:
    std::vector<std::pair<int, int>> tasks; // pair of (arrivalTime, burstTime)
};

#endif // FCFS_SCHEDULER_H
