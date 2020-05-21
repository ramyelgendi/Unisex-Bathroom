cmake_minimum_required(VERSION 3.10)
project(OS C)

set(CMAKE_C_STANDARD 11)


add_executable(OS main.c)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(OS Threads::Threads)