/*********************************************************************
* Compiler:         gcc 4.6.3
*
* Company:          Institute for Cognitive Systems
*                   Technical University of Munich
*
* Author:           Emmanuel Dean (dean@tum.de)
*                   Karinne Ramirez (karinne.ramirez@tum.de)
*
* Compatibility:    Ubuntu 12.04 64bit (ros hydro)
*
* Software Version: V0.1
*
* Created:          01.06.2015
*
* Comment:          turtle connection and visualization (Sensor and Signals)
*
********************************************************************/


/*********************************************************************
* STD INCLUDES
********************************************************************/
#include <iostream>
#include <fstream>
#include <pthread.h>


/*********************************************************************
* ROS INCLUDES
********************************************************************/
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <tf_conversions/tf_eigen.h>

/*********************************************************************
* EIGEN INCLUDES
********************************************************************/
#include <Eigen/Eigen>
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <Eigen/Core>




/*********************************************************************
 * SEVICES AND MESSAGES
 * ******************************************************************/
//SET HEADERS FOR THE SERVICE AND THE MESSAGES OF THE TURTLE_VIS PACKAGE
#include<turtle_vis/myClass/TurtleClass.h>
#include <turtle_vis/DesiredPose.h>
#include <turtle_vis/send_desired_pose.h>



using namespace Eigen;


int main(int argc, char** argv)
{

    ros::init(argc, argv, "turtle_set_position",ros::init_options::AnonymousName);

    ROS_INFO_STREAM("**Client turtle desired position");

    ros::NodeHandle n;
    ros::Rate r(60);

    //INITIALIZE THE CLIENT
    ros::ServiceClient client=n.serviceClient<turtle_vis::send_desired_pose/*//#>>>>TODO: DEFINE THE SERVICE TYPE*/>("TurtlePose");

    ////#>>>>TODO: DEFINE A MSG VARIABLE FOR THE SERVICE MESSAGE
    turtle_vis::send_desired_pose msg;

    std::string myString;

    std::string sub1, sub2, sub3;
    int pos1, pos2;


    static tf::TransformBroadcaster br;           // create a broadcaster
    tf::Transform transform;                      // create a transform variable, will be used to describe the transform information between two coordinates
                                                    // including the translation and rotation information

    tf::Quaternion qtf;                           // create a quaternion variable, will be used to describe the rotation information between two coordinates

    while(ros::ok())
    {

        std::vector<double> vals;

        ROS_INFO_STREAM("Give me the desired position of the turtle: x,y,theta");
        std::cin>>myString;

        ////#>>>>TODO:GET THE VALUES FROM THE TERMINAL AND SAVE THEM IN A LOCAL VARIABLE. YOU WILL GET X,Y AND THETA
        pos1 = myString.find(",");
        pos2 = myString.rfind(",");

        sub1 = myString.substr(0, pos1);
        sub2 = myString.substr(pos1+1, pos2-pos1-1);
        sub3 = myString.substr(pos2+1, myString.length());

      
        vals.push_back(atof(sub1.c_str()));
        vals.push_back(atof(sub2.c_str()));
        vals.push_back(atof(sub3.c_str()));



        ////#>>>>TODO:CREATE THE MESSAGE WITH THE LOCAL VARIABLE
        msg.request.x = vals[0];
        msg.request.y = vals[1];
        msg.request.theta = vals[2];




        ////#>>>>TODO:COMPUTE THE POSITION AND ORIENTATION OF THE TF FOR THE DESIRED POSITION
        
        
        //qtf.setRPY(0,0,////#>>>>TODO:USE THETA VARIABLE);
        qtf.setRPY(0,0,vals[2]);    // use Quaternion to represent the rotation information

        //transform.setOrigin(tf::Vector3(/*//#>>>>TODO:USE X VARIABLE*/, /*//#>>>>TODO:USE Y VARIABLE*/, 0));
        transform.setOrigin(tf::Vector3(vals[0], vals[1], 0));       //set the translation information into transform

        transform.setRotation(qtf);             // set the rotation information into transform

        // broadcast the transform information between the world coordinate and turtle_desired coordinate, the moment is ros::Time::now()
        br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"/world","/turtle_desired")); 
        



        if(client.call(msg))//#>>>>TODO:CALL THE CLIENT WITH msg)
        {
            //#>>>>TODO:PLOT THE MESSAGE

            ROS_INFO("The desired position is: x=%f, y=%f,theta=%f", msg.request.x, msg.request.y, msg.request.theta);

        }
        else
        {
            ROS_ERROR_STREAM("Failed to call the service 'TurtlePose'");
            return 1;
        }

    }



    return 0;
}
