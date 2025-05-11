#ifndef DEQUE_HPP
#define DEQUE_HPP

class Deque
{
private:
    int front;
    int rear;
    int capacity;
    int currSize;
    int *tasks;
    void resizeTasks(int newCapacity);

public:
    Deque();
    ~Deque();

    void pushFront(int taskId);
    void pushBack(int taskId);
    void popFront();
    void popBack();

    bool isEmpty();
    bool isFull();

    int getSize();
    int getCapacity();
    int getFront();
    int getBack();
};

#endif
