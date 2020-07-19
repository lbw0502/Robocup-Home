#include <pcl_ros/point_cloud.h> // enable pcl publishing
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/filters/passthrough.h>

#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

#include <image_geometry/pinhole_camera_model.h>

// Visualization
//#include <visualization_msgs/MarkerArray.h>
//#include <visualization_msgs/Marker.h>

//#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <geometry_msgs/PoseStamped.h>


class PlaneSegmentation
{

private:
    //! The node handle
    ros::NodeHandle nh_;
    //! Node handle in the private namespace
    ros::NodeHandle priv_nh_;


    //#>>>>TODO: Create subscriber to the PointCloud data
    // Optional: MESSAGE FILTERS COULD BE A GOOD IDEA FOR GRABBING MULTIPLE TOPICS SYNCRONIZED, NOT NEEDED THOUGH
    ros::Subscriber sub;


    //#>>>>TODO: Create publishers for pointclouds
    ros::Publisher pub_plane_pc_;
    ros::Publisher pub_clusters_pc_;


    // Parameters
    //#>>>>TODO: Load parameters if needed
    



    // Internal data
    pcl::PointCloud<pcl::PointXYZ> curr_table_pc;
    pcl::PointCloud<pcl::PointXYZ> curr_clusters_pc;
    
    //#>>>>TODO: Create more containers if needed.
    

    //------------------ Callbacks -------------------

    // Callback for service calls
	

    //! Callback for subscribers
    //! Complete processing of new point cloud
    void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& input); // for multiple data topics (const sensor_msgs::TypeConstPtr &var, const sensor_msgs::TypeConstPtr &var, ...)

public:
    
    PlaneSegmentation(ros::NodeHandle nh);
    ~PlaneSegmentation();
};