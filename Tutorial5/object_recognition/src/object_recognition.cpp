#include <ros/ros.h>
#include<object_recognition/ObjectRecognition.h>

namespace ObjectSpace {

ObjectClass::ObjectClass()
{
    count_mutex = PTHREAD_MUTEX_INITIALIZER;
}
ObjectClass::~ObjectClass()
{

}

void ObjectClass::BoundtoPose(const darknet_ros_msgs::BoundingBoxes::ConstPtr &msg)
{
    pthread_mutex_lock( &this->count_mutex );
    
    for(int i = 0;i < msg->bounding_boxes.size();i++){
        rect_msg.x = (msg->bounding_boxes[i].xmax + msg->bounding_boxes[i].xmin)/2;
        rect_msg.y = (msg->bounding_boxes[i].ymax + msg->bounding_boxes[i].ymin)/2;
        rect_msg.height = msg->bounding_boxes[i].ymax - msg->bounding_boxes[i].ymin;
        rect_msg.width = msg->bounding_boxes[i].xmax - msg->bounding_boxes[i].xmin;
        rect_msg.header.frame_id = msg->bounding_boxes[i].Class;
        rectarr_msg.rect_array.push_back(rect_msg);
    } 
    
    pthread_mutex_unlock( &this->count_mutex );
}
}