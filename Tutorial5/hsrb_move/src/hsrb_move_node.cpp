#include<hsrb_move/hsrb_move.h>




int main(int argc, char** argv){

  ros::init(argc, argv, "hsrb_move_node");
  ros::NodeHandle nh;
  ros::Rate r(60);

  hsrb_move_Obj Obj(nh);
  Obj.moving();


  return 0;


}