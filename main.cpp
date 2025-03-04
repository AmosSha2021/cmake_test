#include <iostream>
#include <vector>
#include "Logger.h"
#include "Calculate.h"
#include <thread>
#include <atomic>

// 新增测试函数
void dut_test(int dut_id) {
    try {
        std::string log_file = "logs/dut" + std::to_string(dut_id) + "_test.log";
        Logger logger(log_file, "DUT_" + std::to_string(dut_id), Logger::Level::Debug);
        
        for(int i=0; i<100; ++i){
            logger.info("DUT" + std::to_string(dut_id) + "loop test #" + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } catch(const std::exception& e) {
        std::cerr << "DUT" << dut_id << "error: " << e.what() << std::endl;
    }
}

int main() {
    // 新增核心模块测试
    std::cout << "core module test" << std::endl;
    std::cout << "5 + 3 = " << Calculate::add(5, 3) << std::endl;
    std::cout << "5 * 3 = " << Calculate::multiply(5, 3) << std::endl;
    std::cout << "square(5) = " << Calculate::square(5) << std::endl;
    
    try {
        // 新增多线程测试
        constexpr int DUT_NUM = 3;
        std::vector<std::thread> workers;
        
        std::cout << "start to thread test..." << std::endl;
        for(int i=0; i<DUT_NUM; ++i){
            workers.emplace_back(dut_test, i+1); // DUT编号从1开始
        }
        
        // 等待所有线程完成
        for(auto& t : workers){
            t.join();
        }
        std::cout << "all dut test done" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "error on main thread: " << e.what() << std::endl;
    }

    return 0;
}