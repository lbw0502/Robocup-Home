%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Exercise 1  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Robot: tiago

Packages: ics_gazebo

Compilation:

$ catkin_make

Execution:

$ roslaunch ics_gazebo tiago.launch world_suffix:=tutorial2



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Exercise 2  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Robot: tiago

Packages: ics_gazebo

Compilation:

$ catkin_make

Execution:

$ roslaunch ics_gazebo tiago.launch world_suffix:=tutorial2



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Exercise 3  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Robot: tiago

Packages: ics_gazebo    turtle_vis

Compilation:

$ catkin_make

Execution:

$ roslaunch ics_gazebo tiago.launch
$ roslaunch turtle_vis TurtleVis.launch

Give the desired position in the terminal as requested, such as "2,2,0", the delimiter has to be ","

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Exercise 4  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Robot: tiago

Packages: ics_gazebo   controllers_tutorials

Compilation:

$ catkin_make

Execution:

$ roslaunch ics_gazebo tiago.launch
$ rosrun controller_manager controller_manager kill torso_controller
$ roslaunch controllers_tutorials new_torso_controller.launch
