#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>
#include "const.h"
#include "util.h"
int main(){
	IO::init();
	bool flag = true;
	for(frameId; frameId<=15000; ){
		IO::readFrame();
		if(flag){
			for(int i=0;i<conVar::maxRobot;i++){
				int blockId = getBlockId(robot[i].getPosition());
				robot[i].setBlockId(blockId);
				if(blockId!=-1){
					aliveRobotId.push_back(i);
				}
			}
			flag = false;
		}

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
		for(auto i:aliveRobotId){
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