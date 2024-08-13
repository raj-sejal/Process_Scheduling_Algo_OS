// fcfs.cpp

#include "fcfs.h"
#include <iostream>
#include <fstream>
#include <iomanip> // For std::setw
#include <algorithm>

// Function to calculate waiting time, turnaround time, burst time, average waiting time, and response time
// Function to calculate waiting time, turnaround time, burst time, average waiting time, and response time
void calculateMetrics(const std::vector<Process *> &processes, std::vector<int> &waitingTime, std::vector<int> &turnaroundTime, std::vector<int> &burstTime, double &avgWaitingTime, std::vector<int> &responseTime)
{
    int totalProcesses = processes.size();
    waitingTime.resize(totalProcesses);
    turnaroundTime.resize(totalProcesses);
    burstTime.resize(totalProcesses);
    responseTime.resize(totalProcesses);

    // Calculate completion time for each process
    int completionTime = 0;
    for (int i = 0; i < totalProcesses; ++i)
    {
        completionTime = std::max(completionTime, processes[i]->getArrivalTime()) + processes[i]->getExecuteTime();
        turnaroundTime[i] = completionTime - processes[i]->getArrivalTime();
    }

    // Calculate waiting time, burst time, and response time
    for (int i = 0; i < totalProcesses; ++i)
    {
        burstTime[i] = processes[i]->getExecuteTime();
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        responseTime[i] = waitingTime[i]; // For FCFS, response time equals waiting time
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
void printMetricsTable(const std::vector<Process *> &processes, const std::vector<int> &waitingTime, const std::vector<int> &turnaroundTime, const std::vector<int> &burstTime, double avgWaitingTime, const std::vector<int> &responseTime)
{
    int totalProcesses = processes.size();

    // Print header
    std::cout << std::setw(15) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::setw(15) << "Waiting Time" << std::setw(20) << "Turnaround Time" << std::setw(15) << "Response Time"
              << "\n";
    for (int i = 0; i < totalProcesses; ++i)
    {
        std::cout << std::setw(15) << processes[i]->getProcessName() << std::setw(15) << processes[i]->getArrivalTime() << std::setw(15) << burstTime[i] << std::setw(15) << waitingTime[i] << std::setw(20) << turnaroundTime[i] << std::setw(15) << responseTime[i] << "\n";
    }
    std::cout << "\nAverage Waiting Time: " << avgWaitingTime << "\n";
}

// Function to save process metrics to a file in table format
void saveMetricsToFile(const std::vector<Process *> &processes, const std::vector<int> &waitingTime, const std::vector<int> &turnaroundTime, const std::vector<int> &burstTime, double avgWaitingTime, const std::vector<int> &responseTime, const std::string &filename)
{
    std::ofstream outfile(filename);

    if (outfile.is_open())
    {
        int totalProcesses = processes.size();

        // Write header to file
        outfile << std::setw(15) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::setw(15) << "Waiting Time" << std::setw(20) << "Turnaround Time" << std::setw(15) << "Response Time"
                << "\n";
        for (int i = 0; i < totalProcesses; ++i)
        {
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

// Function to schedule processes using FCFS (First Come First Serve) algorithm
void scheduleFCFS(const std::vector<Process *> &processes, bool saveToFile, const std::string &filename)
{
    // Create a copy of the input vector to preserve the original order
    std::vector<Process *> sortedProcesses = processes;

    std::vector<int> waitingTime;
    std::vector<int> turnaroundTime;
    std::vector<int> burstTime;
    double avgWaitingTime;
    std::vector<int> responseTime;

    // Sort the copy of the input vector based on arrival time (FCFS)
    std::sort(sortedProcesses.begin(), sortedProcesses.end(), [](const Process *a, const Process *b)
              {
    // Use const_cast to cast away constness and call non-const member function
    return const_cast<Process*>(a)->getArrivalTime() < const_cast<Process*>(b)->getArrivalTime(); });

    // Calculate metrics for the sorted copy
    calculateMetrics(sortedProcesses, waitingTime, turnaroundTime, burstTime, avgWaitingTime, responseTime);

    // Print metrics table to console
    printMetricsTable(sortedProcesses, waitingTime, turnaroundTime, burstTime, avgWaitingTime, responseTime);

    // Save metrics to file if requested
    if (saveToFile)
    {
        saveMetricsToFile(sortedProcesses, waitingTime, turnaroundTime, burstTime, avgWaitingTime, responseTime, filename);
    }
}
