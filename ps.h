// fcfs.h

#ifndef PS_H
#define PS_H

#include "process.h"
#include <vector>
#include <string>

void schedulePS(const std::vector<Process *> &processes, bool saveToFile = false, const std::string &filename = "");

#endif // PS_H
