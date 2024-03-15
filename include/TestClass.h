//
// Created by stellaura on 14/03/24.
//

#ifndef STATIC_REFLECTION_TESTCLASS_H
#define STATIC_REFLECTION_TESTCLASS_H

#include "fmt/format.h"
#include <string>

class TestClass {
  public:
    TestClass();
    explicit TestClass(std::string name);
    ~TestClass();

    std::string name;

    // 如果这个是模板会怎么样 重载会怎么样 是否还能正常使用反射
    // 如果是 模板函数
    // 那么需要在取地址的时候 明确的告诉编译器 模板函数的参数类型是什么
    // 然后就可以正常地获得函数的成员函数指针
    // 例如 void (Person::*memberPtr)(const std::string&) = &Person::templateFunction<std::string>
    [[nodiscard]] std::string get_name() const;
    void test_func1();
};


#endif // STATIC_REFLECTION_TESTCLASS_H
