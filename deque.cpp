#include <iostream>
#include "deque.hpp"
using namespace std;

void Deque::resizeTasks(int newCapacity)
{
    int *newTasks = new int[newCapacity];
    for (int i = 0; i < currSize; i++)
    {
        newTasks[i] = tasks[(front + i) % capacity];
    }
    delete[] tasks;
    tasks = newTasks;
    front = 0;
    rear = currSize - 1;
    capacity = newCapacity;
}

Deque::Deque() : front(-1), rear(-1), capacity(4), currSize(0), tasks(new int[4])
{
}

Deque::~Deque()
{
    delete[] tasks;
}

void Deque::pushFront(int taskId)
{
    if (isEmpty())
    {
        front = rear = 0;
    }
    else
    {
        front = (front - 1 + capacity) % capacity;
    }

    tasks[front] = taskId;
    currSize++;

    if (isFull())
    {
        resizeTasks(capacity * 2);
    }
}

void Deque::pushBack(int taskId)
{
    if (isEmpty())
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % capacity;
    }
    tasks[rear] = taskId;
    currSize++;

    if (isFull())
    {
        resizeTasks(capacity * 2);
    }
}

void Deque::popFront()
{
    if (isEmpty())
    {
        return;
    }
    front = (front + 1) % capacity;
    currSize--;

    if (isEmpty())
    {
        front = rear = -1;
    }
    else if (currSize == (capacity / 4) && capacity > 2 && currSize > 0)
    {
        resizeTasks(capacity / 2);
    }
}

void Deque::popBack()
{
    if (isEmpty())
    {
        return;
    }
    rear = (rear - 1 + capacity) % capacity;
    currSize--;

    if (isEmpty())
    {
        front = rear = -1;
    }
    else if (currSize == (capacity / 4) && capacity > 2 && currSize > 0)
    {
        resizeTasks(capacity / 2);
    }
}

bool Deque::isEmpty()
{
    return currSize == 0;
}

bool Deque::isFull()
{
    return currSize == capacity;
}

int Deque::getSize()
{
    return currSize;
}

int Deque::getCapacity()
{
    return capacity;
}

int Deque::getFront()
{
    if (isEmpty())
    {
        return -1;
    }
    return tasks[front];
}

int Deque::getBack()
{
    if (isEmpty())
    {
        return -1;
    }
    return tasks[rear];
}