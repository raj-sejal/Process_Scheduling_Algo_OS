#ifndef SJF_H
#define SJF_H

#include <vector>
#include <string>
#include "process.h"

// Function prototypes
void calculateMetricsSJF(const std::vector<Process *> &processes, std::vector<int> &waitingTime, std::vector<int> &turnaroundTime, std::vector<int> &burstTime, double &avgWaitingTime, std::vector<int> &responseTime);
void printMetricsTableSJF(const std::vector<Process *> &processes, const std::vector<int> &waitingTime, const std::vector<int> &turnaroundTime, const std::vector<int> &burstTime, double avgWaitingTime, const std::vector<int> &responseTime);
void saveMetricsToFileSJF(const std::vector<Process *> &processes, const std::vector<int> &waitingTime, const std::vector<int> &turnaroundTime, const std::vector<int> &burstTime, double avgWaitingTime, const std::vector<int> &responseTime, const std::string &filename);
void scheduleSJF(const std::vector<Process *> &processes, bool saveToFile, const std::string &filename);

#endif // SJF_H
