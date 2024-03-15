#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>
#include<cstring>
#include <ctime>
#include "const.h"
#include "util.h"
int main(){
	// 设置随机种子
	srand(time(0));
	IO::init();
	bool flag = true;
	for(frameId; frameId<=15000; ){
		memset(robotMap,0,sizeof robotMap);
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
		shipToBerth();
		puts("OK");
//		for (int i = 0; i < conVar::maxBerth; i++)
//			std::clog << berth[i].getGoods_size() <<" ";
//		std::clog << std::endl;
		std::fflush(stdout);
		/*      货物进机器人货物队列      */

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