//
// Created by stellaura on 15/03/24.
//

#ifndef STATIC_REFLECTION_TRAVERSAL_H
#define STATIC_REFLECTION_TRAVERSAL_H

#include "functional"

// ==============================================
// 利用 typeinfo 遍历类
// 调用 field 里面的 所有的 不需要参数的 函数
//    // 递归写法
// template <std::size_t Index = 0, typename... Args, typename Class>
// void traversal_function(const std::tuple<Args...> &infos, Class element) {
//    if constexpr (Index >= sizeof...(Args)) {
//        return;
//    } else {
//        if constexpr (auto info = std::get<Index>(infos); info.is_function() && info.get_parameter_size() == 0) {
//            std::invoke(info.pointer, element);
//        }
//        traversal_function<Index + 1>(infos, element);
//    }
//}

namespace detail {
template <typename T, typename Class>
void invoke_if_function(T &&info, Class &&element) {
    if (info.is_function() && info.get_parameter_size() == 0) {
        std::invoke(info.pointer, element);
    }
}

template <typename... Args, typename Class, std::size_t... Is>
void traversal_implement(const std::tuple<Args...> &infos, Class &&element, std::index_sequence<Is...>) {
    (invoke_if_function(std::get<Is>(infos), std::forward<Class>(element)), ...);
}

} // namespace detail
template <typename... Args, typename Class>
void traversal_function(const std::tuple<Args...> &infos, Class &&element) {
    detail::traversal_implement(infos, std::forward<Class>(element), std::index_sequence_for<Args...>{});
}

#endif // STATIC_REFLECTION_TRAVERSAL_H
