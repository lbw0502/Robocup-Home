#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <string>
#include <vector>
#include <map>

namespace navigationSpace
{
  class navigationClass
  {
  public:
    navigationClass();
    ~navigationClass();

    void rotate();
    void armMove(std::map<std::string, double> target_position);

  };

}



navigationSpace::navigationClass::navigationClass(){

}


navigationSpace::navigationClass::~navigationClass(){

}


void navigationSpace::navigationClass::rotate(){
    ros::NodeHandle n1;
    ros::Rate r(60);
    ros::Publisher pub_rotate = n1.advertise<geometry_msgs::Twist>("/key_vel",100);

    geometry_msgs::Twist twist_msg;
    twist_msg.angular.z = -1.2;

    double t0 = ros::Time::now().toSec();
    double t1;
    while(t1 < t0 + 16){
    pub_rotate.publish(twist_msg);
    t1 = ros::Time::now().toSec();
    }

    twist_msg.angular.z = 0;
    pub_rotate.publish(twist_msg);

}


void navigationSpace::navigationClass::armMove(std::map<std::string, double> target_position){

  ros::AsyncSpinner spinner(1);
  spinner.start();

  std::vector<std::string> torso_arm_joint_names;
  //select group of joints
  moveit::planning_interface::MoveGroupInterface group_arm_torso("arm_torso");
  //choose your preferred planner
  group_arm_torso.setPlannerId("SBLkConfigDefault");

  torso_arm_joint_names = group_arm_torso.getJoints();

  group_arm_torso.setStartStateToCurrentState();
  group_arm_torso.setMaxVelocityScalingFactor(1.0);

  for (unsigned int i = 0; i < torso_arm_joint_names.size(); ++i)
    if ( target_position.count(torso_arm_joint_names[i]) > 0 )
    {
      ROS_INFO_STREAM("\t" << torso_arm_joint_names[i] << " goal position: " << target_position[torso_arm_joint_names[i]]);
      group_arm_torso.setJointValueTarget(torso_arm_joint_names[i], target_position[torso_arm_joint_names[i]]);
    }

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  group_arm_torso.setPlanningTime(5.0);
  group_arm_torso.plan(my_plan);

  ROS_INFO_STREAM("Plan found in " << my_plan.planning_time_ << " seconds");

  // Execute the plan
  ros::Time start = ros::Time::now();

  group_arm_torso.move();

  ROS_INFO_STREAM("Motion duration: " << (ros::Time::now() - start).toSec());

  spinner.stop();

}
