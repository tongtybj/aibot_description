#include <stdlib.h>
#include <math.h>
#include <stdexcept>
#include "ros/ros.h"
#include "joint.h"

#define PI 3.14159

namespace AIBotHardwareInterface{
	Joint::Joint(){
	}
	Joint::Joint(int id){
		this->mId = id;
	}
	Joint::~Joint(){
	}

}
