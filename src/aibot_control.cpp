#include "aibot_control.h"


namespace AIBotHardwareInterface{
	AIBot::AIBot(){
		mClient = mNodeHandle.serviceClient<lino_msgs::ServoCtrl>("servo_ctrl");
		joints[0].name = "arm_base_rot_link_joint";
		joints[1].name = "arm_first_link_joint";
		joints[2].name = "arm_second_motor_link_joint";
		joints[3].name = "arm_second_connector_link_joint";
		joints[4].name = "arm_second_link_joint";
		joints[5].name = "arm_third_link_joint";
		joints[6].name = "arm_fourth_link_joint";

	//   - arm_base_link_rot_joint

		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_base_link_rot_joint",  &joints[0].position, &joints[0].velocity, &joints[0].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_first_link_joint", &joints[1].position, &joints[1].velocity, &joints[1].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_second_link_joint",  &joints[2].position, &joints[2].velocity, &joints[2].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_third_link_joint", &joints[3].position, &joints[3].velocity, &joints[3].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_fourth_link_joint",  &joints[4].position, &joints[4].velocity, &joints[4].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_second_motor_link_joint",  &joints[5].position, &joints[5].velocity, &joints[5].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_second_connector_link_joint",  &joints[6].position, &joints[6].velocity, &joints[6].effort));

		registerInterface(&joint_state_interface);

		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_base_link_rot_joint"),  &joints[0].posCmd));
		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_first_link_joint"),  &joints[1].posCmd));
		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_second_link_joint"),  &joints[2].posCmd));
		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_third_link_joint"),  &joints[3].posCmd));
		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_fourth_link_joint"),  &joints[4].posCmd));
		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_second_motor_link_joint"), &joints[5].posCmd));
		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_second_connector_link_joint"),  &joints[6].posCmd));

		registerInterface(&joint_position_interface);
	}
	AIBot::~AIBot(){
	}

	Joint AIBot::getJoint(std::string jointName){
		for (int i = 0; i < 7; i++){
			if(joints[i].name == jointName){
				return joints[i];
			}
		}
	throw std::runtime_error("Could not find joint with name: " + jointName);
	}
	void AIBot::setJoint(Joint joint){
		bool foundJoint = false;
		for (int i = 0; i < 7; i++){
			if(joints[i].name == joint.name){
				foundJoint = true;
				joints[i] = joint;
			}
		}
		if (foundJoint == false){
			throw std::runtime_error("Could not find joint with name: " + joint.name);
		}
	}


	void AIBot::write(){

		ROS_INFO("write write posCmd = %lf ,position = %lf",joints[0].posCmd,joints[0].position);

		for (int i = 0; i < 7; i++)
		{
			mSrv.request.id = i+2;
			mSrv.request.mode = 0;
			mSrv.request.angle = joints[i].posCmd;
			mSrv.request.speed = 100;
			if(!mClient.call(mSrv)){
				ROS_ERROR("Failed to call service");
			}
		}
	}
	
	void AIBot::read(){
		//虚拟实现
		for (int i = 0; i < 7; i++)
		{
			joints[i].position = joints[i].posCmd;
		}
		
		
	}


}