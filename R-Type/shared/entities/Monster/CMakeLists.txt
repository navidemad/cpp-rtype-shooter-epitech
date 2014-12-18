cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
set(PRJ Monster)
set(SRC Monster.cpp Monster.hpp)
set(EXECUTABLE_OUTPUT_PATH ..)

include_directories(../../includes/IResource.hpp)

OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)
SET (BUILD_SHARED_LIBS TRUE)

project (${PRJ})
ADD_LIBRARY(${PRJ} SHARED ${SRC})

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif(UNIX)
