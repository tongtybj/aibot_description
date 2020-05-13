#include <ros/ros.h>
int main(int argc, char** argv){
	ros::init(argc, argv, "aibot");
	ros::AsyncSpinner spinner(1);
	spinner.start();
	ros::Rate rate(10.0);
	while(ros::ok()){
        ros::Duration(1).sleep();
        ROS_INFO("AIbot ----");
	}
	rate.sleep();
}