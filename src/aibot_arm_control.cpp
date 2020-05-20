#include "aibot_arm_control.h"



namespace AIBotHardwareInterface{
	AIBot::AIBot(){
		/**
		 * @brief ROS service 客户端
		 * 
		 */
		mClient = mNodeHandle.serviceClient<lino_msgs::ServoCtrl>("servo_ctrl");


		/**
		 * @brief 初始化joint
		 * 
		 */

		joints[0].mId = 2;
		joints[0].mName = "arm_base_rot_link_joint";

		joints[1].mId = 3;
		joints[1].mName = "arm_first_link_joint";

		joints[2].mId = 4;
		joints[2].mName = "arm_second_motor_link_joint";

		joints[3].mId = 5;
		joints[3].mName = "arm_second_connector_link_joint";

		joints[4].mId = 6;
		joints[4].mName = "arm_second_link_joint";

		joints[5].mId = 7;
		joints[5].mName = "arm_third_link_joint";

		joints[6].mId = 8;
		joints[6].mName = "arm_fourth_link_joint";

		for(int i = 0;i<7;i++){
			joints[i].posCmd = 0;
		}

		/**
		 * @brief joint注册
		 * 
		 */
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_base_rot_link_joint",  &joints[0].position, &joints[0].velocity, &joints[0].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_first_link_joint", &joints[1].position, &joints[1].velocity, &joints[1].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_second_link_joint",  &joints[2].position, &joints[2].velocity, &joints[2].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_third_link_joint", &joints[3].position, &joints[3].velocity, &joints[3].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_fourth_link_joint",  &joints[4].position, &joints[4].velocity, &joints[4].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_second_motor_link_joint",  &joints[5].position, &joints[5].velocity, &joints[5].effort));
		joint_state_interface.registerHandle(hardware_interface::JointStateHandle("arm_second_connector_link_joint",  &joints[6].position, &joints[6].velocity, &joints[6].effort));

		registerInterface(&joint_state_interface);

		joint_position_interface.registerHandle(hardware_interface::JointHandle(joint_state_interface.getHandle("arm_base_rot_link_joint"),  &joints[0].posCmd));
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
			if(joints[i].mName == jointName){
				return joints[i];
			}
		}
	throw std::runtime_error("Could not find joint with name: " + jointName);
	}
	void AIBot::setJoint(Joint joint){
		bool foundJoint = false;
		for (int i = 0; i < 7; i++){
			if(joints[i].mName == joint.mName){
				foundJoint = true;
				joints[i] = joint;
			}
		}
		if (foundJoint == false){
			throw std::runtime_error("Could not find joint with name: " + joint.mName);
		}
	}

	/**
	 * @brief 线程函数
	 * 
	 * @param arg 包含client和srv的结构体
	 * @return void* 
	 */
	void *threadFunction( void *arg) {
		AIBot::myPara *pstru;
		pstru = (struct AIBot::myPara *) arg;

		if(!pstru->tClient.call(pstru->tSrv))
		{
			ROS_ERROR("call failed");
		}

	}

	void AIBot::write(){

		for (int i = 0; i < 7; i++)
		{
			if(joints[i].mName == "arm_base_rot_link_joint")
			ROS_INFO("write write posCmd = %lf ,position = %lf",joints[0].posCmd,joints[0].position);

			mSrv.request.id = i+2;
			mSrv.request.mode = 0;
			mSrv.request.angle = (joints[i].posCmd / 3.14 ) * 180;
			mSrv.request.speed = 100;
			mMyPara.tClient = mClient;
			mMyPara.tSrv = mSrv;
        	int ret_thrd = pthread_create(&mThread, NULL, threadFunction, &mMyPara);

		}
	}
	
	void AIBot::read(){
		//虚拟实现
		for (int i = 0; i < 7; i++)
		{	
			joints[i].position = joints[i].posCmd;
			if(joints[i].mName=="arm_first_link_joint")
			{
				// joints[i].position = 0;
			}
			
		}
		
		
	}


}