#include<ros/ros.h>
#include <string>
#include <iostream>
#include <perception_msgs/Rect.h>
#include <darknet_ros_msgs/BoundingBoxes.h>



class ObjectRecognition{

private:

    //! The node handle
    ros::NodeHandle nh_;
    //! Node handle in the private namespace
    ros::NodeHandle priv_nh_;

    //! subscribe to bonding box
    ros::Subscriber sub_bonding_box;
    //! publish to rect
    ros::Publisher pub_rect;


    std::string name_;
    perception_msgs::Rect msg_;

    // callback function of topic-subsription "/darknet_ros/bounding_boxes"
    void processObject(const darknet_ros_msgs::BoundingBoxes::ConstPtr &box);

public:
    ObjectRecognition(ros::NodeHandle nh);

    ~ObjectRecognition();

};
