cmake_minimum_required(VERSION 3.12...3.16)

#------------------------------------------------------------------------------
# 3rd party library support
#------------------------------------------------------------------------------
set(ENABLE_RAPID_YAML OFF CACHE BOOL "Adds YAML to the Project" FORCE)
set(ENABLE_ENET       OFF CACHE BOOL "Adds Network to the Project" FORCE)
set(ENABLE_SOUND      OFF CACHE BOOL "Adds SoLoud Audio" FORCE)

#------------------------------------------------------------------------------
# Project settings
#------------------------------------------------------------------------------
project(HelloASGE
        VERSION 1.0
        DESCRIPTION "A sample hello world ASGE application"
        LANGUAGES CXX)

message(STATUS "")
message(STATUS "##### ${PROJECT_NAME} Project configuration #####")
message(STATUS "")

#------------------------------------------------------------------------------
# General settings
#------------------------------------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/${PROJECT_NAME}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/${PROJECT_NAME}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/${PROJECT_NAME}/bin")

#------------------------------------------------------------------------------
# Static and shared build configurations
#------------------------------------------------------------------------------
option(STATIC_APP "Build a static application" ON)
message(STATUS " ")

if( STATIC_APP )
    message(STATUS "APPLICATION STATIC BUILD: \t YES")
    message(STATUS "APPLICATION SHARED BUILD: \t NO")
    set(BUILD_SHARED_LIBS false)
else()
    message(STATUS "APPLICATION STATIC BUILD: \t NO")
    message(STATUS "APPLICATION SHARED BUILD: \t YES")
    set(BUILD_SHARED_LIBS true)
endif()

#------------------------------------------------------------------------------
# Add the game library and executable projects
#------------------------------------------------------------------------------
add_subdirectory(cmake)
add_subdirectory(src)