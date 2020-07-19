------------------------ Task 1 ----------------------------------------

"small_office" and "tutorial_office" are in folder "task 1"





------------------------ Task 2 ----------------------------------------

open the folder "task_2"

copy the package "naviagtion_goals" to tiago workspace

$ source devel/setup.bash

$ roslaunch navigation_goals navigation.launch 

the tiago robot will patrol A-B-C


------------------------ Task 3 ----------------------------------------

open the folder "task_3"

copy the package "naviagtion_goals_lift" to tiago workspace

$ source devel/setup.bash

$ roslaunch navigation_goals_lift navigation.launch 

the tiago robot will go to point C, lift the table and put it down. Then it will patrol A-B-C



*************************************************************************
Note: when the robot can't localize itself correctly at the beginning, just launch it again!

