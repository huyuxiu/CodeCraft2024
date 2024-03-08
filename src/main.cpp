#include "const.h"
#include "iointerface.h"
int main(){
	std::cout<<1<<std::endl;
	IO::init();
	for(frameId;frameId<15000;){
		IO::readFrame();
		std::cout<<frameId<<std::endl;
	}
}