cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 14)
add_definitions(-std=c++11)

project(rc_indoor)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

file(GLOB libraryHeaders 
        "include/rc_indoor/*.h"
)
FILE(GLOB SRC_FILES 
        "src/*.cpp"
)

add_executable(rc_indoor ${SRC_FILES} ${libraryHeaders})
target_link_libraries(rc_indoor ${catkin_LIBRARIES})

