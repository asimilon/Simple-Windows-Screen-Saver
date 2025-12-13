//
// Created by asimi on 13/12/2025
//

#pragma once
#include <atomic>

class SharedState
{
public:
    bool isRunning() const
    {
        return runningCount > 0;
    }

    void start()
    {
        isPreviewing = true;
        runningCount++;
    }

    void stop()
    {
        isPreviewing = false;
        runningCount--;
    }

    std::atomic<bool> isPreviewing { false };
private:
    size_t runningCount { 0 };
};
