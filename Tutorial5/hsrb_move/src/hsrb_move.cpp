#include<hsrb_move/hsrb_move.h>

hsrb_move_Obj::hsrb_move_Obj(ros::NodeHandle nh):n(nh)
{

    pose_sub = n.subscribe("/segmentation/point3D",100,&hsrb_move_Obj::processtargetpose, this); 


}

hsrb_move_Obj::~hsrb_move_Obj() {}




void hsrb_move_Obj::processtargetpose(const geometry_msgs::PointStampedConstPtr& msg)
{
  if (receiveflag == false && msg->point.z > 0){
      ROS_INFO("Target received");
      receiveflag = true;
      Displacement = msg->point;
  }
  
}



void hsrb_move_Obj::moving(){
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base/move", true);
  

  // pose_sub = n.subscribe("/segmentation/point3D",100,&processtargetpose);  


    while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
    ROS_INFO("??????????");
    }



  move_base_msgs::MoveBaseGoal goal;
  move_base_msgs::MoveBaseGoal base_goal;
  goal.target_pose.header.frame_id = "map";
  base_goal.target_pose.header.frame_id = "base_link";
  // start the navigation
  ROS_INFO("start the navigation");

    ROS_INFO("Moving to table1");
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = 2.563;
    goal.target_pose.pose.position.y = 0.901;
    goal.target_pose.pose.position.z = 0;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0;
    goal.target_pose.pose.orientation.w = 1.000;
    ac.sendGoal(goal);
    ac.waitForResult();
    ROS_INFO("Moving to table1 is done!!!!");
    
    
    
    ros::Duration(1.).sleep();
    ros::spinOnce();

    ROS_INFO("Raise arm");
    system("rosrun arm_hsrb joints 0.3 -1.0 0.0 -0.5236 0 0");
    ROS_INFO("Looking for target");
    
    ros::Duration(2.).sleep();
    ros::spinOnce();
    ROS_INFO("Moving to target");
    // Move to the position directly facing the target 
    base_goal.target_pose.header.stamp = ros::Time::now();
    base_goal.target_pose.pose.position.x = 0.0;
    base_goal.target_pose.pose.position.y = -Displacement.y+0,05;
    base_goal.target_pose.pose.position.z = 0.0;
    base_goal.target_pose.pose.orientation.x = 0.0;
    base_goal.target_pose.pose.orientation.y = 0.0;
    base_goal.target_pose.pose.orientation.z = 0.0;
    base_goal.target_pose.pose.orientation.w = 1.000;
    ac.sendGoal(base_goal);
    ac.waitForResult();
    ros::Duration(1.).sleep();

    ROS_INFO("Fetching target");
    // Move to the position to grab target
    base_goal.target_pose.header.stamp = ros::Time::now();
    base_goal.target_pose.pose.position.x = Displacement.z;
    base_goal.target_pose.pose.position.y = 0;
    base_goal.target_pose.pose.position.z = 0.0;
    base_goal.target_pose.pose.orientation.x = 0.0;
    base_goal.target_pose.pose.orientation.y = 0.0;
    base_goal.target_pose.pose.orientation.z = 0.0;
    base_goal.target_pose.pose.orientation.w = 1.000;
    ac.sendGoal(base_goal);
    ac.waitForResult();
    ROS_INFO("Moving to target is done!!!!");


    // grab the target and come back to the 'go' position
    system("rosrun arm_hsrb grab.py");
    ROS_INFO("Grabed and move back!!!!");



    ROS_INFO("Moving to table2");
    // goal.target_pose.header.stamp = ros::Time::now();
    // goal.target_pose.pose.position.x = 2.511;
    // goal.target_pose.pose.position.y = 2.203;
    // goal.target_pose.pose.position.z = 0;
    // goal.target_pose.pose.orientation.x = 0.0;
    // goal.target_pose.pose.orientation.y = 0.0;
    // goal.target_pose.pose.orientation.z = 0.0;
    // goal.target_pose.pose.orientation.w = 1.000;
    // ac.sendGoal(goal);
    // ac.waitForResult();

    // Move to the second navigate point
    ros::spinOnce();
    base_goal.target_pose.header.stamp = ros::Time::now();
    base_goal.target_pose.pose.position.x = 0;
    base_goal.target_pose.pose.position.y = 1.5;
    base_goal.target_pose.pose.position.z = 0;
    base_goal.target_pose.pose.orientation.x = 0.0;
    base_goal.target_pose.pose.orientation.y = 0.0;
    base_goal.target_pose.pose.orientation.z = 0.0;
    base_goal.target_pose.pose.orientation.w = 1.000;
    ac.sendGoal(base_goal);
    ac.waitForResult();
    ROS_INFO("Moving to table2 is done!!!!");
    
    // system("chmod u+x ~/ros/workspace/new_T5/src/arm_hsrb/lib/release.py");
    // system("source ~/ros/workspace/new_T5/devel/setup.bash");
    system("rosrun arm_hsrb release.py");

}

