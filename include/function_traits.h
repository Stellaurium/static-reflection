//
// Created by stellaura on 15/03/24.
//

#ifndef STATIC_REFLECTION_FUNCTION_TRAITS_H
#define STATIC_REFLECTION_FUNCTION_TRAITS_H

#include <tuple>

// ==============================================================
// tool template define
namespace detail {
template <typename Return, typename... Parameters>
struct basic_function {
    using return_type = Return;
    using parameters_tuple = std::tuple<Parameters...>;
    static constexpr std::size_t parameter_size = sizeof...(Parameters);
    static constexpr std::size_t get_parameter_size() { return parameter_size; }
};

template <typename Return, typename Class, typename... Parameters>
struct basic_member_function : basic_function<Return, Parameters...> {
    using class_type = Class;
};

template <bool is_member_function_pointer_>
struct member_function_pointer_flag {
    constexpr static bool is_member_function_pointer = is_member_function_pointer_;
    static constexpr bool is_member_function() { return is_member_function_pointer; }
};

template <bool is_const_member_function_pointer_>
struct const_member_function_pointer_flag {
    constexpr static bool is_const_member_function_pointer = is_const_member_function_pointer_;
    // 该函数只有在已经是 成员函数的类型中 可以调用
    // 如果调用不是 普通函数作为参数的类 就根本没有这个函数
    static constexpr bool is_const_member_function() { return is_const_member_function_pointer; }
};
} // namespace detail

// ==============================================================
// declaration and define function_traits
namespace detail {
template <typename T>
struct function_traits;

// function traits for function pointer
template <typename Return, typename... Parameters>
struct function_traits<Return (*)(Parameters...)> : basic_function<Return, Parameters...>,
                                                    member_function_pointer_flag<false> {};

// function traits for pointer to member function
template <typename Return, typename Class, typename... Parameters>
struct function_traits<Return (Class::*)(Parameters...)> : basic_member_function<Return, Class, Parameters...>,
                                                           member_function_pointer_flag<true>,
                                                           const_member_function_pointer_flag<false> {};

// function traits for pointer to member function
template <typename Return, typename Class, typename... Parameters>
struct function_traits<Return (Class::*)(Parameters...) const> : basic_member_function<Return, Class, Parameters...>,
                                                                 member_function_pointer_flag<true>,
                                                                 const_member_function_pointer_flag<true> {};
} // namespace detail

#endif // STATIC_REFLECTION_FUNCTION_TRAITS_H
