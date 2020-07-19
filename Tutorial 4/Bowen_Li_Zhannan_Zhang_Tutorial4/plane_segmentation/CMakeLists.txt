cmake_minimum_required(VERSION 2.8.3)
project(plane_segmentation)


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS  
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  tf
  image_geometry
  pcl_conversions
  pcl_ros

#>>>>TODO: Add all the dependencies you need. Don't forget to update also the package manifest (package.xml).

)

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

catkin_package()
## Specify additional locations of header files
## Your package locations should be listed before other locations

#>>>>TODO: Add the other include locations.
include_directories(
  include
  ${catkin_INCLUDE_DIRS}  
  ${PCL_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}   #!!!!!!! necessary when include own head file!!!!!!!!!!!!
  ${roscpp_INCLUDE_DIRS}
)
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


#>>>>TODO: Create a library for the class declared in the files.
add_library(plane_segmentation_lib src/PlaneSegmentation_class.cpp)

#>>>>TODO: Link the executable with the library.
target_link_libraries(plane_segmentation_lib ${roscpp_LIBRARIES} ${catkin_LIBRARIES})


set_target_properties(plane_segmentation_lib  PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_dependencies(plane_segmentation_lib ${catkin_EXPORTED_TARGETS}  ${${PROJECT_NAME}_EXPORTED_TARGETS})



## Declare a cpp executable
add_executable(plane_segmentation_node src/PlaneSegmentation_node.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(plane_segmentation_node ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES} plane_segmentation_lib)
add_dependencies(plane_segmentation_node ${catkin_EXPORTED_TARGETS}  ${${PROJECT_NAME}_EXPORTED_TARGETS})


