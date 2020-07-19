#include<arm_hsrb/joint_space.h>


int main(int argc, char** argv)
{
    ros::init(argc, argv, "plan_arm_torso_fk");

    float para1 = atof(argv[1]);
    float para2 = atof(argv[2]);
    float para3 = atof(argv[3]);
    float para4 = atof(argv[4]);
    float para5 = atof(argv[5]);
    float para6 = atof(argv[6]);


    ros::NodeHandle nh;
    
    joint_space_Obj Obj(nh,para1,para2,para3,para4,para5,para6);
    
    return 0;
}
