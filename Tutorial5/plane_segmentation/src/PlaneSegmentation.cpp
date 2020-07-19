#include <plane_segmentation/PlaneSegmentation.h>


void PlaneSegmentation::processCloud(const sensor_msgs::PointCloud2ConstPtr &var)  //TypeConstPtr
{

    pcl::PointCloud< pcl::PointXYZ > pc; // internal data
    

   
	//#>>>>TODO: Convert the data to the internal var (pc) using pcl function: fromROSMsg
    pcl::fromROSMsg(*var,pc);   //  todo
    

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = pc.makeShared(); // cloud to operate
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered( new pcl::PointCloud<pcl::PointXYZ> ); //cloud_f// todo cloud to store the filter the data

    std::cout << "PointCloud before filtering has: " << pc.points.size() << " data points." << std::endl; //*
    std::cout << "width: " << pc.width << "height: " << pc.height << std::endl;


    // Create the filtering object    to cut the wall
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (0.0, 1.0);
    //pass.setFilterLimitsNegative (true);
    pass.filter (*cloud_filtered);

    
    // cut the cabel
    /* pcl::PassThrough<pcl::PointXYZ> pass1;
    pass1.setInputCloud (cloud_filtered);
    pass1.setFilterFieldName ("x");
    pass1.setFilterLimits (-2, 3);
    //pass.setFilterLimitsNegative (true);
    pass1.filter (*cloud_filtered);*/


    //#>>>>TODO: Down sample the pointcloud using VoxelGrid
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud(cloud_filtered);
    sor.setLeafSize(0.01f,0.01f,0.01f);
    sor.filter(*cloud_filtered);                // todo*4

    //----

    std::cout << "PointCloud after filtering has: " << cloud_filtered->points.size()  << " data points." << std::endl;
    


    // Create the segmentation object for the plane model and set all the parameters using pcl::SACSegmentation<pcl::PointXYZ>
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    pcl::PointIndices::Ptr inliers( new pcl::PointIndices );
    pcl::ModelCoefficients::Ptr coefficients( new pcl::ModelCoefficients );
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane( new pcl::PointCloud<pcl::PointXYZ>() );

    //#>>>>TODO: set parameters of the SACS segmentation
	seg.setInputCloud(cloud_filtered);      //cloud_filtered
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(0.025);     //0.02
    seg.setMaxIterations(100);
    seg.setProbability(0.95);
    seg.segment(*inliers,*coefficients);      //todo*7

    //----

    //int nr_points = (int) cloud_filtered->points.size();     todo

    // Segment the planes using pcl::SACSegmentation::segment() function and pcl::ExtractIndices::filter() function
	// TODO
        // If you want to extract more than one plane you have to do a while
    pcl::ExtractIndices<pcl::PointXYZ> extract_pts;
    extract_pts.setInputCloud(cloud_filtered);
    extract_pts.setIndices(inliers);
    extract_pts.setNegative(false);
    extract_pts.filter(curr_table_pc);
    extract_pts.setNegative(true);
    extract_pts.filter(curr_clusters_pc);   //todo*7

    pub_plane_pc_.publish(curr_table_pc);
    pub_clusters_pc_.publish(curr_clusters_pc);   //todo*2

    //----


    //#>>>>TODO: Publish biggest plane

	// Tips: rosl
	// - you can copy the pointcloud using cl::copyPointCloud()
	// - Set the header frame_id to the pc2 header frame_id
	// - you can use pcl_conversions::toPCL() to convert the stamp from pc2 header to pointcloud header stamp
	// - to publish -> pub_plane_pc_.publish( pointcloud_variable.makeShared() )
    //----


    //#>>>>TODO: Publish other clusters
    // Tip: similar to the previous publish
    


    return;


}


