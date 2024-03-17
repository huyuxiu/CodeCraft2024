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
	int totalMoney = 0;
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

//			for(int i :aliveRobotId){
//				robot[i].setClassId(berth[robot[i].getBerthId()].getClassId());
//				robot_in_class[robot[i].getClassId()].push_back(i);
//			}
//			balanceRobot();
			distributeRobots();
			flag = false;
		}
		/*      指令进机器人指令队列      */
		for(auto i:aliveRobotId){
			if(!robotMoveQueue[i].empty()) continue;        //指令序列非空跳过
			if(robot[i].hasGoods()){
				robotFindBerth(i);
				totalMoney+=robot[i].getGoods().value;
			}
			else{
				if(robotGoodsQueue[i].empty()) distributeGoods(i);     //给机器人分配货物
				robotFindGood(i);
			}
		}
		/*      指令序列输出      */
		robotMove();
		shipToBerth();
		puts("OK");
		std::fflush(stdout);
		if(frameId==14199) std::clog<<totalMoney<<std::endl;
		if(frameId==14999) std::clog<<totalMoney<<std::endl;
	}

}