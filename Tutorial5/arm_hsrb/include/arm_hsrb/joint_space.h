// ROS headers
#include <ros/ros.h>

// MoveIt! headers
#include <moveit/move_group_interface/move_group_interface.h>

// Std C++ headers
#include <string>
#include <vector>
#include <map>

class joint_space_Obj{


public:
    ros::NodeHandle nh_;

  
    joint_space_Obj(ros::NodeHandle nh, float para1_out, float para2_out, float para3_out, float para4_out, float para5_out, float para6_out);
    
    ~joint_space_Obj();



};