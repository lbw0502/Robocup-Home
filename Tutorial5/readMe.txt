-------------------------------Tutorial 5-------------------------------
Group Name: KNL_LPL

Group Member:
Fengyi Wang 
Shuo Ma
Zhannan Zhang 
Bowen Li

Contribution:
Navigation: Bowen Li
Object Recogniction: Fengyi Wang, Shuo Ma
Manipulation: Fengyi Wang, Zhannan Zhang
Intergration+Readme: Fengyi Wang, Bowen Li, Shuo Ma, Zhannan Zhang
-------------------------------------------------------------------------

Robot:HSRB

-------------------------------------------------------------------------
Copy the all folders in this .zip file into your workspace!!!
If catkin_make dose not work well at the first time and at the same time the "darknet_ros" is already in your workspace",
please catkin_make more times, it must works.

Notations before running the code:

1. make sure that package "darknet_ros" is in your workspace

2. connect to HSRB

3. in your workspace and open a terminal: chmod u+x src/arm_hsrb/lib/grab.py

4. in your workspace and open a terminal: chmod u+x src/arm_hsrb/lib/release.py 

5. $ rosservice call /reload_map "new_map_yaml: '/etc/opt/tmc/robot/conf.d/lab-map/map.yaml'"
   interpretation: let HSRB load the ics lab map

6. $ rosrun rviz rviz -d `rospack find hsrb_common_launch`/config/hsrb_display_full_hsrb.rviz
   interpretation: open the rviz

7. in rviz gui, use "pose estimation", drag HSRB model to the correct initial position.


-------------------------------------------------------------------------


Notations before building the code:

1. Build the perception_msgs and darknet_ros first

2. make the other packages

3. or simply make it twice
-------------------------------------------------------------------------

Steps running the code:

1. source your workspace

2. $ roslaunch arm_hsrb hsrb1.launch

3. $ roslaunch arm_hsrb hsrb2.launch

4. $ roslaunch object_recognition object_recognition.launch

5. $ rosrun from2dto3d from2dto3d_node

6. $ rosrun hsrb_move hsrb_move


*Attenation: please run the next step only when the last step is done, otherwise there will be some unexpected errors!

*Declaration: This version of the tutorial works well but with stupid method by moving the robot around.
 We had a better solution by moving the arm to manipulate the object with much higher accuracy and success rate.
 But Chenghao seemed to have changed some configuration on Thursday and then our solution did not work any more.
 So we finally submit this version.
