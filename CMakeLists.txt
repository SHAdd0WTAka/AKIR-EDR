cmake_minimum_required(VERSION 3.20)
project(AKIR LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Hardening Flags
if(MSVC)
    add_compile_options(/guard:cf /ZH:SHA_256 /GS /W4 /WX /utf-8)
    add_link_options(/HIGHENTROPYVA /DYNAMICBASE /NXCOMPAT /GUARD:CF /CETCOMPAT)
endif()

# Include Directories für das gesamte Projekt
include_directories(src/agent)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Agent Executable
add_executable(AKIR_Agent 
    src/agent/main.cpp 
    src/agent/IntegrityGuard.cpp
    src/agent/AdminAuth.cpp
)

target_link_libraries(AKIR_Agent PRIVATE unofficial::sqlite3::sqlite3 OpenSSL::SSL nlohmann_json::nlohmann_json)

# Tests Configuration
enable_testing()
find_package(GTest CONFIG REQUIRED)

# Test Executable
add_executable(AKIR_Tests 
    tests/test_auth_logic.cpp 
    src/agent/AdminAuth.cpp
)

target_link_libraries(AKIR_Tests PRIVATE GTest::gtest GTest::gtest_main OpenSSL::SSL nlohmann_json::nlohmann_json)

# Test Discovery (für ctest)
include(GoogleTest)
gtest_discover_tests(AKIR_Tests)
