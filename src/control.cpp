#include "model.h"
#include "util.h"
#include "control.h"


//
//void shipToBearth() {
//
//	for (int i = 0; i < conVar::maxShip; i++) {
//		if (ship[i].getBerthId() == -1 && ship[i].getStatus() == 1) {            //当船达到虚拟点空闲的时候
//			ship[i].setLoaded(0);
//			int target_berth = maxGoodsBerth();
//			if (target_berth != -1) {
//				IO::SHIP::ship(i, target_berth);
//				shipTargetBerth[target_berth] = 1;
//			}
//		}
//		else if (ship[i].getStatus() == 1) {                                     //当船到达泊位
//			int current_berth = ship[i].getBerthId();
//			int rest_cap = ship[i].getCapacity() - ship[i].getLoaded();
//			if (berth[current_berth].getGoods_size() && rest_cap && frameId + berth[current_berth].getTransport_time() + 1 < 15000) {              //如果泊位还有货物则还需要搬货并且来得及回去
//				int carry_num = berth[current_berth].getGoods_size() > berth[current_berth].getVelocity() ? berth[current_berth].getVelocity() : berth[current_berth].getGoods_size();
//				carry_num = carry_num > rest_cap ? rest_cap : carry_num;        //搬运货物的数量是速度，船剩余容量，泊位货物数量三个中的最小值
//				berth[current_berth].carryGoods(carry_num);
//				berth[current_berth].setStatus(1);
//				int new_load = ship[i].getLoaded() + carry_num;
//				ship[i].setLoaded(new_load);
//			}
//			else if (rest_cap && !berth[current_berth].getGoods_size()) {		//当前港口搬完但是还能搬去其他地方搬
//				int temp_max = 0, target_berth = -1;
//				for (int j = 0; j < conVar::maxBerth; j++) {
//					if (berth[j].getGoods_size() > temp_max && berth[j].getStatus() == 0 && !shipTargetBerth[j] && frameId + 500 + berth[j].getTransport_time() < 15000) {      //找物品多的港口
//						temp_max = berth[j].getGoods_size();
//						target_berth = j;
//					}
//				}
//				if (target_berth != -1) {
//					IO::SHIP::ship(i, target_berth);
//					berth[current_berth].setStatus(0);
//					shipTargetBerth[target_berth] = 1;
//					shipTargetBerth[current_berth] = 0;
//				}
//			}
//			else {                                                              //已经没有货物可以搬了了要开走了
//				IO::SHIP::go(i);
//				berth[current_berth].setStatus(0);
//				shipTargetBerth[current_berth] = 0;
//			}
//		}
//		else if (ship[i].getStatus() == 2) {
//			int current_berth = ship[i].getBerthId();
//			if (berth[current_berth].getStatus() == 0 && !shipTargetBerth[current_berth]) {
//				IO::SHIP::ship(i, current_berth);
//				shipTargetBerth[current_berth] = 0;
//				berth[current_berth].setStatus(1);
//			}
//		}
//	}
//}

void shipToBearth() {
	/*      船和泊位的匹配      */
	for (int i = 0; i < conVar::maxShip; i++) {
		if (ship[i].getBerthId() == -1 && ship[i].getStatus() == 1) {            //当船达到虚拟点空闲的时候
			int temp_max = 0, target_berth = -1;
			ship[i].setLoaded(0);
			for (int j = 0; j < conVar::maxBerth; j++) {
				if (berth[j].getGoods_size() > temp_max && berth[j].getStatus() == 0 && !shipTargetBerth[j]) {      //找物品多的港口
					temp_max = berth[j].getGoods_size();
					target_berth = j;
				}
			}
			if (target_berth != -1) {
				IO::SHIP::ship(i, target_berth);
				shipTargetBerth[target_berth] = 1;
			}
		}
		else if (ship[i].getStatus() == 1) {                                     //当船到达泊位
			int current_berth = ship[i].getBerthId();
			int rest_cap = ship[i].getCapacity() - ship[i].getLoaded();
			if (berth[current_berth].getGoods_size() && rest_cap && frameId + berth[current_berth].getTransport_time() < 14980) {              //如果泊位还有货物则还需要搬货并且来得及回去
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
				shipTargetBerth[current_berth] = 0;
			}
		}
		else if (ship[i].getStatus() == 2) {
			int current_berth = ship[i].getBerthId();
			if (berth[current_berth].getStatus() == 0 && !shipTargetBerth[i]){
				IO::SHIP::ship(i, current_berth);
				berth[current_berth].setStatus(1);
				shipTargetBerth[current_berth] = 1;
			}
		}
	}
}
void distributeGoods(int id){
	/*      将货物分配给机器人队列       */

}



void robotFindGood(int id){
	/*      机器人找货       */
	auto q = robotGoodsQueue[id];
	Goods g;//从机器人的货物队头拿第一个合法货物
	berth[robot[id].getBerthId()].presure--;//减轻泊位压力
	bool isFind = false;                                                                                                                           //拿到合法货物没有
	while(robotGoodsQueue[id].size()){
		g = robotGoodsQueue[id].front();
		robotGoodsQueue[id].pop();
		isFind = true;
		break;
	}
	if(!isFind){
		//std::cerr << "[error][robortGetGood]couldn't find the suitable good." << std::endl;
		return;
	}
	robot[id].carryGoods(g);
	auto moves = aStar(robot[id].getPosition(), g.pos);                                                           //加载找货指令序列
	while(moves.size()){
		auto m = moves.front(); moves.pop_front();
		robotMoveQueue[id].push_back(m.second);                                                                                                 //get指令为-1
	}
}

void robotFindBerth(int id){
	/*      机器人送货（拿到货找泊位）          */
	bool isFind = false;//有无可替换（可达）/同一个联通块的泊位
	Goods g = robot[id].getGoods();//要拿的货
	int i= 0;//第i优的泊位
	int berthId = robot[id].getGoods().berthId; //找到最优泊位(必定可达)
	robot[id].setBerthId(berthId);
	berth[berthId].presure++;//给泊位上压力

	//TODO 后续判断泊位是否忙碌，忙碌就转为后续泊位

    Position berthPos = berth[berthId].getPosition();
    berthPos.x+=rand() % 4,berthPos.y+=rand() % 4;              //泊位增加随机数
	auto moves = aStar(robot[id].getPosition(), berthPos);                                    //加载找泊位指令序列
	while(moves.size()){
		auto m = moves.front(); moves.pop_front();
		robotMoveQueue[id].push_back(m.second<0? -2: m.second);                                                                                 //pull指令为-2
	}
}

//void robotMove(){
//	for(auto i :aliveRobotId){
//		if(robotMoveQueue[i].empty() ) continue;                                                                           //如果当前指令序列为空or发生碰撞跳过
//
//		int front = robotMoveQueue[i].front(); robotMoveQueue[i].pop_front();                                                                      //取出队头指令
//		IO::ROBOT::move(i,front);                                                                                                      //执行move指令
//
//		if(!robotMoveQueue[i].empty()){                                                                                                            //如果下一操作是get/pull，一起执行
//			front = robotMoveQueue[i].front();
//			if(front == -1){
//				robotMoveQueue[i].pop_front();
//				IO::ROBOT::get(i);
//				continue;
//			}else if(front == -2){
//				robotMoveQueue[i].pop_front();
//				IO::ROBOT::pull(i);
//				berth[robot[i].getGoods().berthId].pullGoods();
//				continue;
//			}
//		}
//	}
//}
//
void robotMove(){
	for(auto i :aliveRobotId){
		if(robotMoveQueue[i].empty() || !robot[i].getStatus()) continue;                                                                           //如果当前指令序列为空or发生碰撞跳过

		int front = robotMoveQueue[i].front();
		robotMoveQueue[i].pop_front();                                                                      //取出队头指令
		if(front == -1){
			IO::ROBOT::get(i);
			robot[i].setCarry(1);
		}
		else if(front == -2){
			IO::ROBOT::pull(i);
			berth[robot[i].getBerthId()].pullGoods();
			robot[i].setCarry(0);
		}//执行move指令
		else{
			int new_x = robot[i].getPosition().x + dx[front];
			int new_y = robot[i].getPosition().y + dy[front];
			if (!robotIsCollision(Position(new_x, new_y)))
			{
				robotMap[new_x][new_y] = 1;
				robotMap[new_x - dx[front]][new_y - dy[front]] = 0;
				IO::ROBOT::move(i, front);
			}
			else {
				robotAfterCollision(i);
			}
		}
	}
}

int maxGoodsBerth() {
	int temp_max = 0, target_berth = -1;
	for (int i = 0; i < conVar::maxBerth; i++) {
		if (berth[i].getGoods_size() > temp_max && berth[i].getStatus() == 0 && !shipTargetBerth[i] && frameId + 2 * berth[i].getTransport_time() < 15000) {      //找物品多的港口
			temp_max = berth[i].getGoods_size();
			target_berth = i;
		}
	}
	return target_berth;
}


void robotAfterCollision(int id) {
	while (robotMoveQueue[id].size()) {
		robotMoveQueue[id].pop_front();
	}
	bool isGet;																	//新的规划是不是可达的
	if (!robot[id].hasGoods()) {
		auto moves = aStar2(robot[id].getPosition(), robot[id].getGoods().pos, isGet);
		if (!isGet) {
			robot[id].setCarry(0);
			//robotGoodsQueue[id].pop();
			return;
		}
		while (moves.size()) {
			auto m = moves.front(); moves.pop_front();
			robotMoveQueue[id].push_back(m.second);                                                                                                 //get指令为-1
		}
	}
	else {
		auto moves = bfsTarget(robot[id].getPosition(), 'B');
		while (moves.size()) {
			auto m = moves.front(); moves.pop_front();
			robotMoveQueue[id].push_back(m.second < 0 ? -2 : m.second);                                                                                 //pull指令为-2
		}
	}
	if (robotMoveQueue[id].empty() || !robot[id].getStatus()) return;
	int front = robotMoveQueue[id].front();
	robotMoveQueue[id].pop_front();                                                                      //取出队头指令
	if (front == -1) {
		IO::ROBOT::get(id);
	}
	else if (front == -2) {
		IO::ROBOT::pull(id);
		berth[robot[id].getGoods().berthId].pullGoods();
	}//执行move指令
	else {
		int new_x = robot[id].getPosition().x + dx[front];
		int new_y = robot[id].getPosition().y + dy[front];
		robotMap[new_x][new_y] = 1;
		robotMap[new_x - dx[front]][new_y - dy[front]] = 0;
		IO::ROBOT::move(id, front);
	}
}