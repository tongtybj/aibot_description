#include <ros/ros.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "aibot_arm_demo");

  ros::NodeHandle nodeHandle; 

  ros::AsyncSpinner spinner(1);
  spinner.start();
 
//   ros::shutdown(); 
  return 0;
}