#include "Logger.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>  // 添加此头文件
#include <filesystem>  // 新增头文件

using namespace std;

// 新构造函数实现
Logger::Logger(const std::string& logFile, 
             const std::string& contextID,
             Level minLevel)
    : contextID(contextID), minLevel(minLevel) 
{
    // 优化后的目录创建逻辑
    if (auto pos = logFile.find_last_of("/\\"); pos != std::string::npos) {
        std::filesystem::path dir(logFile.substr(0, pos));
        if (!std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
        }
    }

    logStream.open(logFile, std::ios::app);
    if (!logStream.is_open()) {
        throw std::runtime_error("can not open the log file " + logFile);
    }
}

// 原构造函数委托给新构造函数
// Logger::Logger(const std::string& logFile, Level minLevel)
//     : Logger(logFile, "SYSTEM", minLevel) {}

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
    std::lock_guard<std::mutex> lock(logMutex);
    
    if (level >= minLevel) {
        const std::string logEntry = "[" + getCurrentTimestamp() + "] " 
            + "[" + contextID + "] "
            + "[" + levelToString(level) + "] " + message;
            
        //std::cout << logEntry << std::endl;
        if (logStream.is_open()) {
            logStream << logEntry << std::endl;
        }
    }
}

// 保持快捷方法不变
void Logger::debug(const std::string& message) { log(Level::Debug, message); }
void Logger::info(const std::string& message) { log(Level::Info, message); }
void Logger::warning(const std::string& message) { log(Level::Warning, message); }
void Logger::error(const std::string& message) { log(Level::Error, message); }
