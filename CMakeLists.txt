cmake_minimum_required(VERSION 3.9)

# Define project
project(boostpythonapp VERSION 0.0.1 DESCRIPTION "Example app for embedding boost python in C++" LANGUAGES CXX)

# Define GNU standard installation directories
include(GNUInstallDirs)

include_directories(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
)

set(HEADERS
	${HEADERS}
  include/pyhelper.hpp
  include/testpyhelper.hpp
)

set(SOURCES
	${SOURCES}
    src/main.cpp
)

set(Python_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/python-3.5/python)
find_package (PythonLibs 3.5 EXACT REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

# Define Python dlls (will be copied to install folder)
set(PYTHON_DLLS ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/python-3.5/python/python35.dll)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

set(Boost_NO_SYSTEM_PATHS TRUE) 

if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/boost-1.66.0/boost_1_66_0")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
endif (Boost_NO_SYSTEM_PATHS)

find_package(Boost 1.66.0 COMPONENTS python3 numpy3) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(boostpythonapp ${SOURCES} ${HEADERS}) 
    target_link_libraries(boostpythonapp ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
endif()

# Define Boost python dlls (will be copied to install folder)
set(BOOST_DLLS 
  ${BOOST_LIBRARY_DIRS}/boost_python3-vc140-mt-x64-1_66.dll
  ${BOOST_LIBRARY_DIRS}/boost_numpy3-vc140-mt-x64-1_66.dll
)

# Define python scripts (will be copied to install folder)
set(PYTHON_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/py/TestModule.py)

# Install app in install directory
install(TARGETS ${PROJECT_NAME} DESTINATION .)
# Install python dlls in install directory
install(FILES ${PYTHON_DLLS} DESTINATION .)
# Install boost dlls in install directory
install(FILES ${BOOST_DLLS} DESTINATION .)
# Install python scripts in install directory
install(FILES ${PYTHON_SCRIPTS} DESTINATION .)