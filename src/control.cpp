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

//void shipToBearth() {
//	/*      船和泊位的匹配      */
//	for (int i = 0; i < conVar::maxShip; i++) {
//		if (ship[i].getBerthId() == -1 && ship[i].getStatus() == 1) {            //当船达到虚拟点空闲的时候
//			int temp_max = 0, target_berth = -1;
//			ship[i].setLoaded(0);
//			for (int j = 0; j < conVar::maxBerth; j++) {
//				if (berth[j].getGoods_size() > temp_max && berth[j].getStatus() == 0 && !shipTargetBerth[j]) {      //找物品多的港口
//					temp_max = berth[j].getGoods_size();
//					target_berth = j;
//				}
//			}
//			if (target_berth != -1) {
//				IO::SHIP::ship(i, target_berth);
//				shipTargetBerth[target_berth] = 1;
//			}
//		}
//		else if (ship[i].getStatus() == 1) {                                     //当船到达泊位
//			int current_berth = ship[i].getBerthId();
//			int rest_cap = ship[i].getCapacity() - ship[i].getLoaded();
//			if (berth[current_berth].getGoods_size() && rest_cap && frameId + berth[current_berth].getTransport_time() < 14980) {              //如果泊位还有货物则还需要搬货并且来得及回去
//				int carry_num = berth[current_berth].getGoods_size() > berth[current_berth].getVelocity() ? berth[current_berth].getVelocity() : berth[current_berth].getGoods_size();
//				carry_num = carry_num > rest_cap ? rest_cap : carry_num;        //搬运货物的数量是速度，船剩余容量，泊位货物数量三个中的最小值
//				berth[current_berth].carryGoods(carry_num);
//				berth[current_berth].setStatus(1);
//				int new_load = ship[i].getLoaded() + carry_num;
//				ship[i].setLoaded(new_load);
//			}
//			else {                                                              //已经没有货物可以搬了了要开走了
//				IO::SHIP::go(i);
//				berth[current_berth].setStatus(0);
//				shipTargetBerth[current_berth] = 0;
//			}
//		}
//		else if (ship[i].getStatus() == 2) {
//			int current_berth = ship[i].getBerthId();
//			if (berth[current_berth].getStatus() == 0 && !shipTargetBerth[i]){
//				IO::SHIP::ship(i, current_berth);
//				berth[current_berth].setStatus(1);
//				shipTargetBerth[current_berth] = 1;
//			}
//		}
//	}
//}

void shipModerate(int id) {	//到泊位最多的泊位，船没满继续拿
	if (ship[id].getBerthId() == -1 && ship[id].getStatus() == 1) {            //当船达到虚拟点空闲的时候
		ship[id].setLoaded(0);
		int target_berth = maxGoodsBerth();
		if (target_berth != -1) {
			IO::SHIP::ship(id, target_berth);
			shipTargetBerth[target_berth] = id;
		}
	}
	else if (ship[id].getStatus() == 1) {                                     //当船到达泊位
		int current_berth = ship[id].getBerthId();
		int rest_cap = ship[id].getCapacity() - ship[id].getLoaded();
		if (berth[current_berth].getGoods_size() && rest_cap > 0 && frameId + berth[current_berth].getTransport_time() + maxShipRestTime < 15000) {              //如果泊位还有货物则还需要搬货并且来得及回去
			int carry_num = berth[current_berth].getGoods_size() > berth[current_berth].getVelocity() ? berth[current_berth].getVelocity() : berth[current_berth].getGoods_size();
			carry_num = carry_num > rest_cap ? rest_cap : carry_num;        //搬运货物的数量是速度，船剩余容量，泊位货物数量三个中的最小值
			berth[current_berth].carryGoods(carry_num);
			berth[current_berth].setStatus(1);
			int new_load = ship[id].getLoaded() + carry_num;
			ship[id].setLoaded(new_load);
		}
		else if (rest_cap >= ship[id].getCapacity() / 4 && !berth[current_berth].getGoods_size()) {		//当前港口搬完但是还能搬去其他地方搬
			int temp_max = 1000, target_berth = -1;
			for (int j = 0; j < conVar::maxBerth; j++) {
				if ( abs(berth[j].getGoods_size() - rest_cap) < temp_max && berth[j].getGoods_size() <= rest_cap + 10  && berth[j].getStatus() == 0 && shipTargetBerth[j] == -1 && frameId + 500 + berth[j].getTransport_time() * 3 + 80 < 15000) {      //找物品多的港口   abs(berth[j].getGoods_size() - rest_cap)
					temp_max = abs(berth[j].getGoods_size() - rest_cap);
					target_berth = j;
				}
			}
			if (target_berth != -1) {			//找到能去的
				IO::SHIP::ship(id, target_berth);
				berth[current_berth].setStatus(0);
				shipTargetBerth[target_berth] = id;
				shipTargetBerth[current_berth] = -1;
			}
			else {		//找不到能去的走了
				IO::SHIP::go(id);
				berth[current_berth].setStatus(0);
				shipTargetBerth[current_berth] = -1;
			}
		}
		else {                                                              //已经没有货物可以搬了了要开走了
			IO::SHIP::go(id);
			berth[current_berth].setStatus(0);
			shipTargetBerth[current_berth] = -1;
		}
	}
	else if (ship[id].getStatus() == 2) {
		int current_berth = ship[id].getBerthId();
		if (berth[current_berth].getStatus() == 0 && shipTargetBerth[current_berth] == -1) {
			IO::SHIP::ship(id, current_berth);
			shipTargetBerth[current_berth] = -1;
			berth[current_berth].setStatus(1);
		}
	}
}

void shipFull(int id) {	//到泊位最多的泊位，船没满继续拿
	if (ship[id].getBerthId() == -1 && ship[id].getStatus() == 1) {            //当船达到虚拟点空闲的时候
		ship[id].setLoaded(0);
		int target_berth = maxGoodsBerth();
		if (target_berth != -1) {
			IO::SHIP::ship(id, target_berth);
			shipTargetBerth[target_berth] = id;
		}
	}
	else if (ship[id].getStatus() == 1) {                                     //当船到达泊位
		int current_berth = ship[id].getBerthId();
		int rest_cap = ship[id].getCapacity() - ship[id].getLoaded();
		if (berth[current_berth].getGoods_size() && rest_cap > 0 && frameId + berth[current_berth].getTransport_time() + maxShipRestTime < 15000) {              //如果泊位还有货物则还需要搬货并且来得及回去
			int carry_num = berth[current_berth].getGoods_size() > berth[current_berth].getVelocity() ? berth[current_berth].getVelocity() : berth[current_berth].getGoods_size();
			carry_num = carry_num > rest_cap ? rest_cap : carry_num;        //搬运货物的数量是速度，船剩余容量，泊位货物数量三个中的最小值
			berth[current_berth].carryGoods(carry_num);
			berth[current_berth].setStatus(1);
			int new_load = ship[id].getLoaded() + carry_num;
			ship[id].setLoaded(new_load);
		}
		else if (rest_cap > 0 && !berth[current_berth].getGoods_size()) {		//当前港口搬完但是还能搬去其他地方搬
			int temp_max = 0, target_berth = -1;
			for (int j = 0; j < conVar::maxBerth; j++) {
				if ( berth[j].getGoods_size() > temp_max && berth[j].getStatus() == 0  && shipTargetBerth[j] == -1 && frameId + 500 + berth[j].getTransport_time() + maxShipRestTime < 15000) {      //找物品多的港口   abs(berth[j].getGoods_size() - rest_cap)
					temp_max = berth[j].getGoods_size();
					target_berth = j;
				}
			}
			if (target_berth != -1) {			//找到能去的
				IO::SHIP::ship(id, target_berth);
				berth[current_berth].setStatus(0);
				shipTargetBerth[target_berth] = id;
				shipTargetBerth[current_berth] = -1;
			}
			else if (frameId + berth[current_berth].getTransport_time() + maxShipRestTime > 15000) {		//找不到能去的留一下
				IO::SHIP::go(id);
				berth[current_berth].setStatus(0);
				shipTargetBerth[current_berth] = -1;
			}
		}
		else {                                                              //已经没有货物可以搬了了要开走了
			IO::SHIP::go(id);
			berth[current_berth].setStatus(0);
			shipTargetBerth[current_berth] = -1;
		}
	}
	else if (ship[id].getStatus() == 2) {
		int current_berth = ship[id].getBerthId();
		if (berth[current_berth].getStatus() == 0 && shipTargetBerth[current_berth] == -1) {
			IO::SHIP::ship(id, current_berth);
			shipTargetBerth[current_berth] = -1;
			berth[current_berth].setStatus(1);
		}
	}
}

void shipGreedy(int id) {	//船和泊位的匹配,贪心跑到货物最多的泊位拿完就走
	if (ship[id].getBerthId() == -1 && ship[id].getStatus() == 1) {            //当船达到虚拟点空闲的时候
		int temp_max = 0, target_berth = -1;
		ship[id].setLoaded(0);
		for (int j = 0; j < conVar::maxBerth; j++) {
			if (berth[j].getGoods_size() > temp_max && berth[j].getStatus() == 0 && shipTargetBerth[j] == -1 && frameId + 2 * berth[j].getTransport_time() + maxShipRestTime < 15000) {      //找物品多的港口
				temp_max = berth[j].getGoods_size();
				target_berth = j;
			}
		}
		if (target_berth != -1) {
			IO::SHIP::ship(id, target_berth);
			shipTargetBerth[target_berth] = id;
		}
	}
	else if (ship[id].getStatus() == 1) {                                     //当船到达泊位
		int current_berth = ship[id].getBerthId();
		int rest_cap = ship[id].getCapacity() - ship[id].getLoaded();
		if (berth[current_berth].getGoods_size() && rest_cap && frameId + berth[current_berth].getTransport_time() + maxShipRestTime < 15000) {              //如果泊位还有货物则还需要搬货并且来得及回去
			int carry_num = berth[current_berth].getGoods_size() > berth[current_berth].getVelocity() ? berth[current_berth].getVelocity() : berth[current_berth].getGoods_size();
			carry_num = carry_num > rest_cap ? rest_cap : carry_num;        //搬运货物的数量是速度，船剩余容量，泊位货物数量三个中的最小值
			berth[current_berth].carryGoods(carry_num);
			berth[current_berth].setStatus(1);
			int new_load = ship[id].getLoaded() + carry_num;
			ship[id].setLoaded(new_load);
		}
		else {                                                              //已经没有货物可以搬了了要开走了
			IO::SHIP::go(id);
			berth[current_berth].setStatus(0);
			shipTargetBerth[current_berth] = -1;
		}
	}
	else if (ship[id].getStatus() == 2) {
		int current_berth = ship[id].getBerthId();
		if (berth[current_berth].getStatus() == 0 && shipTargetBerth[id] == -1){
			IO::SHIP::ship(id, current_berth);
			berth[current_berth].setStatus(1);
			shipTargetBerth[current_berth] = id;
		}
	}
}
void shipToBerth() {
	//if (frameId < 1000)	return;
	for (int i = 0; i < conVar::maxShip; i++) {
		if (ship[i].getBerthId() == -1) {
			shipModerate(i);
		}
		else {
			if (berth[ship[i].getBerthId()].getTransport_time() * 3 + frameId + maxShipRestTime < 15000)
				shipModerate(i);
			else
				shipFull(i);
		}
	}
}

void distributeGoods(int id){
	/*      将货物分配给机器人队列       */
	int classId = robot[id].getClassId();
	//std::cout << robot[id].getClassId() << std::endl;
	bool isFind = false;
	while(!isFind&&goodsHeap[classId].size()){
		Goods g = goodsHeap[classId].top();
		goodsHeap[classId].pop();
		goodsTargetBerth[g.berthId]++;
		if(frameId+Parameter::outGoodsHeapSurplusFrame>g.deathId) continue;
		if(g.berthId!=robot[id].getBerthId()){
			//货物和机器人不在一个泊位
			int robotid = findNewRobot(robot[id].getClassId(),g.berthId);
			if(robotid!=-1){
				//给类内其他机器人派活
				robotGoodsQueue[robotid].push(g);
				robot[robotid].carryGoods(g);
			}
			else{
				robotGoodsQueue[id].push(g);
				robot[id].carryGoods(g);
				isFind = true;
			}
		}
		else{
			robotGoodsQueue[id].push(g);
			robot[id].carryGoods(g);
			isFind = true;
		}

	}
	/*     临时找下一个类拿货     */
	if(frameId<1000) return;
	//找到当前类在class_in_block的下标,然后找左右的类
	for(int i = 0;i<class_in_block[robot[id].getBlockId()].size();i++){
		if(class_in_block[robot[id].getBlockId()][i] == classId){
			if(i>0){
				//找左边的类
				while(!isFind&&goodsHeap[class_in_block[robot[id].getBlockId()][i-1]].size()){
					Goods g = goodsHeap[class_in_block[robot[id].getBlockId()][i-1]].top();
					goodsHeap[class_in_block[robot[id].getBlockId()][i-1]].pop();
					if(frameId+Parameter::outGoodsHeapSurplusFrame>g.deathId) continue;
					robotGoodsQueue[id].push(g);
					robot[id].carryGoods(g);
					isFind = true;
					break;
				}
			}
			if(i<class_in_block[robot[id].getBlockId()].size()-1){
				//找左边的类
				while(!isFind&&goodsHeap[class_in_block[robot[id].getBlockId()][i+1]].size()){
					Goods g = goodsHeap[class_in_block[robot[id].getBlockId()][i+1]].top();
					goodsHeap[class_in_block[robot[id].getBlockId()][i+1]].pop();
					if(frameId+Parameter::outGoodsHeapSurplusFrame>g.deathId) continue;
					robotGoodsQueue[id].push(g);
					robot[id].carryGoods(g);
					isFind = true;
					break;
				}
			}
			break;//放弃
		}
	}
}



void robotFindGood(int id) {
	/*      机器人找货       */
	auto q = robotGoodsQueue[id];
	Goods g;//从机器人的货物队头拿第一个合法货物
	bool isFind = false;                                                                                                                           //拿到合法货物没有
	while (robotGoodsQueue[id].size()) {
		g = robotGoodsQueue[id].top();
		robotGoodsQueue[id].pop();
		if (g.berthId == robot[id].getBerthId()) {
			if (frameId + g.berthDist + manhattanDist(robot[id].getPosition(), bestBerth[g.pos.x][g.pos.y].second.second) > g.deathId) continue;
		}
		else if (frameId + Parameter::goodsPermitDeathFrame > g.deathId) continue; //货物和机器人不在一个泊位，不能用距离去估计这个货死了没
		isFind = true;
		break;
	}
	if (!isFind) {
		//std::cerr << "[error][robortGetGood]couldn't find the suitable good." << std::endl;
		return;
	}
	robot[id].carryGoods(g);
	auto moves = aStar(robot[id].getPosition(), g.pos);                                                           //加载找货指令序列
	while (moves.size()) {
		auto m = moves.front(); moves.pop_front();
		robotMoveQueue[id].push_back(m.second);                                                                                                 //get指令为-1
	}
}


void robotFindBerth(int id) {
	/*      机器人送货（拿到货找泊位）          */
	bool isFind = false;//有无可替换（可达）/同一个联通块的泊位
	Goods g = robot[id].getGoods();//要拿的货
	int berthId = robot[id].getGoods().berthId; //找到最优泊位(必定可达)

	if (frameId >= 13000 && !shipTargetBerth[berthId]) {
		int temp_min = 500;
		for (int i = 0; i < conVar::maxBerth; i++) {
			if (shipTargetBerth[i] && getBlockId(g.pos) == getBlockId(berth[i].getPosition()) && manhattanDist(robot[id].getPosition(), berth[i].getPosition()) < temp_min && berth[i].getGoods_size() <= (ship[shipTargetBerth[i]].getCapacity() - ship[shipTargetBerth[i]].getLoaded())) {
				temp_min = manhattanDist(robot[id].getPosition(), berth[i].getPosition());
				berthId = i;
			}
		}
	}
	robot[id].setBerthId(berthId);
	//robot[id].setClassId(berth[berthId].getClassId());
	//TODO 后续判断泊位是否忙碌，忙碌就转为后续泊位
	Position berthPos = bestBerth[g.pos.x][g.pos.y].second.second;
	auto moves = aStar(robot[id].getPosition(), berthPos);                                    //加载找泊位指令序列
	while (moves.size()) {
		auto m = moves.front(); moves.pop_front();
		robotMoveQueue[id].push_back(m.second < 0 ? -2 : m.second);                                                                                 //pull指令为-2
	}
}

/*
void robotFindBerth(int id){
	//      机器人送货（拿到货找泊位）          
	bool isFind = false;//有无可替换（可达）/同一个联通块的泊位
	Goods g = robot[id].getGoods();//要拿的货
	int berthId = robot[id].getGoods().berthId; //找到最优泊位(必定可达)

	if (frameId >= 12000 && shipTargetBerth[berthId] == -1) {
		int temp_min = 1000;
		for (int i = 0; i < conVar::maxBerth; i++) {
			if (shipTargetBerth[i] >= 0 && getBlockId(g.pos) == getBlockId(berth[i].getPosition()) && manhattanDist(robot[id].getPosition(), berth[i].getPosition()) < temp_min && berth[i].getGoods_size() <= (ship[shipTargetBerth[i]].getCapacity() - ship[shipTargetBerth[i]].getLoaded())) {
				temp_min = manhattanDist(robot[id].getPosition(), berth[i].getPosition());
				berthId = i;
			}
		}
		robot[id].setBerthId(berthId);
		robot[id].setClassId(berth[berthId].getClassId());
		//TODO 后续判断泊位是否忙碌，忙碌就转为后续泊位
		Position berthPos = berth[berthId].getPosition();
		berthPos.x += rand() % 4, berthPos.y += rand() % 4;              //泊位增加随机数
		auto moves = aStar(robot[id].getPosition(), berthPos);
	}
                                  //加载找泊位指令序列
	bool isGet = false;
	robot[id].setBerthId(berthId);
	auto moves = bfsTargetBerth(robot[id].getPosition(), berthId, isGet);
	if (isGet) {
		while (moves.size()) {
			auto m = moves.front(); moves.pop_front();
			robotMoveQueue[id].push_back(m.second < 0 ? -2 : m.second);                                                                                 //pull指令为-2
		}
	}
}
*/

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
void robotMove() {
	for (auto i : aliveRobotId) {
		if (robotMoveQueue[i].empty() || !robot[i].getStatus()) continue; //如果当前指令序列为空or发生碰撞跳过

		int front = robotMoveQueue[i].front();
		int new_x = robot[i].getPosition().x + dx[front], new_y = robot[i].getPosition().y + dy[front];
		if (!robotIsCollision(Position(new_x, new_y)))
		{
			robotMap[new_x][new_y] = 1;
			robotMap[new_x - dx[front]][new_y - dy[front]] = 0;
			IO::ROBOT::move(i, front);
			robotMoveQueue[i].pop_front();

			if (robot[i].collision < 2)
				robot[i].collision = 2;

			front = robotMoveQueue[i].front();
			if (front == -1) { //下一步是拿货，拿
				robotMoveQueue[i].pop_front();
				IO::ROBOT::get(i);
			}
			else if (front == -2) { //下一步该拉，拉
				robotMoveQueue[i].pop_front();
				IO::ROBOT::pull(i);
				berth[robot[i].getBerthId()].pullGoods();
			}
		}
		else {
			robotAfterCollision(i);
		}
	}
}


int maxGoodsBerth() {
	int temp_max = 0, target_berth = -1;
	for (int i = 0; i < conVar::maxBerth; i++) {
		if (berth[i].getGoods_size() > temp_max && berth[i].getStatus() == 0 && shipTargetBerth[i] == -1 && frameId + 2 * berth[i].getTransport_time() < 14995) {      //找物品多的港口
			temp_max = berth[i].getGoods_size();
			target_berth = i;
		}
	}
	return target_berth;
}

/*
int maxGoodsBerth() {
	int temp_max = 0, target_berth = -1;
	for (int i = 0; i < conVar::maxBerth; i++) {
		if (berth[i].getGoods_size() > temp_max && berth[i].getStatus() == 0 && shipTargetBerth[i] == -1 && frameId + 2 * berth[i].getTransport_time() < 14995) {      //找物品多的港口
			temp_max = berth[i].getGoods_size();
			target_berth = i;
		}
	}
	if (target_berth == -1) {
		for (int i = 0; i < conVar::maxBerth; i++) {
			if (goodsTargetBerth[i] && berth[i].getStatus() == 0 && shipTargetBerth[i] == -1 && frameId + 2 * berth[i].getTransport_time() < 14995)
				target_berth = i;
		}
	}
	return target_berth;
}
*/


void robotAfterCollision(int id) {
	bool isGet;                                                                    //新的规划是不是可达的
	if (!robot[id].hasGoods()) {
		while (robotMoveQueue[id].size()) {											//清空行动队列
			robotMoveQueue[id].pop_front();
		}
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
	else if (robot[id].collision > 0) {
		robot[id].collision--;
		return;
	}
	else {
		bool isGet = false;
		auto moves = bfsTarget(robot[id].getPosition(), 'B', isGet);
		while (robotMoveQueue[id].size()) {											//清空行动队列
			robotMoveQueue[id].pop_front();
		}
		if (isGet) {
			while (moves.size()) {
				auto m = moves.front(); moves.pop_front();
				robotMoveQueue[id].push_back(m.second < 0 ? -2 : m.second);                                                                                 //pull指令为-2
			}
		}
	}
	if (robotMoveQueue[id].empty() || !robot[id].getStatus()) return;

	int front = robotMoveQueue[id].front(); robotMoveQueue[id].pop_front();
	int new_x = robot[id].getPosition().x + dx[front], new_y = robot[id].getPosition().y + dy[front];
	robotMap[new_x][new_y] = 1;
	robotMap[new_x - dx[front]][new_y - dy[front]] = 0;
	IO::ROBOT::move(id, front);

	front = robotMoveQueue[id].front();
	if (front == -1) { //下一步是拿货，拿
		robotMoveQueue[id].pop_front();
		IO::ROBOT::get(id);
	}
	else if (front == -2) { //下一步该拉，拉
		robotMoveQueue[id].pop_front();
		IO::ROBOT::pull(id);
		berth[robot[id].getBerthId()].pullGoods();
	}
}

/*
void robotAfterCollision(int id) {
	bool isGet;                                                                    //新的规划是不是可达的
	if (!robot[id].hasGoods()) {
		while (robotMoveQueue[id].size()) {											//清空行动队列
			robotMoveQueue[id].pop_front();
		}
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
	else if (robot[id].collision > 0) {
		robot[id].collision--;
		return;
	}
	else {
		bool isGet = false;
		auto moves = bfsTarget(robot[id].getPosition(), 'B', isGet);
		while (robotMoveQueue[id].size()) {											//清空行动队列
			robotMoveQueue[id].pop_front();
		}
		if (isGet) {
			while (moves.size()) {
				auto m = moves.front(); moves.pop_front();
				robotMoveQueue[id].push_back(m.second < 0 ? -2 : m.second);                                                                                 //pull指令为-2
			}
		}
	}
	if (robotMoveQueue[id].empty() || !robot[id].getStatus()) return;

	int front = robotMoveQueue[id].front(); robotMoveQueue[id].pop_front();
	int new_x = robot[id].getPosition().x + dx[front], new_y = robot[id].getPosition().y + dy[front];
	robotMap[new_x][new_y] = 1;
	robotMap[new_x - dx[front]][new_y - dy[front]] = 0;
	IO::ROBOT::move(id, front);

	front = robotMoveQueue[id].front();
	if (front == -1) { //下一步是拿货，拿
		robotMoveQueue[id].pop_front();
		IO::ROBOT::get(id);
	}
	if (map[new_x][new_y] == 'B' && robot[id].hasGoods()) { //下一个位置该拉&&有货，拉
		robotMoveQueue[id] = std::deque<int>();
		IO::ROBOT::pull(id);
		berth[robot[id].getBerthId()].pullGoods();
	}
}
*/

