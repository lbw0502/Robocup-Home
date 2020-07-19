#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Char.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <tf/transform_listener.h>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


// PCL specific includes
#include <pcl_ros/point_cloud.h> // enable pcl publishing
#include <sensor_msgs/PointCloud2.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>

//#include <image_geometry/pinhole_camera_model.h>

#include <perception_msgs/Rect.h>


class From2Dto3D
{

    private:
      // The node handle
      ros::NodeHandle nh_;
      // Node handle in the private namespace
      ros::NodeHandle priv_nh_;

      //#>>>>TODO: Define publishers and subscribers
      ros::Publisher pub_point3D;
      ros::Subscriber sub_hsrbPoint;
      ros::Subscriber sub_rect;


      //#>>>>TODO: Define the pointcloud structure and the bounding box local copy
      pcl::PointCloud< pcl::PointXYZ > pc_local;
      geometry_msgs::Point point3D;


      // A tf transform listener if needed
      tf::TransformListener listener_;


      //------------------ Callbacks -------------------

      // Process clusters
      void processCloud(const sensor_msgs::PointCloud2ConstPtr& pc);
      // Process bounding boxes
      void processRect(const perception_msgs::RectConstPtr & r);


    public:
      // Subscribes to and advertises topics
      From2Dto3D(ros::NodeHandle nh);

      ~From2Dto3D();
};


