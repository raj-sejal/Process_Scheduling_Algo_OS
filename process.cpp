#include "Process.h"

// Constructor implementation
Process::Process()
{
    // Initialize member variables to default values
    nameOfProcess = "";
    arrivalTime = 0;
    executeTime = 0;
}

// Setter methods implementation
void Process::setProcessName(const std::string &_nameOfProcess)
{
    // Set the name of the process
    nameOfProcess = _nameOfProcess;
}

void Process::setArrivalTime(int _arrivalTime)
{
    // Set the arrival time of the process
    arrivalTime = _arrivalTime;
}

void Process::setExecuteTime(int _executeTime)
{
    // Set the execution time of the process
    executeTime = _executeTime;
}

void Process::setPriority(int _priority)
{
    // Set the execution time of the process
    priority = _priority;
}

// Getter methods implementation
std::string Process::getProcessName()
{
    // Get the name of the process
    return nameOfProcess;
}

int Process::getArrivalTime()
{
    // Get the arrival time of the process
    return arrivalTime;
}

int Process::getExecuteTime()
{
    // Get the execution time of the process
    return executeTime;
}

int Process::getPriority()
{
    // Get the execution time of the process
    return priority;
}
