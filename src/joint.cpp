#include <stdlib.h>
#include <math.h>
#include <stdexcept>
#include "ros/ros.h"
#include "joint.h"

#define PI 3.14159

namespace AIBotHardwareInterface{
	Joint::Joint(){
	}
	Joint::Joint(int id,std::string name){
		this->mId = id;
		this->mName = name;
	}
	Joint::~Joint(){
	}

}
