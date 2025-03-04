#pragma once

#ifdef CORE_MODULE_EXPORTS
    #define CORE_API __declspec(dllexport)
#else
    #define CORE_API __declspec(dllimport)
#endif

class CORE_API Calculate {
public:
    // 两数相加
    static double add(double a, double b);
    
    // 两数相乘
    static double multiply(double a, double b);
    
    // 平方计算
    static double square(double x);
};
