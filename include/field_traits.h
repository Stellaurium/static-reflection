//
// Created by stellaura on 15/03/24.
//

#ifndef STATIC_REFLECTION_FIELD_TRAITS_H
#define STATIC_REFLECTION_FIELD_TRAITS_H

#include "function_traits.h"

// ======================================================================
namespace detail {
template <typename T>
struct is_function_or_member_function : std::integral_constant<bool, std::is_function_v<std::remove_pointer_t<T>> ||
                                                                         std::is_member_function_pointer_v<T>> {};
template <typename T>
constexpr bool is_function_or_member_function_v = is_function_or_member_function<T>::value;

// 用于继承使用的 分辨 类型T是 函数或者是变量
template <typename T, bool>
struct basic_field_traits {
    // 不是函数 变量的field traits
};

// 偏特化 传入的类型是广义的函数的情况
template <typename T>
struct basic_field_traits<T, true> : function_traits<T> {
    // 为方便直接在类的对象中得到function_traits的信息
    // 而不是 decltype 获得类型 然后在拿到
    // 创建一系列函数 (其中有一部分直接在 function_traits中定义)
    constexpr static bool is_function() { return true; }
    constexpr static bool is_variable() { return false; }
};
} // namespace detail

// field traits  存储类内部的一个对象 函数或者变量
template <typename T>
struct field_traits : detail::basic_field_traits<T, detail::is_function_or_member_function_v<T>> {

    constexpr explicit field_traits(T &&pointer) : pointer(pointer){};
    constexpr field_traits(T &&pointer, std::string_view name_) : pointer(pointer) {
        if (name_.size() > 1) {
            // 忽略第一个字符
            std::string_view trimmed_name = name_.substr(1);
            // 查找最后一个冒号的位置
            size_t last_position = trimmed_name.rfind(':');
            if (last_position != std::string_view::npos) {
                // 如果找到冒号，返回冒号右侧的字符串
                name = trimmed_name.substr(last_position + 1);
            } else {
                // 如果没有冒号，返回整个字符串
                name = trimmed_name;
            }
        }
    };
    T pointer;
    std::string_view name;
};

#endif // STATIC_REFLECTION_FIELD_TRAITS_H
