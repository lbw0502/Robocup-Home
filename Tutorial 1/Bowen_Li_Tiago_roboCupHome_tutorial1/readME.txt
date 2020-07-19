1) open terminal1:
   cd workspace/roboCupHome_tutorial_Bowen/

2) in terminal1: 
   source devel/setup.bash

3) in terminal1:
   roslaunch turtle_vis TurtleVis.launch

4) open terminal2:
   cd workspace/roboCupHome_tutorial_Bowen/

5) in terminal2:
   source devel/setup.bash

Method1 to call the service: 
6) in terminal2:
   rosservice call /TurtlePose "x: 1.0
y: 2.0
theta: 3.0" 

Method2 to call the service: 
6) in terminal2:
   rosrun turtle_vis turtle_set_position 
7) in terminal2:
   1.0,2.0,3.0
   (note: the input structure must be: "x,y,theta", the delimiter must be ",").

---------------------------------------------------------------------------------

Questions:
1) There are two ways to send the desired position.
   Method1: rosservice call /TurtlePose "x: 1.0
y: 2.0
theta: 3.0"
   explaination: use "rosservice call" command to send the service message manually. The Server reveives the service message directly, and the node "turtle_set_position" is unactived. 

   Method2: rosrun turtle_vis turtle_set_position 
   explaination: active the node "turtle_set_position". When we type the desired position in the terminal, the position information will be given to the request part of the service message. The Client sends this message and the Server reveives this message. If we want to change the position, just type a new one in the terminal.



2) The service is synchronous. The ROS programm waits until the Client receives the response. The communication involves only two nodes, the Client and the Server. It is a one-to-one communication. And we can also get the reply information.
   The topic is asynchronous. The Subscriber just receives the topic message and it doesn't care which publisher sends this message. It is a more-to-more communication.

   If the Server is replaced for a Subscriber, we have to send topic message instead of service message. Once a message is written into the topic, the subscriber keeps reading it. Though, it stil works.
