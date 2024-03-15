//
// Created by stellaura on 14/03/24.
//

#include "TestClass.h"
#include "fmt/format.h"
#include <utility>

TestClass::TestClass() = default;

TestClass::TestClass(std::string name) : name(std::move(name)) {}

TestClass::~TestClass() = default;

std::string TestClass::get_name() const {
    fmt::println("in function get_name with name {}", name);
    return name;
}

void TestClass::test_func1() { fmt::println("in function test 1 with name {}", name); };
