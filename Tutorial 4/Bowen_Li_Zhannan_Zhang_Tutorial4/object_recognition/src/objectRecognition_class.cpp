#include<object_recognition/objectRecognition_class.h>


ObjectRecognition::ObjectRecognition(ros::NodeHandle nh) : nh_(nh), priv_nh_("~"){

    // creat subscriber to topic "/darknet_ros/bounding_boxes"
    sub_bonding_box = nh_.subscribe<darknet_ros_msgs::BoundingBoxes>("/darknet_ros/bounding_boxes", 100, &ObjectRecognition::processObject, this);

    // creat publisher to topic "rect"
    pub_rect = nh_.advertise<perception_msgs::Rect>("/rect", 10);

    ROS_INFO("Type the object name");
    std::cin >> name_;
}

ObjectRecognition::~ObjectRecognition()  {}



void ObjectRecognition::processObject(const darknet_ros_msgs::BoundingBoxes::ConstPtr &box){

    int number = box -> bounding_boxes.size();
    int idx;

    for (int i = 0; i< number; i++){
        if(box -> bounding_boxes[i].Class == name_) idx =i;
    }

    msg_.x = box -> bounding_boxes[idx].xmin;
    msg_.y = box -> bounding_boxes[idx].ymin;
    msg_.width = box->bounding_boxes[idx].xmax - box->bounding_boxes[idx].xmin;
    msg_.height = box->bounding_boxes[idx].ymax - box->bounding_boxes[idx].ymin;

    pub_rect.publish(msg_);
}