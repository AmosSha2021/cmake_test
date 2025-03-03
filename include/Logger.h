#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

class Logger {
public:
    enum class Level { Debug, Info, Warning, Error };

    explicit Logger(const std::string& logFile = "app.log", 
                   Level minLevel = Level::Info);
    ~Logger();

    void log(Level level, const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

private:
    Level minLevel;
    std::ofstream logStream;
    
    static const char* levelToString(Level level);
    std::string getCurrentTimestamp();
};
