#include <iostream>
#include "cpu.hpp"
using namespace std;

int main()
{
    CPU cpu;
    string command;
    while (cin >> command)
    {
        if (command == "ON")
        {
            int N;
            cin >> N;

            string message = (cpu.initialize(N)) ? "success" : "failure";
            cout << message << endl;
        }
        else if (command == "SPAWN")
        {
            int P_ID;
            cin >> P_ID;

            cpu.spawnTask(P_ID);
        }
        else if (command == "RUN")
        {
            int C_ID;
            cin >> C_ID;

            cpu.runTask(C_ID);
        }
        else if (command == "SLEEP")
        {
            int C_ID;
            cin >> C_ID;

            cpu.sleepCore(C_ID);
        }
        else if (command == "SHUTDOWN")
        {
            cpu.shutdown();
        }
        else if (command == "SIZE")
        {
            int C_ID;
            cin >> C_ID;

            int size = cpu.getSize(C_ID);

            if (size == -1)
            {
                cout << "failure" << endl;
            }
            else
            {
                cout << "size is " << size << endl;
            }
        }
        else if (command == "CAPACITY")
        {
            int C_ID;
            cin >> C_ID;

            int capacity = cpu.getCapacity(C_ID);

            if (capacity == -1)
            {
                cout << "failure" << endl;
            }
            else
            {
                cout << "capacity is " << capacity << endl;
            }
        }
        else if (command == "EXIT")
        {
            break;
        }
    }
    return 0;
}