-------------------------ReadMe.txt---------------------------------------


Member: Zhannan Zhang
	Bowen Li

Job distribution: Zhannan Zhang--- Exercise 1, Exercise 2, launch file
		  Bowen Li     --- Exercise 1, Exercise 3, readme file

Copy the folder "from2Dto3D", "object_recognition", "perception_msgs", "plane_segmentation" to your workspace

Attention 1: make sure that "darknet_ros" is also in your workspace

Attention 2: the bag folder in Bowen_Li_Zhannan_Zhang_Tutorial4/plane_segmentation/ is empty, so you must copy 
the "hsrb_tutorial_4.bag"(size: 168.4MB) in this folder. Then you can do following things. Otherwise, you will get nothing.









Steps to run the code:

------------------------------Exercise 2-------------------------------
1. $roslaunch plane_segmentation plane_segment.launch 

Explaination: you can check the segmented point cloud(table or objects) through choosing the different "PointCloud2" topics in rviz


------------------------------Exercise 1&3 ----------------------------
if you want to check the exercise 3, just implement the following step 1, and you can get the result.

if you want to check the exercise 1, please follow all following steps.

1. $roslaunch object_recognition objectRecognition_launch.launch 

   open a new terminal and source your workspace.
2. $roslaunch from2dto3d from2dto2d.launch

3. type the object name in the terminal which you want to detect, for example "book"

   open a new terminal and source your workspace.
4. $rostopic echo /segmentation/point3D
     
     in this terminal, you can see the 3D coordinat of the object that you just typed.
