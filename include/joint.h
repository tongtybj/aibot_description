#ifndef AIBOT_JOINT_H
#define AIBOT_JOINT_H

#include <sstream>

#define ACTUATOR_TYPE_NONE -1
#define ACTUATOR_TYPE_SERVO 1



namespace AIBotHardwareInterface{
	class Joint
	{
		private:
			int mId;
		public:
			double	position;
			double	velocity;
			double	effort;
			double	posCmd;
			double	velCmd;

			std::string name;
			Joint();
			Joint(int id);
			~Joint();
	};
}


#endif
