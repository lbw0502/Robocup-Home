#ifndef OBJECTRECOGNITION_H
#define OBJECTRECOGNITION_H

/*********************************************************************
* ROS INCLUDES
********************************************************************/
#include <ros/ros.h>
#include "std_msgs/Int8.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "perception_msgs/RectArray.h"
#include "perception_msgs/Rect.h"
namespace ObjectSpace
{
    class ObjectClass
    {
    public:

		pthread_mutex_t count_mutex;
        
        ObjectClass();
        ~ObjectClass();

        perception_msgs::Rect rect_msg;
        perception_msgs::RectArray rectarr_msg;
        
        void BoundtoPose(const darknet_ros_msgs::BoundingBoxes::ConstPtr &msg);

    };


}

#endif 
