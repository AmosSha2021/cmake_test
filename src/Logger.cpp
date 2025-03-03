#include "Logger.h"
#include <sstream>


Logger::Logger(const std::string& logFile, Level minLevel)
    : minLevel(minLevel) {
    logStream.open(logFile, std::ios::out | std::ios::app);
    if (!logStream.is_open()) {
        std::cerr << "Failed to open log file: " << logFile << std::endl;
    }
}

Logger::~Logger() {
    if (logStream.is_open()) {
        logStream.close();
    }
}

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

const char* Logger::levelToString(Level level) {
    switch (level) {
        case Level::Debug:   return "DEBUG";
        case Level::Info:    return "INFO";
        case Level::Warning: return "WARNING";
        case Level::Error:   return "ERROR";
        default:             return "UNKNOWN";
    }
}

void Logger::log(Level level, const std::string& message) {
    if (level >= minLevel) {
        const std::string logEntry = "[" + getCurrentTimestamp() + "] " 
            + "[" + levelToString(level) + "] " + message;
        
        // 同时输出到控制台和文件
        std::cout << logEntry << std::endl;
        if (logStream.is_open()) {
            logStream << logEntry << std::endl;
        }
    }
}

void Logger::debug(const std::string& message) { log(Level::Debug, message); }
void Logger::info(const std::string& message) { log(Level::Info, message); }
void Logger::warning(const std::string& message) { log(Level::Warning, message); }
void Logger::error(const std::string& message) { log(Level::Error, message); }
