#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"
// %EndTag(MSG_HEADER)%

#include <sstream>
ros::Publisher *p_pub;
sensor_msgs::LaserScan wall;
geometry_msgs::Twist desire;

float wall_dist = 0.5;

void chatterCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
  
  desire = *msg;
  p_pub->publish(desire);
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
  //p_pub->publish(msg);
  wall=*msg;
  int tmp = 0;
  geometry_msgs::Twist goal;
  
  for(float range : wall.ranges){
    	if(range < wall_dist){
		    ROS_WARN("Distance is too close!!");
    		tmp = 1;
    		break;
    	}
    }
    ROS_INFO("FLAG: [%d]!", tmp);
    if(tmp == 1){
    	desire.linear.x = -0.01;
    	desire.angular.z = -0.5;
    	p_pub->publish(desire);
    	tmp = 0;
    	
    }
  
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "publisher");

  ros::NodeHandle n;


  ros::Publisher publisher_handle = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  //ros::param ("/robot0/des_vel", 1000, chatterCallback);
  ros::Subscriber chatter_sub = n.subscribe<geometry_msgs::Twist>("des_vel", 1000, chatterCallback);
  ros::Subscriber another_sub = n.subscribe<sensor_msgs::LaserScan>("laser_0", 1000, laserCallback);
  

  p_pub =&publisher_handle;
  
  ros::Rate loop_rate(10);
  /*double wall_dist = 0.0;
  // Get the parameter using the node handle
  if (n.getParam("wall_dist", wall_dist)){
     ROS_INFO("wall_dist is: [%2.2f]", wall_dist);
  }
  else{
    ROS_ERROR("Failed to get param 'wall_dist'");
  }*/
  float wall_dist = 0.5;
  // Announce the value of wall_dist before the first call to the Parameter Server
  
  ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);
  // Get the parameter using the node handle that can be updated
  
  if (n.getParamCached("wall_dist", wall_dist)) {
    ROS_INFO("wall_dist was updated to: [%2.2f]", wall_dist);
  }
  ROS_INFO_ONCE("wall_dist is now: [%2.2f]", wall_dist);

  int count = 0;
  //int tmp = 0;
  while (ros::ok())
  {
    int tmp = 0;
    geometry_msgs::Twist goal;
    if (n.getParamCached("wall_dist", wall_dist)) {
    	ROS_INFO("wall_dist was updated to: [%2.2f]", wall_dist);
    }
    for(float range : wall.ranges){
    	if(range < wall_dist){
		
    		tmp = 1;
    		break;
    	}
    }
    if(tmp == 1){
    	goal.linear.x = -0.5;
    	goal.angular.z = -0.5;
    	tmp = 0;
    	
    }
    else{
    	goal = desire;
    }
    
    //publisher_handle.publish(goal);

    ros::spin();


    loop_rate.sleep();

    ++count;
  }


  return 0;
}

