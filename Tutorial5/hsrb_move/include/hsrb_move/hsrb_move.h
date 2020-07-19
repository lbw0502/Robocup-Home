#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <hsrb_move/target.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;



class hsrb_move_Obj{

public:

    ros::NodeHandle n;
    ros::Subscriber pose_sub;

    hsrb_move::target Target_grasp;
    geometry_msgs::Point Displacement;
    bool receiveflag = false;




    void processtargetpose(const geometry_msgs::PointStampedConstPtr& msg);
    void moving();


    hsrb_move_Obj(ros::NodeHandle nh);
    ~hsrb_move_Obj();


};