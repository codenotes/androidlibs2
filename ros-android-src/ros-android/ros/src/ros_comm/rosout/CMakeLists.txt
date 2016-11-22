cmake_minimum_required(VERSION 2.8.3)
project(rosout)
find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(rosout rosout.cpp)
target_link_libraries(rosout ${catkin_LIBRARIES})

if (CYGWIN)
install(TARGETS rosout
  RUNTIME DESTINATION ${CATKIN_GLOBAL_LIB_DESTINATION}/rosout)
else()
install(TARGETS rosout
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endif()
