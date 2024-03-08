#include "const.h"
#include "iointerface.h"
#include "model.h"
#include "control.cpp"

#include<iostream>

int main(){
	IO::init();
	bool flag2 = false;
	for(frameId;frameId<=15000;){
		IO::readFrame();

		if(!flag2){
			IO::ROBOT::move(0,0);
			IO::ROBOT::move(1,0);
			IO::ROBOT::move(2,0);
			IO::ROBOT::move(3,0);
			flag2 = true;
		}
		puts("OK");
		std::fflush(stdout);

	}
}