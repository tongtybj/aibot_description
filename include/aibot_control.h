#ifndef AIBOT_CONTROL_H
#define AIBOT_CONTROL_H

#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>

namespace AIBotHardwareInterface{
    /// \brief Hardware interface for a robot
    class AIBot : public hardware_interface::RobotHW {
	public:
		AIBot();
		~AIBot();
		void read();
		void write();
	private: 
		// Interfaces
		hardware_interface::JointStateInterface joint_state_interface;
		hardware_interface::PositionJointInterface joint_position_interface;
		double cmd[2];
		double pos[2];
		double vel[2];
		double eff[2];

    }; // class

} // end namespace
#endif