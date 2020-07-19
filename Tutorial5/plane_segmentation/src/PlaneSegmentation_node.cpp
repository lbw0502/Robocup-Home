#include <plane_segmentation/PlaneSegmentation.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "plane_segmentation_node");
    ros::NodeHandle nh;
    PlaneSegmentation node(nh);
    ros::spin();
    return 0;
}


