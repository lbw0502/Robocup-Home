/*************************************************************************
ROS INCLUDE
*************************************************************************/
#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Char.h>
#include <geometry_msgs/PoseStamped.h>
/*************************************************************************
MSG INCLUDE
*************************************************************************/
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <tf/transform_listener.h>
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
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
/*************************************************************************
IMG INCLUDE
*************************************************************************/
#include <image_geometry/pinhole_camera_model.h>

using namespace std;
using namespace cv;

    class PlaneSegmentation
    {
    private:  
    ros::NodeHandle nh_;      //! The node handle
    ros::NodeHandle priv_nh_; //! Node handle in the private namespace
    
    ros::Subscriber sub;      

    ros::Publisher pub_plane_pc_;
    ros::Publisher pub_clusters_pc_;
   
    // Internal data
    pcl::PointCloud<pcl::PointXYZ> curr_table_pc;
    pcl::PointCloud<pcl::PointXYZ> curr_clusters_pc;
    
    sensor_msgs::PointCloud2 test;      //todo  

    //------------------ Callbacks -------------------

    // Callback for service calls
	

    //! Callback for subscribers
    //! Complete processing of new point cloud
    void processCloud(const sensor_msgs::PointCloud2ConstPtr &var); 
    public:
        //! Subscribes to and advertises topics
        PlaneSegmentation(ros::NodeHandle nh) : nh_(nh), priv_nh_("~") //,
        //sub(nh, "topic", 5) // constructor initialization form for the subscriber if needed
        {


        pub_plane_pc_ = nh_.advertise< pcl::PointCloud<pcl::PointXYZ> >("/segmentation/plane_points", 10);
        pub_clusters_pc_ = nh_.advertise< pcl::PointCloud<pcl::PointXYZ> >("/segmentation/clusters_points", 10);
        
        sub = nh_.subscribe("/hsrb/head_rgbd_sensor/depth_registered/rectified_points",1,      //todo   /xtion/depth_registered/points
                                        &PlaneSegmentation::processCloud,
                                        this);
        //#>>>>TODO: Callback function register

        //#>>>>TODO: Initialize params



        }

        ~PlaneSegmentation() {}
    };

