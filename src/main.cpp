#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>

int main(){
	IO::init();
	bool flag2 = false;
	for(frameId; frameId<=15000; ){
		IO::readFrame();
		/*      指令序列输出      */
		robotMove();
		shipToBearth();
		puts("OK");
		std::fflush(stdout);
		/*      货物进机器人货物队列      */
		if(frameId%200 == 0){
			distributeGoods(10);
		}
		/*      指令进机器人指令队列      */
		for(int i = 0; i < 10; i++){
			if(!robotMoveQueue[i].empty()) continue;        //指令序列非空跳过
			if(robot[i].hasGoods()){
				robotFindBerth(i);
			}
			else{
				robotFindGood(i);
			}
		}

	}
}