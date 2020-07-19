cmake_minimum_required(VERSION 2.8.3)
project(arm_hsrb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  moveit_ros_planning_interface
  roscpp
  rospy
  geometry_msgs
)

catkin_package(
)

add_service_files(
  FILES
  grasp.srv
)



catkin_package(
  INCLUDE_DIRS include
  LIBRARIES arm_hsrb
  DEPENDS system_lib
)




include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}   #!!!!!!! necessary when include own head file!!!!!!!!!!!!
  ${roscpp_INCLUDE_DIRS}

)



add_library(joints_lib src/joint_space.cpp)
target_link_libraries(joints_lib ${roscpp_LIBRARIES} ${catkin_LIBRARIES})

set_target_properties(joints_lib  PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_dependencies(joints_lib ${catkin_EXPORTED_TARGETS}  ${${PROJECT_NAME}_EXPORTED_TARGETS})



add_executable(joints src/joint_space_node.cpp)
add_dependencies(joints ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(joints
   ${catkin_LIBRARIES}
   joints_lib
 )


install(TARGETS joints 
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )

install(DIRECTORY launch config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
