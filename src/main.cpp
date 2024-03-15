#include "TestClass.h"
#include "catch2/catch_all.hpp"
#include "field_traits.h"
#include "fmt/format.h"
#include "traversal.h"
#include "type_info.h"
#include <string>
#include <type_traits>

bool function(int, double){};

TEST_CASE("function traits") {
    SECTION("function pointer") {
        auto func_prt = &function;
        using function_type_info = detail::function_traits<decltype(func_prt)>;
        using return_type = function_type_info::return_type;
        using parameters = function_type_info::parameters_tuple;
        static_assert(std::is_same_v<return_type, bool>);
        static_assert(std::is_same_v<parameters, std::tuple<int, double>>);
    }
    SECTION("member function pointer") {
        // 根本不需要实例化就可以直接创建类型的信息 (因为没有模板函数)
        TestClass test("alex");
        auto member_ptr = &TestClass::get_name;
        using function_type_info = detail::function_traits<decltype(member_ptr)>;
        using return_type = function_type_info::return_type;
        using parameters = function_type_info::parameters_tuple;
        using class_type = function_type_info::class_type;
        constexpr bool is_member_function = function_type_info::is_member_function_pointer;
        constexpr bool is_const_member_function = function_type_info::is_const_member_function_pointer;

        // Test
        static_assert(std::is_same_v<return_type, std::string>);
        static_assert(std::is_same_v<parameters, std::tuple<>>);
        static_assert(std::is_same_v<class_type, TestClass>);
        static_assert(is_member_function);
        static_assert(is_const_member_function);
    }
}

TEST_CASE("field traits") {
    SECTION("test_function1") {
        auto field1 = field_traits{&TestClass::test_func1};
        REQUIRE(field1.pointer == &TestClass::test_func1);
        REQUIRE(field1.is_function() == true);
        REQUIRE(field1.is_variable() == false);
        REQUIRE(field1.is_member_function() == true);
        REQUIRE(field1.is_const_member_function() == false);
    }
    SECTION("get_name") {
        auto field2 = field_traits{&TestClass::get_name};
        REQUIRE(field2.pointer == &TestClass::get_name);
        REQUIRE(field2.is_function() == true);
        REQUIRE(field2.is_variable() == false);
        REQUIRE(field2.is_member_function() == true);
        REQUIRE(field2.is_const_member_function() == true);
    }
    SECTION("function") {
        auto field3 = field_traits{&function};
        REQUIRE(field3.pointer == &function);
        REQUIRE(field3.is_function() == true);
        REQUIRE(field3.is_variable() == false);
        REQUIRE(field3.is_member_function() == false);
        //        REQUIRE(field3.is_const_member_function() == true);
    }
}

// 注册 TestClass的信息
BEGIN_CLASS_REGISTER(TestClass)
BEGIN_FIELD_REGISTER(FIELD(&TestClass::get_name), FIELD(&TestClass::test_func1))
END_REGISTER()

TEST_CASE("type info") {
    constexpr auto class_info = type_info<TestClass>{};
    static_assert(std::is_same_v<decltype(class_info)::class_type, TestClass>);
    REQUIRE(std::get<0>(class_info.fields).name == "get_name");
    REQUIRE(std::get<0>(class_info.fields).pointer == &TestClass::get_name);
    TestClass test("alex");
    traversal_function(class_info.fields, test);
}
