#include "sjf.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <limits.h>

// Function to calculate waiting time, turnaround time, burst time, average waiting time, and response time
void calculateMetricsSJF(const std::vector<Process *> &sortedProcesses, std::vector<int> &waitingTime, std::vector<int> &turnaroundTime, std::vector<int> &burstTime, double &avgWaitingTime, std::vector<int> &responseTime, std::vector<int> &orderOfExecution)
{
    int totalProcesses = sortedProcesses.size();
    waitingTime.resize(totalProcesses);
    turnaroundTime.resize(totalProcesses);
    burstTime.resize(totalProcesses);
    responseTime.resize(totalProcesses);
    std::vector<int> completed(totalProcesses, 0);
    int currentTime = sortedProcesses[0]->getArrivalTime();
    for (int i = 0; i < totalProcesses; i++)
    {
        int processToExecute = -1;
        int timeToExecuteCurPro = INT_MAX;
        for (int j = 0; j < totalProcesses; j++)
        {
            if (completed[j] == 0)
            {
                if (sortedProcesses[j]->getArrivalTime() > currentTime)
                    break;
                if (sortedProcesses[j]->getExecuteTime() <= timeToExecuteCurPro)
                {
                    timeToExecuteCurPro = sortedProcesses[j]->getExecuteTime();
                    processToExecute = j;
                }
            }
        }
        orderOfExecution.push_back(processToExecute);
        waitingTime[processToExecute] = currentTime - sortedProcesses[processToExecute]->getArrivalTime();
        completed[processToExecute] = 1;
        turnaroundTime[processToExecute] = currentTime + sortedProcesses[processToExecute]->getExecuteTime() - sortedProcesses[processToExecute]->getArrivalTime();
        burstTime[processToExecute] = sortedProcesses[processToExecute]->getExecuteTime();
        responseTime[processToExecute] = waitingTime[processToExecute];
        currentTime += sortedProcesses[processToExecute]->getExecuteTime();
    }

    // Calculate average waiting time
    double totalWaitingTime = 0;
    for (int i = 0; i < totalProcesses; ++i)
    {
        totalWaitingTime += waitingTime[i];
    }
    avgWaitingTime = totalWaitingTime / totalProcesses;
}

// Function to print process metrics in table format on console
void printMetricsTableSJF(const std::vector<Process *> &processes, const std::vector<int> &waitingTime, const std::vector<int> &turnaroundTime, const std::vector<int> &burstTime, double avgWaitingTime, const std::vector<int> &responseTime, const std::vector<int> &orderOfExecution)
{
    int totalProcesses = processes.size();

    // Print header
    std::cout << std::setw(15) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::setw(15) << "Waiting Time" << std::setw(20) << "Turnaround Time" << std::setw(15) << "Response Time"
              << "\n";
    for (int j = 0; j < totalProcesses; ++j)
    {
        int i = orderOfExecution[j];
        std::cout << std::setw(15) << processes[i]->getProcessName() << std::setw(15) << processes[i]->getArrivalTime() << std::setw(15) << burstTime[i] << std::setw(15) << waitingTime[i] << std::setw(20) << turnaroundTime[i] << std::setw(15) << responseTime[i] << "\n";
    }
    std::cout << "\nAverage Waiting Time: " << avgWaitingTime << "\n";
}

// Function to save process metrics to a file in table format
void saveMetricsToFileSJF(const std::vector<Process *> &processes, const std::vector<int> &waitingTime, const std::vector<int> &turnaroundTime, const std::vector<int> &burstTime, double avgWaitingTime, const std::vector<int> &responseTime, const std::string &filename, const std::vector<int> &orderOfExecution)
{
    std::ofstream outfile(filename);

    if (outfile.is_open())
    {
        int totalProcesses = processes.size();

        // Write header to file
        outfile << std::setw(15) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::setw(15) << "Waiting Time" << std::setw(20) << "Turnaround Time" << std::setw(15) << "Response Time"
                << "\n";
        for (int j = 0; j < totalProcesses; ++j)
        {
            int i = orderOfExecution[j];
            outfile << std::setw(15) << processes[i]->getProcessName() << std::setw(15) << processes[i]->getArrivalTime() << std::setw(15) << burstTime[i] << std::setw(15) << waitingTime[i] << std::setw(20) << turnaroundTime[i] << std::setw(15) << responseTime[i] << "\n";
        }
        outfile << "\nAverage Waiting Time: " << avgWaitingTime << "\n";

        std::cout << "Process metrics saved to " << filename << " successfully.\n";
        outfile.close();
    }
    else
    {
        std::cerr << "Unable to open file " << filename << " for writing.\n";
    }
}

// Function to schedule processes using SJF (Shortest Job First) algorithm
void scheduleSJF(const std::vector<Process *> &processes, bool saveToFile, const std::string &filename)
{
    std::vector<int> waitingTime;
    std::vector<int> turnaroundTime;
    std::vector<int> burstTime;
    double avgWaitingTime;
    std::vector<int> responseTime;
    std::vector<int> orderOfExecution;

    // Sort processes based on arrival time and then execution time if arrival times are the same (SJF)
    std::vector<Process *> sortedProcesses = processes;
    std::sort(sortedProcesses.begin(), sortedProcesses.end(), [](Process *a, Process *b)
              {
                  if (a->getArrivalTime() == b->getArrivalTime())
                  {
                      return a->getExecuteTime() < b->getExecuteTime(); // Sort by execution time if arrival times are the same
                  }
                  return a->getArrivalTime() < b->getArrivalTime(); // Otherwise, sort by arrival time
              });
    // Calculate metrics
    calculateMetricsSJF(sortedProcesses, waitingTime, turnaroundTime, burstTime, avgWaitingTime, responseTime, orderOfExecution);

    // Print metrics table to console
    std::cout << "EDNOF" << std::endl;
    printMetricsTableSJF(sortedProcesses, waitingTime, turnaroundTime, burstTime, avgWaitingTime, responseTime, orderOfExecution);

    // Save metrics to file if requested
    if (saveToFile)
    {
        saveMetricsToFileSJF(sortedProcesses, waitingTime, turnaroundTime, burstTime, avgWaitingTime, responseTime, filename, orderOfExecution);
    }
}
