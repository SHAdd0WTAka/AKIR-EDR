cmake_minimum_required(VERSION 3.10)
project(AKIR-EDR-Agent)

set(CMAKE_CXX_STANDARD 17)

add_executable(EDRAgent Agent/EDRAgent.cpp Agent/EDRAgent.h)
