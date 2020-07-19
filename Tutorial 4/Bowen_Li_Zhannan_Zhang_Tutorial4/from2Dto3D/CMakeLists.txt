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
  perception_msgs

#>>>>TODO: Add all the dependencies you need. Don't forget to update also the package manifest (package.xml).

)

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

catkin_package(CATKIN_DEPENDS message_runtime)


include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}   #!!!!!!! necessary when include own head file!!!!!!!!!!!!
)


#>>>>TODO: Create a library for the class declared in the files.
add_library(from2Dto3D_lib src/from2Dto3D_class.cpp)

#>>>>TODO: Link the executable with the library.
target_link_libraries(from2Dto3D_lib ${roscpp_LIBRARIES} ${catkin_LIBRARIES})
set_target_properties(from2Dto3D_lib  PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_dependencies(from2Dto3D_lib ${catkin_EXPORTED_TARGETS}  ${${PROJECT_NAME}_EXPORTED_TARGETS})



add_executable(from2Dto3D_node src/from2Dto3D_node.cpp)
target_link_libraries(from2Dto3D_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${PCL_LIBRARIES}
  from2Dto3D_lib
)
add_dependencies(from2Dto3D_node ${catkin_EXPORTED_TARGETS}  ${${PROJECT_NAME}_EXPORTED_TARGETS})



install(TARGETS from2Dto3D_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

