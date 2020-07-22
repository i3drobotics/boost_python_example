cmake_minimum_required(VERSION 3.9)

# Define project
project(boostpythonapp VERSION 0.0.1 DESCRIPTION "Example app for embedding boost python in C++" LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

set(Boost_NO_SYSTEM_PATHS TRUE) 

if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/boost_1_66_0")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)

find_package(Boost 1.66.0 COMPONENTS python) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(boostpythonapp src/main.cpp) 
    target_link_libraries(boostpythonapp ${Boost_LIBRARIES})
endif()