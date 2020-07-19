cmake_minimum_required(VERSION 2.8.3)
project(from2dto3d)

# Catkin
find_package(catkin REQUIRED COMPONENTS
  message_generation
  rospy
  std_msgs
  sensor_msgs
  message_filters
  cv_bridge
  tf
  image_geometry
  darknet_ros_msgs
  perception_msgs
  message_generation
)

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

add_message_files(
  FILES
  Rect.msg
  RectArray.msg
)

generate_messages(
  DEPENDENCIES
  darknet_ros_msgs   sensor_msgs   std_msgs 
)

catkin_package(CATKIN_DEPENDS message_runtime)


include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
)


#>>>>TODO: Create a library for the class declared in the files.

#>>>>TODO: Link the executable with the library.

add_library(from2Dto3DH src/from2Dto3D.cpp)
target_link_libraries(from2Dto3DH ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES})
set_target_properties(from2Dto3DH  PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_dependencies(from2Dto3DH ${catkin_EXPORTED_TARGETS}  ${${PROJECT_NAME}_EXPORTED_TARGETS})

add_executable(from2dto3d_node src/from2Dto3D_node.cpp)
target_link_libraries(from2dto3d_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${PCL_LIBRARIES}
  from2Dto3DH 
)
#add_dependencies(from2Dto3D_node ${catkin_EXPORTED_TARGETS}  ${${PROJECT_NAME}_EXPORTED_TARGETS})

install(TARGETS from2dto3d_node
##   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
##  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

