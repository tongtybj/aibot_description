#ifndef AIBOT_HARDWARE_H
#define AIBOT_HARDWARE_H

#include <sstream>
#include <joint.h>

namespace AIBotHardwareInterface{
	class AIBotHardware{
		private:
		public:
			AIBotHardware();
			~AIBotHardware();
			Joint joints[2];
			Joint getJoint(std::string jointName);
			void setJoint(Joint joint);
	};

}
#endif
