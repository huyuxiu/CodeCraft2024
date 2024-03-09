#include "model.h"
#include "util.h"

bool moveRobort(Robot robot,int i){
	int new_x = robot.getPosition().x + dx[i];
    int new_y = robot.getPosition().y + dy[i];
    if (!Robort_isCollision(Position(new_x, new_y))){
		map[robot.getPosition().x][robot.getPosition().y] = '.';
		map[new_x][new_y] = 'A';
        return true;
	}
    else return false;
}

int calucateRobotPri(int i,Position goodsPos){
	Position pos = robot[i].hasGoods() ? berth[robot[i].getGoods().berthId].getPosition():robot[i].getPosition();
	int dist = manhattanDist(goodsPos,pos);
	return (robotMoveQueue[i].size()+1+robotGoodsQueue[i].size())*dist;
}

void distributeGoods(int num){
	/*      将货物分配给机器人队列,num为分配个数       */
	while(num--&&!goodsHeap.empty()){
		Goods g = goodsHeap.top();
		goodsHeap.pop();
		if(g.deathId<Parameter::outGoodsHeapSurplusFrame+frameId) continue;
		int robotPri = 1e8;
		int id = 0;
		for(int i = 0;i < 10;i++){
			int p = calucateRobotPri(i,g.pos);
			if(p<robotPri){
				id = i;
				robotPri = p;
			}
		}
		robotGoodsQueue[id].push(g);
	}
}
