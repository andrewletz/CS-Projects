cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(project1D)
SET(VTK_DIR ~/VTK-8.1.2)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(project1D project1D)

if(VTK_LIBRARIES)
  target_link_libraries(project1D ${VTK_LIBRARIES})
else()
  target_link_libraries(project1D vtkHybrid)
endif()

