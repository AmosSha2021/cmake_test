#include <iostream>
#include "Logger.h"


using namespace std;

int main() {
    // 创建日志记录器，指定日志文件路径
    Logger logger("runtime.log", Logger::Level::Debug);
    
    logger.debug("Debug message with timestamp");
    logger.info("Application initialized");
    logger.warning("Low disk space");
    logger.error("Critical system failure");
    std::cout << "Hello, world!" << std::endl;
    return 0;
}