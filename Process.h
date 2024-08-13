#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process
{
private:
    std::string nameOfProcess;
    int arrivalTime;
    int executeTime;
    int priority;

public:
    // Constructor
    Process();

    // Setter methods
    void setProcessName(const std::string &_nameOfProcess);
    void setArrivalTime(int _arrivalTime);
    void setExecuteTime(int _executeTime);
    void setPriority(int _priority);

    // Getter methods
    std::string getProcessName();
    int getArrivalTime();
    int getExecuteTime();
    int getPriority();
};

#endif // PROCESS_H
