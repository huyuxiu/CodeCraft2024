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
		
		/*        货物进机器人优先队列       */
		if(frameId%100==0){
			distributeGoods(15);
		}
		for(int i =0;i<10;i++){
			if(!robotGoodsQueue[i].empty()) continue;
			if(robot[i].hasGoods()){
				robotFindBerth(i);
			}
			else{
				robotFindGood(i);
			}
		}
		/*      指令序列加入队列       */
		shipToBearth();
		puts("OK");
		std::fflush(stdout);
	}
}