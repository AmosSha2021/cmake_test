#include <iostream>
#include <vector>
#include "Logger.h"
#include "Calculate.h"

int main() {
    // 新增核心模块测试
    std::cout << "core module test" << std::endl;
    std::cout << "5 + 3 = " << Calculate::add(5, 3) << std::endl;
    std::cout << "5 * 3 = " << Calculate::multiply(5, 3) << std::endl;
    std::cout << "square(5) = " << Calculate::square(5) << std::endl;
    
    try {
        // 初始化带上下文标识的日志器
        Logger mLogger("test_log.log", "MAIN_CTX", Logger::Level::Debug);

        // 测试用例1：基础日志功能
        mLogger.debug("Debug message should be visible");
        mLogger.info("Application started");
        mLogger.warning("Low disk space warning");
        mLogger.error("Failed to open file");

        std::cout << "所有日志测试已完成" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "run error: " << e.what() << std::endl;
    }
    return 0;
}