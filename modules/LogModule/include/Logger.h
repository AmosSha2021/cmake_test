#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <mutex>

#ifdef _WIN32
    #ifdef LOG_MODULE_EXPORTS
        #define LOG_API __declspec(dllexport)
    #else
        #define LOG_API __declspec(dllimport)
    #endif
#else
    #define LOG_API __attribute__((visibility("default")))
#endif

class LOG_API Logger {
public:
    enum class Level { Debug, Info, Warning, Error };

    LOG_API explicit Logger(const std::string& logFile, 
                          const std::string& contextID,
                          Level minLevel = Level::Info);
                          
    LOG_API ~Logger();

    // 禁用拷贝
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    LOG_API void log(Level level, const std::string& message);
    LOG_API void debug(const std::string& message);
    LOG_API void info(const std::string& message);
    LOG_API void warning(const std::string& message);
    LOG_API void error(const std::string& message);

    LOG_API void setContextID(const std::string& id);
    LOG_API bool isValid() const;

private:
    std::string contextID;
    Level minLevel;
    std::ofstream logStream;
    std::mutex logMutex;
    
    LOG_API static const char* levelToString(Level level);
    LOG_API std::string getCurrentTimestamp();
};
