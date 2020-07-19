#include<object_recognition/objectRecognition_class.h>



int main(int argc, char** argv)
{
    ros::init(argc, argv, "object_recognition_node");
    ros::NodeHandle nh;
    ObjectRecognition node(nh);
    ros::spin();
    return 0;
}