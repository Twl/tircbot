cmake_minimum_required(VERSION 2.8)

set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project (tirc)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

include (CheckFunctionExists)
include (cmake/CheckCXX11Features.cmake)
include (cmake/TwlMacros.cmake)

set (SOURCES_DIR "${PROJECT_SOURCE_DIR}/src")
set (DEPENDENCIES_DIR "${PROJECT_SOURCE_DIR}/dependencies")

LIST_LENGTH(cxx11_length ${CXX11_FEATURE_LIST})

if(${cxx11_length} GREATER 12 OR ${cxx11_length} EQUAL 12)
    message(STATUS "Sufficient C++11 support found.")
else()
    message(FATAL_ERROR "Insufficient C++11 support on your machine. Install GCC >= 4.7 or Clang >= 3.2")
endif()

if (NOT EXISTS "${DEPENDENCIES_DIR}/tirc/CMakeLists.txt")
    message(FATAL_ERROR "You need the TIRC library in the dependencies folder in order to build. Run 'git submodule init && git submodule update'")
endif()

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package (Boost 1.50.0 COMPONENTS system regex)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(tirclib_REQUIRED_LIBRARIES ${Boost_LIBRARIES})
elseif()
    message(FATAL_ERROR "You cannot build without Boost >= 1.50.0.")
endif()

configure_file ("${DEPENDENCIES_DIR}/tirc/src/tirc_config.h.in" "${PROJECT_BINARY_DIR}/tirc_config.h")

add_definitions ("-DHAVE_CONFIG")
add_definitions ("-O2 -march=native -std=gnu++11 -fabi-version=6 -Wall")


include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${DEPENDENCIES_DIR}/tirc/src")
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory("${DEPENDENCIES_DIR}/tirc/src")
add_subdirectory ("src")
