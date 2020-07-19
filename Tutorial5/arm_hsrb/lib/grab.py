#!/usr/bin/env python
# Copyright (C) 2017 Toyota Motor Corporation
import sys
import geometry_msgs.msg
import moveit_commander
import rospy
import trajectory_msgs.msg
import moveit_msgs.msg
    
class grasp(object):
    def __init__(self, wait=0.0):
        # initialize
        moveit_commander.roscpp_initialize(sys.argv)
        rospy.init_node('grasp', anonymous=True)
        arm = moveit_commander.MoveGroupCommander('arm')
        

        rospy.loginfo("Grasp")
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

        rospy.loginfo("Rise arm")
        arm.set_joint_value_target({"arm_lift_joint": 0.5,
                                     "arm_flex_joint": -1.0,
                                     "arm_roll_joint":0.0,
                                     "wrist_flex_joint":-0.5236,
                                     "wrist_roll_joint":0.0,
                                     "wrist_ft_sensor_frame_joint":0.0})
        arm.go()
        

        rospy.loginfo("Move arm back")
        arm.set_joint_value_target({"arm_lift_joint": 0.5,
                                     "arm_flex_joint": -0.5,
                                     "arm_roll_joint":0.0,
                                     "wrist_flex_joint":-0.5236,
                                     "wrist_roll_joint":0.0,
                                     "wrist_ft_sensor_frame_joint":0.0})
        arm.go()

        rospy.loginfo("step4: move_arm_to_go")
        arm.set_named_target("go")
        arm.go()
        rospy.logdebug("done")
        # finalize
        moveit_commander.roscpp_shutdown()
        moveit_commander.os._exit(0)


if __name__ == "__main__":
    grasp(float(sys.argv[1]) if len(sys.argv) > 1 else 0.0)
