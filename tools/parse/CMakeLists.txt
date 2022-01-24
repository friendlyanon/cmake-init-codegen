cmake_minimum_required(VERSION 3.14)

project(parse CXX)

add_executable(parse main.cpp)
target_compile_features(parse PRIVATE cxx_std_17)

install(TARGETS parse)
