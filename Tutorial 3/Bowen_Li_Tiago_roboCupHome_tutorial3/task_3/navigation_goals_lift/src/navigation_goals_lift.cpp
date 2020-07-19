#include <navigation_goals_lift/navigationClass.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){

  ros::init(argc, argv, "tiago_navigation_lift");
  ros::NodeHandle n;

  ros::Rate r(60);

  ros::ServiceClient client_localization = n.serviceClient<std_srvs::Empty>("/global_localization");
  ros::ServiceClient client_clean = n.serviceClient<std_srvs::Empty>("/move_base/clear_costmaps");



  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // create an instance navigationF
  navigationSpace::navigationClass naviagtionF;


  // self-localize through rotating
  std_srvs::Empty empty_srv;
  client_localization.call(empty_srv);
  naviagtionF.rotate();


  //clean the map
  client_clean.call(empty_srv);

  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "map";

  

  ROS_INFO("Moving to C");
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = -1.15;
  goal.target_pose.pose.position.y = -11.8;
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.707;
  goal.target_pose.pose.orientation.w = 0.707;
  ac.sendGoal(goal);
  ac.waitForResult();



  //start to lift the table
  ROS_INFO("start to lift the table");
  
  std::map<std::string, double> target_position;
  target_position["torso_lift_joint"] = 0;
  target_position["arm_1_joint"] = 1.5;
  target_position["arm_2_joint"] = -0.5;
  target_position["arm_3_joint"] = -1.4;
  target_position["arm_4_joint"] = 0.2;
  target_position["arm_5_joint"] = 0;
  target_position["arm_6_joint"] = -0.2;
  target_position["arm_7_joint"] = 0;
  naviagtionF.armMove(target_position);



  target_position["arm_2_joint"] = 0;
  naviagtionF.armMove(target_position);

  target_position["torso_lift_joint"] = 0.5;
  naviagtionF.armMove(target_position);

  target_position["torso_lift_joint"] = 0;
  naviagtionF.armMove(target_position);

  target_position["arm_2_joint"] = -0.5;
  naviagtionF.armMove(target_position);

  target_position["torso_lift_joint"] = 0;
  target_position["arm_1_joint"] = 0.23;
  target_position["arm_2_joint"] = -1.34;
  target_position["arm_3_joint"] = -0.2;
  target_position["arm_4_joint"] = 1.94;
  target_position["arm_5_joint"] = -1.57;
  target_position["arm_6_joint"] = 1.37;
  target_position["arm_7_joint"] = 0;
  naviagtionF.armMove(target_position);





  // start the navigation
  ROS_INFO("start the navigation");

  while(ros::ok){

    ROS_INFO("Moving to A");
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = -2.99147677422;
    goal.target_pose.pose.position.y = -2.36532974243;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0112960987154;
    goal.target_pose.pose.orientation.w = 0.999936197041;
    ac.sendGoal(goal);
    ac.waitForResult();



    ROS_INFO("Moving to B");
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = -3.80597049713;
    goal.target_pose.pose.position.y = -6.47922681808;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0130994101805;
    goal.target_pose.pose.orientation.w = 0.999914199046;
    ac.sendGoal(goal);
    ac.waitForResult();



    ROS_INFO("Moving to C");
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = -1.28180742264;
    goal.target_pose.pose.position.y = -11.9030261993;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.701655241864;
    goal.target_pose.pose.orientation.w = 0.702516611431;
    ac.sendGoal(goal);
    ac.waitForResult();

  }

  return 0;


}