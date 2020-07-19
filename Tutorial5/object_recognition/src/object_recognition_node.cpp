#include <ros/ros.h>
#include<object_recognition/ObjectRecognition.h>

int main( int argc, char** argv )
{
    ros::init(argc, argv, "object_recognition",ros::init_options::AnonymousName);
    ros::NodeHandle n;
    ros::Rate r(60);
    ObjectSpace::ObjectClass Obj;
    //Publisher & Subscriber
    ros::Subscriber sub=n.subscribe("/darknet_ros/bounding_boxes",100,
    &ObjectSpace::ObjectClass::BoundtoPose,&Obj);
    ros::Publisher pub=n.advertise<perception_msgs::RectArray>("/Object/perception_msgs",100);    
    while(ros::ok()){
    ROS_INFO("Publishing rect to 2Dto3D node");
    pub.publish(Obj.rectarr_msg);
    ros::spinOnce();
    r.sleep();

    }
    return 0;
    
}