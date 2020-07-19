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
        rospy.init_node('release', anonymous=True)
        arm = moveit_commander.MoveGroupCommander("arm")
        gripper = moveit_commander.MoveGroupCommander("gripper")
        gripper.set_goal_joint_tolerance(0.05)


        rospy.sleep(2.)

        rospy.loginfo("Raise arm")
        arm.set_joint_value_target({"arm_lift_joint": 0.5,
                                     "arm_flex_joint": -1.0,
                                     "arm_roll_joint":0.0,
                                     "wrist_flex_joint":-0.5236,
                                     "wrist_roll_joint":0.0,
                                     "wrist_ft_sensor_frame_joint":0.0})
        arm.go()
        rospy.sleep(1.)

        rospy.loginfo("Put down")
        arm.set_joint_value_target({"arm_lift_joint": 0.3,
                                     "arm_flex_joint": -1.0,
                                     "arm_roll_joint":0.0,
                                     "wrist_flex_joint":-0.5236,
                                     "wrist_roll_joint":0.0,
                                     "wrist_ft_sensor_frame_joint":0.0})
        arm.go()
        rospy.sleep(1.)
        # open
        rospy.loginfo("Open gripper")
        gripper.set_joint_value_target("hand_motor_joint", 1.2)
        gripper.go()
        rospy.sleep(1.)

        rospy.loginfo("rise arm")
        arm.set_joint_value_target({"arm_lift_joint": 0.5,
                                     "arm_flex_joint": -1.0,
                                     "arm_roll_joint":0.0,
                                     "wrist_flex_joint":-0.5236,
                                     "wrist_roll_joint":0.0,
                                     "wrist_ft_sensor_frame_joint":0.0})
        arm.go()
        rospy.sleep(1.)

        rospy.loginfo("Move_arm_to_'go' position")
        arm.set_named_target("go")
        arm.go()
        rospy.logdebug("done")

        rospy.sleep(wait)


if __name__ == "__main__":
    # rospy.Subscriber("/segmentation/point3D",geometry_msgs.msg.PointStamped,PalmTarget_callback)
    # rospy.loginfo("Subscriber initialized")
    grasp(float(sys.argv[1]) if len(sys.argv) > 1 else 0.0)
