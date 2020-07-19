/*************************************************************************
STD INCLUDE
*************************************************************************/
#include <iostream>
#include <fstream>
#include <pthread.h>
/*************************************************************************
ROS INCLUDE
*************************************************************************/
#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Char.h>
/*************************************************************************
MSG INCLUDE
*************************************************************************/
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <tf/transform_listener.h>
#include <perception_msgs/Rect.h>
#include <perception_msgs/RectArray.h>
/*************************************************************************
SENSOR INCLUDE
*************************************************************************/
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
/*************************************************************************
OPENCV2 INCLUDE
*************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
/*************************************************************************
PCL INCLUDE
*************************************************************************/
#include <pcl_ros/point_cloud.h> // enable pcl publishing
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>
/*************************************************************************
Private variable defination
*************************************************************************/
std_msgs::Header cloudheader;

using namespace std;
using namespace cv;


    class From2Dto3D
    {
    private:  
      //! The node handle
      ros::NodeHandle nh_;
      //! Node handle in the private namespace
      ros::NodeHandle priv_nh_;

      //! Define publishers and subscribers
   
      ros::Subscriber obj_center_sub;
      ros::Subscriber pc_sub;
      ros::Publisher obj_3d_pub;

      int x_2d,y_2d;
      geometry_msgs::PointStamped coordinate_3D_base;
      geometry_msgs::PointStamped coordinate_3D;
      pcl::PointCloud<pcl::PointXYZRGB> cloud;
      // pcl::PointCloud<pcl::PointXYZ> cloud;
      //! Define the pointcloud structure and the bounding box local copy


      //! A tf transform listener if needed
      //ros::Duration five_seconds;
      //ros::Duration five_seconds(5.0);
      //tf::TransformListener listener_ToBase(max_cache,true);
      tf::TransformListener listener_ToBase;
      //static tf::TransformBroadcaster centerpt_br1,centerpt_br2;
      //tf::Transform centerpt_transform1,centerpt_transform2;
      //tf::Quaternion centerpt_qtf1,centerpt_qtf2;
      
      std::string myString;
      std::vector<perception_msgs::Rect> msgs_exe3;     // get information from exercise 3
      //------------------ Callbacks -------------------

      //! Process clusters
      void processCloud(const sensor_msgs::PointCloud2ConstPtr& pc);
      //! Process bounding boxes
      void processRect(const perception_msgs::RectArrayConstPtr & r);

    public:
      From2Dto3D(ros::NodeHandle nh);

      ~From2Dto3D();

    };


