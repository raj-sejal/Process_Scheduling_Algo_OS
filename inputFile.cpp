// inputFile.cpp

// Include the corresponding header file for function declarations
#include "inputFile.h"

#include <iostream>

// Function to take input for process name from the user
void takeInputProcessName(std::string &name)
{
    std::cout << "Enter process name: ";
    std::cin >> name;
}

// Function to take input for arrival time from the user
void takeInputArrivalTime(int &arrivalTime)
{
    std::cout << "Enter arrival time: ";
    std::cin >> arrivalTime;
}

// Function to take input for execution time from the user
void takeInputExecuteTime(int &executeTime)
{
    std::cout << "Enter execution time: ";
    std::cin >> executeTime;
}

void takeInputPriority(int &priority)
{
    std::cout << "Enter Priority of the Given Process: ";
    std::cin >> priority;
}

// Function to set attributes of the current process
void setAttributesOfCurrentProcess(Process *process, std::string name, int arrivalTime, int executeTime, int priority)
{
    process->setProcessName(name);
    process->setArrivalTime(arrivalTime);
    process->setExecuteTime(executeTime);
    process->setPriority(priority);
}

// Function to take input for processes from the user
void takeInputProcess(int numProcesses, std::vector<Process *> &processes)
{
    for (int i = 0; i < numProcesses; ++i)
    {
        Process *process = new Process(); // Create a new Process object
        std::string name;
        int arrivalTime, executeTime, priority;

        // Call functions to take input for process details
        takeInputProcessName(name);
        takeInputArrivalTime(arrivalTime);
        takeInputExecuteTime(executeTime);
        takeInputPriority(priority);

        // Set attributes of the current process
        setAttributesOfCurrentProcess(process, name, arrivalTime, executeTime, priority);

        // Add the process to the vector
        processes.push_back(process);
    }
}

// Function to input processes from the user and return them as a vector
std::vector<Process *> inputProcesses()
{
    std::vector<Process *> processes; // Vector to store pointers to Process objects
    int numProcesses;
    std::cout << "Enter the number of processes: ";
    std::cin >> numProcesses;

    // Call function to take input for processes
    takeInputProcess(numProcesses, processes);

    return processes;
}
