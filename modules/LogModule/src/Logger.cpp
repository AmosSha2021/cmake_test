#include "Logger.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <filesystem>

using namespace std;

Logger::Logger(const std::string& logFile, 
             const std::string& contextID,
             Level minLevel)
    : contextID(contextID), minLevel(minLevel) 
{
    if (auto pos = logFile.find_last_of("/\\"); pos != string::npos) {
        filesystem::path dir(logFile.substr(0, pos));
        if (!filesystem::exists(dir)) {
            filesystem::create_directories(dir);
        }
    }

    logStream.open(logFile, ios::app);
}

Logger::~Logger() {
    if (logStream.is_open()) {
        logStream.close();
    }
}

bool Logger::isValid() const {
    return logStream.is_open();
}

void Logger::log(Level level, const string& message) {
    if (level < minLevel) return;

    lock_guard<mutex> guard(logMutex);
    logStream << "[" << getCurrentTimestamp() << "]"
              << "[" << contextID << "]"
              << "[" << levelToString(level) << "] "
              << message << endl;
}

// 其他方法实现保持不变，但需要添加：
void Logger::setContextID(const string& id) {
    lock_guard<mutex> guard(logMutex);
    contextID = id;
}

void Logger::debug(const string& message) { log(Level::Debug, message); }
void Logger::info(const string& message) { log(Level::Info, message); }
void Logger::warning(const string& message) { log(Level::Warning, message); }
void Logger::error(const string& message) { log(Level::Error, message); }

const char* Logger::levelToString(Level level) {
    switch(level) {
        case Level::Debug: return "DEBUG";
        case Level::Info: return "INFO";
        case Level::Warning: return "WARNING";
        case Level::Error: return "ERROR";
        default: return "UNKNOWN";
    }
}

string Logger::getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    
    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}