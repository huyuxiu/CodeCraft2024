#include "const.h"
#include "robot.h"
#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>
int main(){

	IO::init();
	for(frameId;frameId<=15000;){
		IO::readFrame();
		std::cout<<frameId<<std::endl;
	}
}