// fcfs.h

#ifndef FCFS_H
#define FCFS_H

#include "process.h"
#include <vector>
#include <string>

void scheduleFCFS(const std::vector<Process *> &processes, bool saveToFile = false, const std::string &filename = "");

#endif // FCFS_H
