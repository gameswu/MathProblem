#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <memory>

enum LogLevel
{
    INFO,
    WARNING,
    ERROR
};

class Logger
{
public:
    static Logger &getInstance();
    void log(const std::string &message, LogLevel level = INFO);

private:
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    std::ofstream logFile;
    std::mutex logMutex;

    std::string getLogLevelString(LogLevel level);
};
