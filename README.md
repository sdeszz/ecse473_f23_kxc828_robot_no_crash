# ecse473_f23_kxc828_robot_no_crash

This README provides instructions on how to use the ROS (Robot Operating System) system node to run a simulation control algorithm for a laser obstacle avoidance robot operating in a maze environment.

## Prerequisites

Before you begin, make sure you have the following prerequisites installed:

- ROS (Robot Operating System): [ROS Installation Guide](http://wiki.ros.org/ROS/Installation)
- Gazebo: ROS simulation environment for testing
- rqt_gui: ROS tool for remote control

## Getting Started

1. Clone this repository to your ROS workspace:

   ```
   git clone https://github.com/sdeszz/ecse373_f23_kxc828_subscriber_package.git
   ```

2. Build the ROS package:
  ```
  cd ~/catkin_ws
  catkin_make
  ```
3. Running the Simulation
Launch the simulation using the second.launch launch file:

  ```
  roslaunch robot_no_crash second.launch
  ```
The simulation will launch, and you should see the robot model in the maze environment.

4. Controlling the Robot
Open the rqt_gui for remote control:
  ```
  rosrun rqt_gui rqt_gui
  ```
Use the rqt_gui interface to send control signals to the robot. The algorithm implemented in the src directory allows the robot to receive signals from rqt_gui and control its movement while avoiding collisions with maze walls.
