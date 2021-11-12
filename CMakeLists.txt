cmake_minimum_required(VERSION 3.10)

project(RayTracer)

#--- Load the common configuration
include(common/config.cmake)

#--- Load third party packages
include(common/Eigen.cmake)
include(common/OpenCV.cmake)

include_directories(raytrace)


#--- Subprojects
add_subdirectory(raytrace)


#--- C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)









