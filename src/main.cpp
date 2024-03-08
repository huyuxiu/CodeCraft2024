#include "const.h"
#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>

int main(){
	IO::init();
	for(frameId;frameId<=15000;){

		IO::readFrame();
		for(int i =0;i<10;i++){
			IO::ROBOT::move(i,frameId%4);
		}
		puts("OK");
		std::fflush(stdout);

	}
}