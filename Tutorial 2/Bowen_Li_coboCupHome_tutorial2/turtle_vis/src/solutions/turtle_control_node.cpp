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
 * CUSTOM CLASS
 * ******************************************************************/
#include <turtle_vis/myClass/TurtleClass.h>


int main( int argc, char** argv )
{

    ros::init(argc, argv, "turtle_control",ros::init_options::AnonymousName);

    ROS_INFO_STREAM("**Publishing turtle control..");

    ros::NodeHandle n;
    ros::Rate r(60);



    //ADVERTISE THE SERVICE
    turtleSpace::TurtleClass turtleF;
    ros::ServiceServer service=n.advertiseService("TurtlePose",
                                                  &turtleSpace::TurtleClass::getDPose,
                                                  //#>>>>TODO: DEFINE THE CALLBACK FUNCTION,
                                                  &turtleF);
    //CALL SERVICE FROM TERMINAL//
    //    rosservice call /TurtlePose '{p: [0.5, 0.0, 3.0]}'
    //    rosservice call /TurtlePose "{p: {x: 1.5, y: 1.0, theta: 0.0}}"
    //DON'T FORGET TO SOURCE THE WORKSPACE BEFORE CALLING THE SERVICE

    //ADVERTIZE THE TOPIC
    ros::Publisher pub=n.advertise<geometry_msgs::Twist/*#>>>>TODO: DEFINE THE MSG TYPE*/>("mobile_base_controller/cmd_vel",100);



    ros::Subscriber sub = n.subscribe("mobile_base_controller/odom",10,
                                      &turtleSpace::TurtleClass::getPose,
                                      &turtleF);



    ros::Time ti, tf;
    ti=ros::Time::now();

    //Proportional Gain
    Matrix2d K;


   	

    //#>>>>TODO: SET GAINS

    double d=0.0;
    double k = 0;
    double dt;

    //#>>>>TODO: LOAD control parameters FROM THE ROS PARAMETER SERVER 
    
    ros::param::get("turtle_control/controlPara/d",d);
    ros::param::get("turtle_control/controlPara/k",k);



    ROS_INFO_STREAM("d= "<<d);
    ROS_INFO_STREAM("k= "<<k);


    //Proportional Gain

    K<<k,0,
        0,k;



    ROS_INFO_STREAM("K= \n"<<K);

    Vector2d poseNow, poseD, error, T, VelD;
    Vector3d poseNow_extend(0,0,0);
    double theta;
    Matrix2d mat;

    poseNow << 0,0;
    poseD = poseNow;
    error << 0,0;
    T << 0,0;
    VelD << 0,0;


    //CREATE A DESIREDPOSE MSG VARIABLE
    geometry_msgs::Twist msg; //#>>>>TODO:DEFINE THE MSG TYPE

    while(ros::ok())
    {
        tf=ros::Time::now();

        dt=tf.toSec()-ti.toSec();

        ////#>>>>TODO: Get Desired Pose from the class variable
        poseD = turtleF.getLocalDesiredPose();
        poseNow_extend = turtleF.getLocalPose();
        theta = poseNow_extend[2];

        poseNow[0] = poseNow_extend[0];// + d*cos(theta);
        poseNow[1] = poseNow_extend[1];// + d*sin(theta);
        

        error = poseD - poseNow;
        VelD = K * error;

        

        mat << cos(theta), -d*sin(theta),
                sin(theta), d*cos(theta);
        
        T = mat.inverse() * VelD;



        //Publish Data
        ////#>>>>TODO:SET THE MSG VARIABLE WITH THE NEW TURTLE POSE

        msg.linear.x = T[0];
        msg.angular.z = T[1];
        
        pub.publish(msg);

        ti=tf;

        //ROS::SPIN IS IMPORTANT TO UPDATE ALL THE SERVICES AND TOPICS
        ros::spinOnce();

        r.sleep();
    }

    return 0;
}


