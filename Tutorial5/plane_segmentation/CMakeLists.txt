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

#>>>>TODO: Add all the dependencies you need. Don't forget to update also the package manifest (package.xml).

)

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES plane_segmentation
  CATKIN_DEPENDS cv_bridge image_geometry image_transport roscpp rospy  std_msgs tf
  DEPENDS system_lib
)
## Specify additional locations of header files
## Your package locations should be listed before other locations

#>>>>TODO: Add the other include locations.
include_directories(
  ${catkin_INCLUDE_DIRS}
      include  
  ${PCL_INCLUDE_DIRS}
  include

)


#>>>>TODO: Create a library for the class declared in the files.

#>>>>TODO: Link the executable with the library.


## Declare a cpp executable
add_library(PlaneSegmentationH src/PlaneSegmentation.cpp)
target_link_libraries(PlaneSegmentationH ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES})
## Specify libraries to link a library or executable target against
add_executable(PlaneSegmentation_node src/PlaneSegmentation_node.cpp)
target_link_libraries(PlaneSegmentation_node ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES} PlaneSegmentationH)


