#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>

namespace navigationSpace
{
  class navigationClass
  {
  public:
    navigationClass();
    ~navigationClass();

    void rotate();

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