#include "log.h"
#include <iostream>
#include <ctime>

Logger::Logger()
{
    logFile.open("log.log", std::ios::out | std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "无法打开日志文件" << std::endl;
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string &message, LogLevel level)
{
    std::lock_guard<std::mutex> guard(logMutex);
    if (logFile.is_open())
    {
        std::time_t now = std::time(nullptr);
        logFile << std::ctime(&now) << " [" << getLogLevelString(level) << "] " << message << std::endl;
    }
}

std::string Logger::getLogLevelString(LogLevel level)
{
    switch (level)
    {
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}
