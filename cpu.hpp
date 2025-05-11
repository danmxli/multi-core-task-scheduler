#ifndef CPU_HPP
#define CPU_HPP

#include "deque.hpp"

class CPU
{
private:
    Deque *cores;
    int numCores;
    bool isInitialized;
    int findCoreIdWithLeastTasks();
    int findCoreIdWithLeastTasksExcluding(int C_ID);
    int findCoreIdWithMostTasks();

public:
    CPU();
    ~CPU();

    bool initialize(int N);
    void spawnTask(int P_ID);
    void runTask(int C_ID);
    void sleepCore(int C_ID);
    void shutdown();

    int getSize(int C_ID);
    int getCapacity(int C_ID);
};

#endif
