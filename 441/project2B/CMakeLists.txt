cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(project2B)
SET(VTK_DIR ~/VTK-6.3.0)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(project2B project2B.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(project2B ${VTK_LIBRARIES})
else()
  target_link_libraries(project2B vtkHybrid)
endif()
