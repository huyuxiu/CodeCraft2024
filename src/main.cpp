#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>

int main(){
	IO::init();
	bool flag2 = false;
	for(frameId;frameId<=15000;){
		IO::readFrame();
		/*     指令序列输出     */
		robotMove();
		puts("OK");
		std::fflush(stdout);
		/*        货物进机器人优先队列       */
		if(frameId%200==0){
			distributeGoods(1);
		}
		for(int i =0;i<10;i++){
			if(!robotMoveQueue[i].empty()) continue;
			if(robot[i].hasGoods()){
				robotFindBerth(i);
			}
			else{
				robotFindGood(i);
			}
		}
		/*      指令序列加入队列       */


	}
}