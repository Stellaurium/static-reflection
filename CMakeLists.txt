# 记得一定要去设置里 更改cmake的参数 明确指定 conan_toolchain.cmake

cmake_minimum_required(VERSION 3.25)
project(static_reflection)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)


# my common header
set(PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
# executable output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)


file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)


find_package(fmt REQUIRED)
find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)



include_directories(${COMMON_INCLUDE_DIRS} ${PROJECT_INCLUDE_DIRS})
add_executable(static_reflection ${source_files})


target_link_libraries(static_reflection PRIVATE fmt::fmt)
target_link_libraries(static_reflection PRIVATE Catch2::Catch2WithMain)
target_link_libraries(static_reflection PRIVATE spdlog::spdlog)



