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

class LOG_API Logger {  // 导出类
public:
    enum class Level { Debug, Info, Warning, Error };

    // 支持上下文标识的构造函数
    explicit Logger(const std::string& logFile, 
                  const std::string& contextID,
                  Level minLevel = Level::Info);
                  
    // 保持原有构造函数兼容性
    // explicit Logger(const std::string& logFile = "app.log", 
    //               Level minLevel = Level::Info);
    ~Logger();

    void log(Level level, const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

    // 上下文标识设置接口
    void setContextID(const std::string& id) { contextID = id; }

private:
    std::string contextID;
    Level minLevel;
    std::ofstream logStream;
    std::mutex logMutex;
    
    static const char* levelToString(Level level);
    std::string getCurrentTimestamp();
};
