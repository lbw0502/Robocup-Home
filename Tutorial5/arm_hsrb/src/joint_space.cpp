#include<arm_hsrb/joint_space.h>


joint_space_Obj::joint_space_Obj(ros::NodeHandle nh, float para1_out, float para2_out, float para3_out, float para4_out, float para5_out, float para6_out) : 
nh_(nh)
{
    
    float para1 = para1_out;
    float para2 = para2_out;
    float para3 = para3_out;
    float para4 = para4_out;
    float para5 = para5_out;
    float para6 = para6_out;


  std::map<std::string, double> target_position;

  //target_position["arm_lift_joint"] = atof(argv[1]);
  //target_position["arm_flex_joint"] = atof(argv[2]);
  //target_position["arm_roll_joint"] = atof(argv[3]);
  //target_position["wrist_flex_joint"] = atof(argv[4]);
  //target_position["wrist_roll_joint"] = atof(argv[5]);
  //target_position["wrist_ft_sensor_frame_joint"] = atof(argv[6]);


  target_position["arm_lift_joint"] = para1;
  target_position["arm_flex_joint"] = para2;
  target_position["arm_roll_joint"] = para3;
  target_position["wrist_flex_joint"] = para4;
  target_position["wrist_roll_joint"] = para5;
  target_position["wrist_ft_sensor_frame_joint"] = para6;




  ros::AsyncSpinner spinner(1);
  spinner.start();
  std::vector<std::string> torso_arm_joint_names;
  //select group of joints
  moveit::planning_interface::MoveGroupInterface group_arm_torso("arm");



  //choose your preferred planner
  group_arm_torso.setPlannerId("ESTkConfigDefault");

  torso_arm_joint_names = group_arm_torso.getJoints();
  
  group_arm_torso.setStartStateToCurrentState();
  group_arm_torso.setMaxVelocityScalingFactor(1.0);

  for (unsigned int i = 0; i < torso_arm_joint_names.size(); ++i)
  {
    ROS_INFO_STREAM("the number = "<<target_position.count(torso_arm_joint_names[i]));
    ROS_INFO_STREAM("the name = "<<torso_arm_joint_names[i]);
    if ( target_position.count(torso_arm_joint_names[i]) > 0)
    {
      ROS_INFO_STREAM("\t" << torso_arm_joint_names[i] << " goal position: " << target_position[torso_arm_joint_names[i]]);
      group_arm_torso.setJointValueTarget(torso_arm_joint_names[i], target_position[torso_arm_joint_names[i]]);
      ROS_INFO("#########################");
    }
  }
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  group_arm_torso.setPlanningTime(5.0);
  bool success = bool(group_arm_torso.plan(my_plan));

  if ( !success )
    throw std::runtime_error("No plan found");

  ROS_INFO_STREAM("Plan found in " << my_plan.planning_time_ << " seconds");

  // Execute the plan
  ros::Time start = ros::Time::now();

  moveit::planning_interface::MoveItErrorCode e = group_arm_torso.move();
  if (!bool(e))
    throw std::runtime_error("Error executing plan");

  ROS_INFO_STREAM("Motion duration: " << (ros::Time::now() - start).toSec());

  spinner.stop();
}


joint_space_Obj::~joint_space_Obj() {}