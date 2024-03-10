#include "control.h"

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
	return (robotMoveQueue[i].size()/50+1+robotGoodsQueue[i].size())*dist;
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
		if(robotGoodsQueue[id].size()<=1)robotGoodsQueue[id].push(g);
	}
}


void robotFindGood(int id){
	/*      机器人找货       */
	auto q = robotGoodsQueue[id];
	Goods g;                                                                                                                                       //从机器人的货物队头拿第一个合法货物
	bool isFind = false;                                                                                                                           //拿到合法货物没有
	while(q.size()){
		g = q.front(); q.pop();
		if(g.deathId-frameId>=Parameter::goodsPermitDeathFrame || g.deathId-frameId>=manhattanDist(robot[id].getPosition(), g.pos)){        //存活时间>=400||存活时间>=人货曼哈顿距离
			isFind = true;
			break;
		}
	}
	if(!isFind){
		//std::cerr << "[error][robortGetGood]couldn't find the suitable good." << std::endl;
		return;
	}
	robot[id].carryGoods(g);
	auto moves = aStar(robot[id].getPosition(), g.pos);                                                                //加载找货指令序列
	while(moves.size()){
		auto m = moves.front(); moves.pop_front();
		robotMoveQueue[id].push_back(m.second);                                                                                       //get指令为-1
	}
	return;
}

void robotFindBerth(int id){
	/*      机器人送货（拿到货找泊位）          */
	int berthId = robot[id].getGoods().berthId;
	auto moves = aStar(robot[id].getPosition(), berth[berthId].getPosition());                                         //加载找泊位指令序列
	while(moves.size()){
		auto m = moves.front(); moves.pop_front();
		robotMoveQueue[id].push_back(m.second<0? -2: m.second);                                                                       //pull指令为-2
	}
	return;
}


void robotMove(){
	for(int i =0;i<10;i++){
		if(robotMoveQueue[i].empty()) continue;
		int front = robotMoveQueue[i].front();
		robotMoveQueue[i].pop_front();
		if(front==-1){
			IO::ROBOT::get(i);
			continue;
		}
		else if(front==-2){
			IO::ROBOT::pull(i);
			continue;
		}
		else IO::ROBOT::move(i,front);
	}
}

