#include "model.h"
#include "util.h"
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
	return (robotMoveQueue[i].size()+1+robotGoodsQueue[i].size())*dist;
}

void shipToBearth(){
    /*      船和泊位的匹配      */
    for (int i = 0; i < conVar::maxShip; i++){
        if (ship[i].getBerthId() == -1 && ship[i].getStatus() == 1){            //当船达到虚拟点空闲的时候
            int temp_max = 0, target_bearth = 0;
            for (int j = 0; j < conVar::maxBerth; j++){
                if (berth[j].getGoods_size() > temp_max && berth[j].getStatus() == 0){      //找物品多的港口
                    temp_max = berth[j].getGoods_size();
                    target_bearth = j;
                }
            }
            IO::SHIP::ship(i, target_bearth);
        }
        else if (ship[i].getStatus() == 1){                                     //当船到达泊位
            int current_berth = ship[i].getBerthId();
            int rest_cap = ship[i].getCapacity() - ship[i].getLoaded();
            if (berth[current_berth].getGoods_size() && rest_cap){              //如果泊位还有货物则还需要搬货
                int carry_num = berth[current_berth].getGoods_size() > berth[current_berth].getVelocity() ? berth[current_berth].getVelocity() : berth[current_berth].getGoods_size();
                carry_num = carry_num > rest_cap ? rest_cap : carry_num;        //搬运货物的数量是速度，船剩余容量，泊位货物数量三个中的最小值
                berth[current_berth].carryGoods(carry_num);
                berth[current_berth].setStatus(1);
                int new_load = ship[i].getLoaded() + carry_num;
                ship[i].setLoaded(new_load);
            }
            else {                                                              //已经没有货物可以搬了了要开走了
                IO::SHIP::go(i);
                berth[current_berth].setStatus(0);
            }
        }
        else if (ship[i].getStatus() == 2){
            int current_berth = ship[i].getBerthId();
            if (berth[i].getStatus() == 0)
                IO::SHIP::ship(i, current_berth);
        }
    }
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
		std::cerr << "[error][robortGetGood]couldn't find the suitable good." << std::endl;
		return;
	}
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

