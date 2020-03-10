cmake_minimum_required( VERSION 3.0 )

project (lab3)

if(LINUX)
    set(CMAKE_CXX_FLAGS "-g")
endif()

add_executable(lab3
  main.cpp
)
