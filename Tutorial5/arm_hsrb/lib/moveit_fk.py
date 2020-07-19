#!/usr/bin/env python
# Copyright (C) 2017 Toyota Motor Corporation

import sys

import moveit_commander
import rospy


class MoveItFKDemo(object):
    def __init__(self, wait=0.0):
        # initialize
        moveit_commander.roscpp_initialize(sys.argv)
        rospy.init_node("movetograb", anonymous=True)

        arm = moveit_commander.MoveGroupCommander("arm")
        head = moveit_commander.MoveGroupCommander("head")

        # move_to_neutral
        head.set_named_target("neutral")
        head.go()
        
        
        arm.set_joint_value_target({"arm_lift_joint": 0.3,
                                     "arm_flex_joint": -1.0,
                                     "arm_roll_joint":0.0,
                                     "wrist_flex_joint":-0.5236,
                                     "wrist_roll_joint":0.0,
                                     "wrist_ft_sensor_frame_joint":0.0})
        arm.go()

        # finalize
        moveit_commander.roscpp_shutdown()
        moveit_commander.os._exit(0)


if __name__ == "__main__":
    MoveItFKDemo(float(sys.argv[1]) if len(sys.argv) > 1 else 0.0)
