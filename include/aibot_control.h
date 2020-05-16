#ifndef AIBOT_CONTROL_H
#define AIBOT_CONTROL_H

#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>
#include "joint.h"
#include "ros/ros.h"
#include "lino_msgs/ServoCtrl.h"


namespace AIBotHardwareInterface{
    class AIBot : public hardware_interface::RobotHW {
	public:
	  
		AIBot();
		~AIBot();
		ros::NodeHandle mNodeHandle;
		ros::ServiceClient mClient;
		lino_msgs::ServoCtrl mSrv;

		Joint joints[7];
		Joint getJoint(std::string jointName);
		void setJoint(Joint joint);
		void write();
		void read();

	private: 
		hardware_interface::JointStateInterface joint_state_interface;
		hardware_interface::PositionJointInterface joint_position_interface;

    }; 

}
#endif