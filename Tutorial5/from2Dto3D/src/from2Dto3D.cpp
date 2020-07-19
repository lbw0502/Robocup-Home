#include <from2Dto3D/from2Dto3D.h>


From2Dto3D::From2Dto3D(ros::NodeHandle nh) : nh_(nh), priv_nh_("~")
{
        
  // subscribers to the bounding boxes and the point cloud
  
  pc_sub = nh_.subscribe("/hsrb/head_rgbd_sensor/depth_registered/rectified_points",100,
                                &From2Dto3D::processCloud,
                                this);


  // pc_sub = nh_.subscribe("/segmentation/clusters_points",100,
  //                                &From2Dto3D::processCloud,
  //                                this);


  
  obj_center_sub=nh_.subscribe("/Object/perception_msgs",100,
                                  &From2Dto3D::processRect,
                                  this);                                      
  obj_3d_pub = nh_.advertise<geometry_msgs::PointStamped>("/segmentation/point3D", 100);                         
  // format:
  // sub_name = nh_.subscribe<Type>("topic", queuesize, Function_of_the_class, this);

  // Publishers
  // format:
  //pub_name = nh_.advertise< Type >("topic", queuesize);
  

  ROS_INFO("Initializing, please wait");

}

From2Dto3D::~From2Dto3D() {}






void From2Dto3D::processCloud(const sensor_msgs::PointCloud2ConstPtr& pc)
{
    // store local data copy or shared, depending on the message
    ROS_INFO_STREAM("Waiting for cloud point");
    pcl::fromROSMsg(*pc, cloud);
    while(!cloud.isOrganized())
    {}
    std::vector<perception_msgs::Rect> msgs_tmp;
    if(msgs_exe3.size()!=0)
    {
      msgs_tmp = msgs_exe3;
      ROS_INFO_STREAM("Detected "<<msgs_tmp.size()<<" objects, they are:");
      
      for(int i = 0;i < msgs_tmp.size();i++)
      {
        if (msgs_tmp[i].header.frame_id=="bottle" ){
        ROS_INFO_STREAM("Object is "<<msgs_tmp[i].header.frame_id<<":");
        x_2d = msgs_tmp[i].x;
        y_2d = msgs_tmp[i].y;
        ROS_INFO_STREAM("2D location of "<<msgs_tmp[i].header.frame_id<<" is: "<<x_2d<<","<<y_2d);
        coordinate_3D.point.x = cloud.at(x_2d,y_2d).x;
        coordinate_3D.point.y = cloud.at(x_2d,y_2d).y;
        coordinate_3D.point.z = cloud.at(x_2d,y_2d).z;
        ROS_INFO_STREAM("3D location of "<<msgs_tmp[i].header.frame_id<<" is: "<<coordinate_3D.point.x<<","<<coordinate_3D.point.y<<","<<coordinate_3D.point.z);
        cloudheader = pcl_conversions::fromPCL(cloud.header);
        coordinate_3D.header = cloudheader;
        ROS_INFO_STREAM("Waiting for transform");
        listener_ToBase.waitForTransform("/hand_palm_link","head_rgbd_sensor_rgb_frame",ros::Time(0), ros::Duration(5.0));
        coordinate_3D.header.stamp = ros::Time(0);  
        listener_ToBase.transformPoint("/hand_palm_link", coordinate_3D, coordinate_3D_base);

        // ROS_INFO_STREAM("3D location of "<<msgs_tmp[i].header.frame_id<<" is: "<<coordinate_3D.point.x<<","<<coordinate_3D.point.y<<","<<coordinate_3D.point.z);
        ROS_INFO_STREAM("3D location of "<<msgs_tmp[i].header.frame_id<<" in hand_palm_link is: "<<coordinate_3D_base.point.x<<","<<coordinate_3D_base.point.y<<","<<coordinate_3D_base.point.z);
        
        obj_3d_pub.publish(coordinate_3D_base);
        }

        
      }
      std::cout<<std::endl;

    }
}

void From2Dto3D::processRect(const perception_msgs::RectArrayConstPtr& r)
{
msgs_exe3 = r->rect_array; 
//ROS_INFO("c"); 
}



