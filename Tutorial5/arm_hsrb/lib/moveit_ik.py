#!/usr/bin/env python
# Copyright (C) 2017 Toyota Motor Corporation
import sys
import geometry_msgs.msg
import moveit_commander
import rospy
import trajectory_msgs.msg
import moveit_msgs.msg

def PalmTarget_callback(StamptedPoint):
    global TP
    TP = StamptedPoint.point
    
class grasp(object):
    def __init__(self, wait=0.0):
        # initialize
        moveit_commander.roscpp_initialize(sys.argv)
        rospy.init_node('grasp', anonymous=True)
        rospy.Subscriber("/segmentation/point3D",geometry_msgs.msg.PointStamped,PalmTarget_callback)

        arm = moveit_commander.MoveGroupCommander('arm')
        head = moveit_commander.MoveGroupCommander('head')
        whole_body = moveit_commander.MoveGroupCommander('whole_body')
        base = moveit_commander.MoveGroupCommander("base")
        # whole_body_weighted \
        #     = moveit_commander.MoveGroupCommander('whole_body_weighted')
        # whole_body_light \
        #     = moveit_commander.MoveGroupCommander('whole_body_light')
        rospy.sleep(10.)
        # move_to_neutral
        rospy.wait_for_message("/segmentation/point3D", geometry_msgs.msg.PointStamped)
        rospy.loginfo("Target pose recieved")
        rospy.loginfo("step1: move_to_neutral")
        #arm.set_named_target("neutral")
        #arm.go()
        head.set_named_target("neutral")
        head.go()   

        rospy.logdebug("done")
        # rospy.sleep(wait)

        rospy.sleep(3.)

        # move hand forward
        rospy.loginfo("step2: move hand forward")
        p_target = geometry_msgs.msg.PoseStamped()
        p_target.header.frame_id = "hand_palm_link"
        p_target.pose.position.x = TP.x
        p_target.pose.position.y = TP.y
        p_target.pose.position.z = TP.z
        p_target.pose.orientation.w = 1
        # moveit_commander.MoveGroupCommander('whole_body').set_joint_value_target(p_target)
        # moveit_commander.MoveGroupCommander('whole_body').go()
        whole_body.set_joint_value_target(p_target)
        whole_body.go()
        rospy.logdebug("done")
        # rospy.sleep(wait)

        rospy.sleep(1.)
        rospy.loginfo("step3: grasp")
        # grasp
        gripper = moveit_commander.MoveGroupCommander("gripper")
        gripper.set_goal_joint_tolerance(0.05)
        t = moveit_msgs.msg.RobotTrajectory()
        t.joint_trajectory.joint_names = ["hand_motor_joint"]
        pg = trajectory_msgs.msg.JointTrajectoryPoint()
        pg.positions = [0.0]
        pg.effort = [-0.01]
        pg.time_from_start = rospy.Duration(1.0)
        t.joint_trajectory.points.append(pg)
        gripper.execute(t)
         # rospy.sleep(wait)       

        rospy.loginfo("step4: rise arm")
        p = geometry_msgs.msg.PoseStamped()
        p.header.frame_id = "hand_palm_link"
        p.pose.position.x = 0.1
        p.pose.position.y = 0
        p.pose.position.z = 0
        p.pose.orientation.w = 1
        whole_body.set_joint_value_target(p)
        whole_body.go()
        rospy.logdebug("done")
        rospy.sleep(wait)
 
        rospy.loginfo("step5: move arm back")
        p.pose.position.x = 0
        p.pose.position.y = 0
        p.pose.position.z = -0.5
        whole_body.set_joint_value_target(p)
        whole_body.go()
        rospy.logdebug("done")
        rospy.sleep(wait)

        rospy.loginfo("step6: move_arm_to_go")
        arm.set_named_target("go")
        arm.go()
        rospy.logdebug("done")

        # finalize
        moveit_commander.roscpp_shutdown()
        moveit_commander.os._exit(0)


if __name__ == "__main__":
    # rospy.Subscriber("/segmentation/point3D",geometry_msgs.msg.PointStamped,PalmTarget_callback)
    rospy.loginfo("Subscriber initialized")
    grasp(float(sys.argv[1]) if len(sys.argv) > 1 else 0.0)
