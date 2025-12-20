cmake_minimum_required(VERSION 3.20)
project(AKIR LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

# Hardening Flags
if(MSVC)
    add_compile_options(/guard:cf /ZH:SHA_256 /CETCOMPAT /GS /W4 /WX)
    add_link_options(/HIGHENTROPYVA /DYNAMICBASE /NXCOMPAT /GUARD:CF)
endif()

find_package(sqlite3 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Agent Executable
add_executable(AKIR_Agent 
    src/agent/main.cpp 
    src/agent/IntegrityGuard.cpp
    src/agent/AdminAuth.cpp
)

target_link_libraries(AKIR_Agent PRIVATE sqlite3 OpenSSL::SSL nlohmann_json::nlohmann_json)

# Tests
enable_testing()
find_package(GTest CONFIG REQUIRED)
add_executable(AKIR_Tests tests/test_auth_logic.cpp src/agent/AdminAuth.cpp)
target_link_libraries(AKIR_Tests PRIVATE GTest::gtest GTest::gtest_main OpenSSL::SSL)
add_test(NAME AKIR_Tests COMMAND AKIR_Tests)

# Subdirectories for Kernel (if using WDK with CMake, typically handled separately or with custom toolchains)
# add_subdirectory(src/kernel)