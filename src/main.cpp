#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>
#include<cstring>
#include <ctime>
#include "const.h"
#include "util.h"
int main(){
	srand(time(0)); //设置随机种子
	IO::init();
	bool flag = true;
	for(frameId; frameId <= 15000; ){
		IO::readFrame();
		if(flag){   //第一次执行
			for(int i = 0; i < conVar::maxRobot; i++){ //判断机器人死活
				int blockId = getBlockId(robot[i].getPosition());
				robot[i].setBlockId(blockId);
				if(blockId != -1){
					aliveRobotId.push_back(i);
					robot_in_block[blockId].push_back(i);
				}
			}
			distributeRobots();
			flag = false;
		}
		/*      指令序列输出      */
		robotMove();
		shipToBearth();
		puts("OK");
		std::fflush(stdout);
		/*      指令进机器人指令队列      */
		for(auto i:aliveRobotId){
			if(!robotMoveQueue[i].empty()) continue;        //指令序列非空跳过
			if(robot[i].hasGoods()){
				robotFindBerth(i);
			}
			else{
				if(robotGoodsQueue[i].empty()) distributeGoods(i);     //给机器人分配货物
				robotFindGood(i);
			}
		}
	}
}