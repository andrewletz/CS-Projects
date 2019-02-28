cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(project2A)
SET(VTK_DIR ~/VTK-6.3.0)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(project2A project2A.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(project2A ${VTK_LIBRARIES})
else()
  target_link_libraries(project2A vtkHybrid)
endif()
