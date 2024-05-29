cmake_minimum_required(VERSION 3.28)

project(
    DataStructures              # Your project name
    VERSION 1.0.0                 # Example version
    DESCRIPTION "Data Structures library"
    LANGUAGES C CXX               # For C++ (or C for C projects)
)


set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_EXECUTABLE App)

option(ENABLE_TESTING "Enable Testing" ON)
option(ENABLE_WARNINGS "Enable Warnings" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable warnings as errors" ON)
option(ENABLE_SANATIZER_ADDRESS "Enable Address sanitizer" ON)
option(GENERATE_DOCS "Generate documentation" ON)
option(ENABLE_LTO "Enable link time optimization" ON)

if(GENERATE_DOCS)
    include(${CMAKE_SOURCE_DIR}/cmake/Docs.cmake)
endif()



add_executable(DataStructures
        App.cpp)
