#include <iostream>
#include "cpu.hpp"
using namespace std;

int CPU::findCoreIdWithLeastTasks()
{
    int lowestWorkIndex = -1;
    int lowestWork = __INT_MAX__;

    for (int i = 0; i < numCores; i++)
    {
        if (cores[i].getSize() < lowestWork)
        {
            lowestWork = cores[i].getSize();
            lowestWorkIndex = i;
        }
    }

    return lowestWorkIndex;
}

int CPU::findCoreIdWithLeastTasksExcluding(int C_ID)
{
    int lowestWorkIndex = -1;
    int lowestWork = __INT_MAX__;

    for (int i = 0; i < numCores; i++)
    {
        if (i != C_ID && cores[i].getSize() < lowestWork)
        {
            lowestWork = cores[i].getSize();
            lowestWorkIndex = i;
        }
    }

    return lowestWorkIndex;
}

int CPU::findCoreIdWithMostTasks()
{
    int highestWorkIndex = -1;
    int highestWork = -1;

    for (int i = 0; i < numCores; i++)
    {
        if (cores[i].getSize() > highestWork)
        {
            highestWork = cores[i].getSize();
            highestWorkIndex = i;
        }
    }

    return highestWorkIndex;
}

CPU::CPU() : cores(nullptr), numCores(0), isInitialized(false)
{
}

CPU::~CPU()
{
    delete[] cores;
}

bool CPU::initialize(int N)
{
    if (isInitialized)
    {
        return false;
    }
    numCores = N;
    cores = new Deque[numCores];
    isInitialized = true;
    return true;
}

void CPU::spawnTask(int P_ID)
{
    if (P_ID <= 0)
    {
        cout << "failure" << endl;
        return;
    }

    int i = findCoreIdWithLeastTasks();

    cores[i].pushBack(P_ID);

    cout << "core " << i << " assigned task " << P_ID << endl;
}

void CPU::runTask(int C_ID)
{
    if (C_ID < 0 || C_ID > numCores - 1)
    {
        cout << "failure" << endl;
        return;
    }

    if (cores[C_ID].isEmpty())
    {
        cout << "core " << C_ID << " has no tasks to run" << endl;

        int i = findCoreIdWithMostTasks();
        if (!cores[i].isEmpty())
        {
            int stolenTaskId = cores[i].getBack();
            cores[i].popBack();
            cores[C_ID].pushBack(stolenTaskId);
        }

        return;
    }

    int P_ID = cores[C_ID].getFront();
    cores[C_ID].popFront();

    if (cores[C_ID].isEmpty())
    {
        int i = findCoreIdWithMostTasks();
        if (!cores[i].isEmpty())
        {
            int stolenTaskId = cores[i].getBack();
            cores[i].popBack();
            cores[C_ID].pushBack(stolenTaskId);
        }
    }

    cout << "core " << C_ID << " is running task " << P_ID << endl;
}

void CPU::sleepCore(int C_ID)
{
    if (C_ID < 0 || C_ID > numCores - 1)
    {
        cout << "failure" << endl;
        return;
    }

    if (cores[C_ID].isEmpty())
    {
        cout << "core " << C_ID << " has no tasks to assign" << endl;
        return;
    }

    while (!cores[C_ID].isEmpty())
    {
        int P_ID = cores[C_ID].getBack();
        cores[C_ID].popBack();

        int lowestWorkIndex = findCoreIdWithLeastTasksExcluding(C_ID);

        cores[lowestWorkIndex].pushBack(P_ID);
        cout << "task " << P_ID << " assigned to core " << lowestWorkIndex << " ";
    }
    cout << endl;
}

void CPU::shutdown()
{
    bool noRemainingTasks = true;

    for (int i = 0; i < numCores; i++)
    {
        if (!cores[i].isEmpty())
        {
            noRemainingTasks = false;
            break;
        }
    }

    if (noRemainingTasks)
    {
        cout << "no tasks to remove" << endl;
        return;
    }

    for (int i = 0; i < numCores; i++)
    {
        while (!cores[i].isEmpty())
        {
            int P_ID = cores[i].getFront();
            cores[i].popFront();
            cout << "deleting task " << P_ID << " from core " << i << " ";
        }
    }
    cout << endl;
}

int CPU::getSize(int C_ID)
{
    if (C_ID < 0 || C_ID > numCores - 1)
    {
        return -1;
    }
    return cores[C_ID].getSize();
}

int CPU::getCapacity(int C_ID)
{
    if (C_ID < 0 || C_ID > numCores - 1)
    {
        return -1;
    }
    return cores[C_ID].getCapacity();
}
