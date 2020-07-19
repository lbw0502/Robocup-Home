#include<from2Dto3D/from2Dto3D_class.h>


using namespace std;
using namespace cv;


From2Dto3D::From2Dto3D(ros::NodeHandle nh) : nh_(nh), priv_nh_("~")
{

  //#>>>>TODO: Set publishers and subscribers.
  sub_hsrbPoint = nh_.subscribe<sensor_msgs::PointCloud2> ("/hsrb/head_rgbd_sensor/depth_registered/rectified_points", 100, &From2Dto3D::processCloud, this);
  sub_rect = nh_.subscribe<perception_msgs::Rect> ("/rect", 100, &From2Dto3D::processRect, this);
  pub_point3D = nh_.advertise<geometry_msgs::Point> ("/segmentation/point3D",100);


  // subscribers to the bounding boxes and the point cloud
  // format:
  // sub_name = nh_.subscribe<Type>("topic", queuesize, Function_of_the_class, this);

  // Publishers
  // format:
  //pub_name = nh_.advertise< Type >("topic", queuesize);

  ROS_INFO("from2Dto3D initialized ...");

}


From2Dto3D::~From2Dto3D() {}


void From2Dto3D::processCloud(const sensor_msgs::PointCloud2ConstPtr& pc)
{    
    //#>>>>TODO: store local data copy or shared, depending on the message
    pcl::fromROSMsg (*pc, pc_local);
}


void From2Dto3D::processRect(const perception_msgs::RectConstPtr& r)
{

    //#>>>>TODO: process bounding box and send 3D position to the topic
    // tip: take a look at the pcl::PointXYZRGB structure
    int x = r->x;
    int y = r->y;
    int width = r->width;
    int height = r-> height;

    int x_cen = x + width/2;
    int y_cen = y - height/2;
    
    while(1){
      std::cout <<"state is:"<< pc_local.isOrganized() << std::cout;
      if (pc_local.isOrganized() == 1) break;
    }

    point3D.x = pc_local.at(x_cen, y_cen).x;
    point3D.y = pc_local.at(x_cen, y_cen).y;
    point3D.z = pc_local.at(x_cen, y_cen).z;

    pub_point3D.publish(point3D);

}