//
// Created by stellaura on 15/03/24.
//

#ifndef STATIC_REFLECTION_TYPE_INFO_H
#define STATIC_REFLECTION_TYPE_INFO_H

#include "field_traits.h"
// ======================================================================
// 类类型注册函数信息
// 这个仅仅是一个声明 具体的全特化实现在宏展开中
// 每当需要用一个类型的信息 都需要手动注册 然后利用宏自动展开成该模板类的全特化实现
template <typename T>
struct type_info;

// 只能用宏展开去写 丑陋也就只能这样了
#define BEGIN_CLASS_REGISTER(T)                                                                                        \
    template <>                                                                                                        \
    struct type_info<T> {                                                                                              \
        using class_type = T;
#define BEGIN_FIELD_REGISTER(...) constexpr static auto fields = std::make_tuple(__VA_ARGS__);
#define FIELD(element)                                                                                                 \
    field_traits { element, #element }
#define END_REGISTER()                                                                                                 \
    }                                                                                                                  \
    ;

#endif // STATIC_REFLECTION_TYPE_INFO_H
