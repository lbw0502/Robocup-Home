#include<plane_segmentation/PlaneSegmentation_class.h>

using namespace std;
using namespace cv;

PlaneSegmentation::PlaneSegmentation(ros::NodeHandle nh) : nh_(nh), priv_nh_("~") //,
        //sub(nh, "topic", 5) // constructor initialization form for the subscriber if needed
    {

        //! Subscribes to and advertises topics
        pub_plane_pc_ = nh_.advertise< pcl::PointCloud<pcl::PointXYZ> >("/segmentation/plane_points", 10);
        pub_clusters_pc_ = nh_.advertise< pcl::PointCloud<pcl::PointXYZ> >("/segmentation/clusters_points", 10);

        //#>>>>TODO: Callback function register
        sub = nh_.subscribe<sensor_msgs::PointCloud2> ("/hsrb/head_rgbd_sensor/depth_registered/rectified_points", 1, &PlaneSegmentation::cloud_cb, this);

        //#>>>>TODO: Initialize params

    }


PlaneSegmentation::~PlaneSegmentation() {}




void PlaneSegmentation::cloud_cb(const sensor_msgs::PointCloud2ConstPtr &input)
{

    pcl::PointCloud< pcl::PointXYZ > pc; // internal data
    

   
	//#>>>>TODO: Convert the data to the internal var (pc) using pcl function: fromROSMsg
    pcl::fromROSMsg (*input, pc);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_orignal = pc.makeShared();                             // cloud to be operated
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_gd (new pcl::PointCloud<pcl::PointXYZ>);     //cloud to store the filtered-process1 data
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_pass_1 (new pcl::PointCloud<pcl::PointXYZ>); // clood to store the filtered-process2 data
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered( new pcl::PointCloud<pcl::PointXYZ> );       // cloud to store the final filtered data

    
    std::cout << "PointCloud before filtering has: " << pc.points.size() << " data points." << std::endl; //*
    std::cout << "width: " << pc.width << "height: " << pc.height << std::endl;


    //#>>>>TODO: Down sample the pointcloud using VoxelGrid

    // filter process 1
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud(cloud_orignal);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter(*cloud_filtered_gd);

    // filter process 2
    pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud (cloud_filtered_gd);
	pass.setFilterFieldName ("z");
	pass.setFilterLimits (0.0, 1.1);
    pass.filter (*cloud_filtered_pass_1);

    // final filter process
    pass.setInputCloud (cloud_filtered_pass_1);
    pass.setFilterFieldName ("y");
	pass.setFilterLimits (-0.3, 0.15);
	pass.filter (*cloud_filtered);

    //----

    std::cout << "PointCloud after filtering has: " << cloud_filtered->points.size()  << " data points." << std::endl;
    


    // Create the segmentation object for the plane model and set all the parameters using pcl::SACSegmentation<pcl::PointXYZ>
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    pcl::PointIndices::Ptr inliers( new pcl::PointIndices );
    pcl::ModelCoefficients::Ptr coefficients( new pcl::ModelCoefficients );
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane( new pcl::PointCloud<pcl::PointXYZ>() );

    //#>>>>TODO: set parameters of the SACS segmentation
    // Optional
    seg.setOptimizeCoefficients (true);
    // Mandatory
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setMaxIterations (1000);
    seg.setDistanceThreshold (0.02);
    seg.setProbability (0.95);
	

    //----

    int nr_points = (int) cloud_filtered->points.size();

    // Segment the planes using pcl::SACSegmentation::segment() function and pcl::ExtractIndices::filter() function
	// TODO
        // If you want to extract more than one plane you have to do a while
    seg.setInputCloud(cloud_filtered);
    seg.segment(*inliers, *coefficients);

    // Create the extraction object
    pcl::ExtractIndices<pcl::PointXYZ> extract;

    // Extract the inliers
    extract.setInputCloud (cloud_filtered);
    extract.setIndices (inliers);

    // extract the plane
    extract.setNegative (false);
    extract.filter(curr_table_pc);

    // extract the rest objects
    extract.setNegative (true);
    extract.filter(curr_clusters_pc);

    //----


    //#>>>>TODO: Publish biggest plane

	// Tips: 
	// - you can copy the pointcloud using cl::copyPointCloud()
	// - Set the header frame_id to the pc2 header frame_id
	// - you can use pcl_conversions::toPCL() to convert the stamp from pc2 header to pointcloud header stamp
	// - to publish -> pub_plane_pc_.publish( pointcloud_variable.makeShared() )
    //----

    pub_plane_pc_.publish(curr_table_pc);
          

    //#>>>>TODO: Publish other clusters
    // Tip: similar to the previous publish
    pub_clusters_pc_.publish(curr_clusters_pc);
    


    //return;
    ROS_INFO("done!");


}
