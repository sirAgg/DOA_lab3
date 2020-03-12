cmake_minimum_required( VERSION 3.0 )

project (lab3)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-g")
    message("hi")
endif()

add_executable(lab3
  main.cpp
)
