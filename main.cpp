#include "inputFile.h"
#include "fcfs.h"
#include "sjf.h"
#include "ps.h"
#include <iostream>
#include <ctime> // For generating unique filename based on timestamp

int main()
{
    // Input processes
    std::vector<Process *> processes = inputProcesses();

    // Ask user whether to save metrics to a file
    char saveToFileInput;
    bool saveToFile = false;
    while (true)
    {
        std::cout << "Do you want to save process metrics to a file? (y/n): ";
        std::cin >> saveToFileInput;
        if (saveToFileInput == 'y' || saveToFileInput == 'Y')
        {
            saveToFile = true;
            break;
        }
        else if (saveToFileInput == 'n' || saveToFileInput == 'N')
        {
            break;
        }
        else
        {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }

    // Generate unique filename based on current timestamp
    std::time_t currentTime = std::time(nullptr);
    std::string filenameFCFS = "metrics_FCFS_" + std::to_string(currentTime) + ".txt";
    std::string filenameSJF = "metrics_SJF_" + std::to_string(currentTime) + ".txt";
    std::string filenamePS = "metrics_PS_" + std::to_string(currentTime) + ".txt";

    // Schedule processes using FCFS algorithm
    scheduleFCFS(processes, saveToFile, filenameFCFS);

    // Schedule processes using SJF algorithm
    scheduleSJF(processes, saveToFile, filenameSJF);

    // Schedule processes using SJF algorithm
    schedulePS(processes, saveToFile, filenamePS);

    // Clean up memory
    for (auto &process : processes)
    {
        delete process;
    }

    return 0;
}