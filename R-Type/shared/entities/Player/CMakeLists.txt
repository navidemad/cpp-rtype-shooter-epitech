cmake_minimum_required (VERSION 2.6)

project (${PRJ} CXX)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(--std=c++11 SUPPORTS_STD_CXX11)
    check_cxx_compiler_flag(--std=c++0x SUPPORTS_STD_CXX01)
    if(SUPPORTS_STD_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c++11")
    elseif(SUPPORTS_STD_CXX01)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c++0x")
    else()
        message(ERROR "Compiler does not support --std=c++11 or --std=c++0x.")
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(PRJ Player)
set(SRC Player.cpp Player.hpp)
set(EXECUTABLE_OUTPUT_PATH ..)

include_directories(../../includes/IResource.hpp)

OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)
SET (BUILD_SHARED_LIBS TRUE)

ADD_LIBRARY(${PRJ} SHARED ${SRC})

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif(UNIX)
