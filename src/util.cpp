#include "util.h"


int manhattanDist(Position pos1,Position pos2){
	return abs(pos1.x-pos2.x)+abs(pos1.y-pos2.y);
}

bool isCollision(Position pos){
	return map[pos.x][pos.y] == '*' || map[pos.x][pos.y] == '#';
}

bool robotIsCollision(Position pos){
	return map[pos.x][pos.y] == '*' || map[pos.x][pos.y] == '#' || robotMap[pos.x][pos.y]==1;
}

std::deque<PPI> aStar(Position start, Position end) {
	/*
	 * 返回std::pair<Position, int>(坐标, 该坐标下一步操作方向)
	 * */
    std::deque<PPI> res;
    if (start.x == end.x && start.y == end.y) return res;

    std::unordered_map<Position, int,PositionHash> dist;                                                         //某一点到起点的真实距离
    std::unordered_map<Position, PPI> prev;                                                                      //某一点是从哪个点走过来的及操作
    std::priority_queue<PIP, std::vector<PIP>, Compare> heap;                                                    //小根堆 (估价, 坐标)
    heap.push({manhattanDist(start, end), start});


    while (heap.size()) {
        auto t = heap.top();
        heap.pop();

        Position ver = t.second;                                                                                 //估价最小坐标
        if (ver.x == end.x && ver.y == end.y) break;

        for (int i = 0; i < 4; i++) {
            Position p(ver.x + dx[i], ver.y + dy[i]);
            if (p.x < 0 || p.x > conVar::maxX || p.y < 0 || p.y > conVar::maxY) continue;                        //地图越界
            if (isCollision(p)) continue;
            if (!dist.count(p) || dist[p] > dist[ver] + 1) {                                                  //第一次遍历or距离更短
                dist[p] = dist[ver] + 1;
                prev[p] = {ver, i};
                heap.push({dist[p] + manhattanDist(p, end), p});
            }
        }
    }
	res.push_front({end, -1});
    while (end.x != start.x || end.y != start.y) {
        res.push_front(prev[end]);
        end = prev[end].first;
    }
    return res;
}
int priorityGoodsBerthSHip(Goods good,Berth berth){
	/*     货物-泊点优先函数     */
	return berth.getTransport_time()+manhattanDist(good.pos,berth.getPosition());
}

void floodFill(Position startPos,int blockId){
	int hh = 0, tt  = 0;
	Position q[(conVar::maxX+1)*(conVar::maxY+1)];   // 数组模拟队列
	q[0] = {startPos.x, startPos.y};
	block[startPos.x][startPos.y] = blockId;
	while(hh <= tt){
		Position t = q[hh++];    // 取下队头

		for(int i = 0;i<4;i++){
			int x = t.x+dx[i],y = t.y+dy[i];
			if(x == t.x && y == t.y) continue;  // 起点
			if(x < 0 || x > conVar::maxX || y < 0 || y > conVar::maxY)  continue;   // 越界
			if(map[x][y] == '*'||map[x][y] == '#' || block[x][y]!=-1) continue;    // 不含雨水||已经遍历过

			q[++tt] = {x, y};   // 入队
			block[x][y] = blockId;
		}
	}
}

int getBlockId(Position pos){
	return block[pos.x][pos.y];
}

void bfsBerth(Position start, int dist[conVar::maxX+5][conVar::maxY+5]) {
	std::queue<Position> q;
	q.push(start);
	dist[start.x][start.y] = 0;

	while (!q.empty()) {
		auto node = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = node.x + dx[i];
			int ny = node.y + dy[i];
			if(isCollision(Position(nx,ny))) continue;// 判断新位置是否合法
			if(nx<0||nx>conVar::maxX||ny<0||ny>conVar::maxY) continue;

			if (dist[nx][ny] == -1) {
				dist[nx][ny] = dist[node.x][node.y] + 1;
				q.push({nx, ny});
			}
		}
	}
}



double calPriorityGoodsBerth(Goods g){
	/*      通过距离和价格计算得到节点优先级       */
	return double(g.value)-2*double(g.berthDist);
}

std::deque<PPI> aStar2(Position start, Position end, bool &isGet) {
	/*
	 * 返回std::pair<Position, int>(坐标, 该坐标下一步操作方向)
	 * */
	std::deque<PPI> res;
	if (start.x == end.x && start.y == end.y) return res;

	std::unordered_map<Position, int, PositionHash> dist;                                                         //某一点到起点的真实距离
	std::unordered_map<Position, PPI> prev;                                                                      //某一点是从哪个点走过来的及操作
	std::priority_queue<PIP, std::vector<PIP>, Compare> heap;                                                    //小根堆 (估价, 坐标)
	heap.push({ manhattanDist(start, end), start });
	int sum = 0;
	isGet = false;

	while (heap.size()) {
		sum++;
		if (sum > 300) {
			isGet = false;
			break;
		}
		auto t = heap.top();
		heap.pop();

		Position ver = t.second;                                                                                 //估价最小坐标
		if (ver.x == end.x && ver.y == end.y) {
			isGet = true;
			break;
		}

		for (int i = 0; i < 4; i++) {
			Position p(ver.x + dx[i], ver.y + dy[i]);
			if (p.x < 0 || p.x > conVar::maxX || p.y < 0 || p.y > conVar::maxY) continue;                        //地图越界
			if (robotIsCollision(p)) continue;                                                                   //碰撞检测
			if (!dist.count(p) || dist[p] > dist[ver] + 1) {                                                  //第一次遍历or距离更短
				dist[p] = dist[ver] + 1;
				prev[p] = { ver, i };
				heap.push({ dist[p] + manhattanDist(p, end), p });
			}
		}
	}
	res.push_front({ end, -1 });
	if (isGet) {
		while (end.x != start.x || end.y != start.y) {
			res.push_front(prev[end]);
			end = prev[end].first;
		}
	}
	return res;
}

std::deque<PPI> bfsTarget(Position startPos, char target, bool &isGet) {
	std::deque<PPI> res;
	std::queue<Position>q;
	std::unordered_map<Position, PPI> prev;
	std::unordered_map<Position, bool> visitited;
	visitited[startPos] = true;

	isGet = false;
	Position end;
	q.push(startPos);

	while (q.size()) {
		Position current_position = q.front();
		q.pop();
		if (map[current_position.x][current_position.y] == target) {
			isGet = true;
			end = current_position;
			break;
		}
		for (int i = 0; i < 4; i++) {
			Position next_position(current_position.x + dx[i], current_position.y + dy[i]);
			if (next_position.x < 0 || next_position.x > conVar::maxX || next_position.y < 0 || next_position.y > conVar::maxY) continue;                        //地图越界
			if (robotIsCollision(next_position) || visitited[next_position]) continue;                                                                 //碰撞检测
			visitited[next_position] = true;
			prev[next_position] = {current_position, i};
			q.push(next_position);
		}
	}
	res.push_front({ end, -1 });
	if (isGet) {
		while (end.x != startPos.x || end.y != startPos.y) {
			res.push_front(prev[end]);
			end = prev[end].first;
		}
	}
	return res;
}

void multiSourceBFS() {
	/*     多源bfs给地图上每个点分配一个泊位(更新bestBerth)     */
	for (int i = 0; i <= conVar::maxX; ++i) {
		for (int j = 0; j <= conVar::maxY; ++j) {
			bestBerth[i][j] = { -1,-1 };
		}
	}
	std::queue<Position> q;
	for (int i = 0; i < conVar::maxBerth; i++) {
		Position p = berth[i].getPosition();
		bestBerth[p.x][p.y].first = i;
		bestBerth[p.x][p.y].second = 0;
		q.push(p);
		berthArea[i] = 1;
	}
	while (!q.empty()) {
		Position t = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int a = t.x + dx[i];
			int b = t.y + dy[i];
			if (a<0 || a>conVar::maxX || b<0 || b>conVar::maxY) continue;
			if (isCollision(Position(a, b))) continue;
			if (bestBerth[a][b].first != -1) continue;
			bestBerth[a][b].first = bestBerth[t.x][t.y].first;
			bestBerth[a][b].second = bestBerth[t.x][t.y].second + 1;
			q.push(Position(a, b));
			if (bestBerth[a][b].second < Parameter::maxFoot) berthArea[bestBerth[t.x][t.y].first]++;
		}
	}
}


/*      roll点版本     */
//void clusteringBerth(){
//	std::unordered_map<int, std::vector<int>> berth_in_block; // blockid:包含的泊位id
//	int cnt = 0; // class个数
//	for (int i = 0; i < conVar::maxBerth; i++) {
//		berth_in_block[berth[i].getBlockId()].push_back(i);
//	}
//	for (auto p : berth_in_block) {
//		auto q = p.second;
//		if (q.size() > 2) { // 需要再分类
//			int k = std::ceil(q.size() / 2); // 需要分成的类数
//			int max_iterations = 100;
//			std::unordered_map<int, std::vector<int>> res; // 中心，泊位id
//			/*      kmeans聚类        */
//			std::vector<int> cx, cy; // 初始化k个中心
//
//			// 使用K-means++算法选择初始聚类中心
//			std::vector<int> indices(q.size());
//			std::iota(indices.begin(), indices.end(), 0); // 生成0到q.size()-1的序列
//			std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device{}())); // 打乱序列
//			for (int i = 0; i < k; i++) {
//				cx.push_back(berth[q[indices[i]]].getPosition().x);
//				cy.push_back(berth[q[indices[i]]].getPosition().y);
//			}
//
//			for (int i = 0; i < max_iterations; i++) { // 迭代
//				res.clear();
//				for (int j = 0; j < q.size(); j++) { // 分配每个样本到最近的中心
//					int min = 0, min_dist = 1e8, dist;
//					for (int s = 0; s < k; s++) {
//						dist = manhattanDist(berth[q[j]].getPosition(), Position(cx[s], cy[s]));
//						if (dist < min_dist) min_dist = dist, min = s;
//					}
//					res[min].push_back(q[j]);
//				}
//
//				for (int s = 0; s < k; s++) { // 更新聚类中心
//					cx[s] = 0, cy[s] = 0;
//					for (auto b : res[s]) cx[s] += berth[b].getPosition().x, cy[s] += berth[b].getPosition().y;
//					cx[s] /= res[s].size(), cy[s] /= res[s].size();
//				}
//			}
//
//			for (int s = 0; s < k; s++) {
//				for (auto b : res[s]) berth[b].setClassId(cnt);
//				cnt++;
//			}
//		} else {
//			for (auto b : q) berth[b].setClassId(cnt);
//			cnt++;
//		}
//	}
//}

std::unordered_map<int, std::vector<int>> kmeans(int k, std::vector<int> q) {
	/*
	 * 对q(berths)进行kmeans聚类，分成k个类。
	 * */
	std::unordered_map<int, std::vector<int>> center_berth; //中心:berthid
	if (q.size() > 2) {
		int max_iterations = k < 4 ? 50 : 100;
		std::vector<int> cx, cy; //初始化k个中心
		for (int i = 0; i < k; i++) {
			cx.push_back(berth[q[1 + i * q.size() / k]].getPosition().x);
			cy.push_back(berth[q[1 + i * q.size() / k]].getPosition().y);
		}
		for (int i = 0; i < max_iterations; i++) { //迭代
			center_berth.clear();
			for (int j = 0; j < q.size(); j++) { //分配每个样本到最近的中心
				int min = 0, min_dist = 1e8, dist;
				for (int s = 0; s < k; s++) {
					dist = manhattanDist(berth[q[j]].getPosition(), Position(cx[s], cy[s]));
					if (dist < min_dist) min_dist = dist, min = s;
				}
				center_berth[min].push_back(q[j]);
			}

			for (int s = 0; s < k; s++) { //更新聚类中心
				cx[s] = 0, cy[s] = 0;
				for (auto b : center_berth[s]) cx[s] += berth[b].getPosition().x, cy[s] += berth[b].getPosition().y;
				cx[s] /= center_berth[s].size(), cy[s] /= center_berth[s].size();
			}
		}
	}
	else {
		for (int i = 0; i < q.size(); i++) {
			std::vector<int> res;
			res.push_back(q[i]);
			center_berth[i] = res;
		}
	}
	return center_berth;
}


void clusteringBerth() {
	for (int i = 0; i < conVar::maxBerth; i++) {
		berth_in_block[berth[i].getBlockId()].push_back(i);
	}
	for (auto p : berth_in_block) { //遍历连通块
		auto q = p.second;
		if (q.size() > 2) { //连通块内的泊位>2，需要再分类
			int k = std::ceil(q.size() / 2.0);
			auto center_berth = kmeans(k, q);
			bool isOK = false;


			while (!isOK) {
				//计算面积并判断是否需要继续分类
				isOK = true;
				double total_area = 0;
				std::unordered_map<int, double> class_area;
				for (auto [cid, berths] : center_berth) {
					for (auto b : berths) class_area[cid] += berthArea[b], total_area += berthArea[b];
				}
				for (auto [cid, berths] : center_berth) {
					std::clog << cid << " " << class_area[cid] / total_area << std::endl;
					if (berths.size() >= Parameter::max_berth_size && class_area[cid] / total_area > Parameter::max_area)  isOK = false;
				}
				if (isOK) break;

				//继续分类
				std::unordered_map<int, std::vector<int>> add_res;
				std::vector<int> erase_res_id;
				for (auto [cid, berths] : center_berth) {
					if (berths.size() >= Parameter::max_berth_size && class_area[cid] / total_area > Parameter::max_area) {
						int k_new = berths.size() == 2 ? 2 : std::ceil(berths.size() / 2.0);
						auto res = kmeans(k_new, berths);
						for (int i = 0; i < k_new; i++) {
							add_res[k++] = res[i];
						}
						erase_res_id.push_back(cid);
					}
				}
				for (auto i : erase_res_id) center_berth.erase(i);
				for (auto [cid, berths] : add_res) center_berth[cid] = berths;
			}

			for (auto [cid, berths] : center_berth) {
				for (auto b : berths) {
					berth[b].setClassId(totalClass);
					berthInCenter[totalClass].push_back(b);
				}
				class_in_block[p.first].push_back(totalClass++);
			}
		}
		else {
			for (auto b : q) {
				berth[b].setClassId(totalClass);
				berthInCenter[totalClass].push_back(b);
			}
			class_in_block[p.first].push_back(totalClass++);
		}
	}
}

int findNewRobot(int classId,int berthId){
	for(int i : robot_in_class[classId]) {
		if (robotGoodsQueue[i].size() < Parameter::maxRobotGoodsQueue && robot[i].getBerthId()==berthId) {
			return i;
		}
	}
	return -1;
}
void calCenterPos(){
	for(int i = 0; i < totalClass; i++){
		Position p(0,0);
		for(int j = 0; j < berthInCenter[i].size(); j++){
			p.x += berth[berthInCenter[i][j]].getPosition().x;
			p.y += berth[berthInCenter[i][j]].getPosition().y;
		}
		p.x /= berthInCenter[i].size();
		p.y /= berthInCenter[i].size();
		classCenterPos[i] = p;
	}
}



void balanceRobot(){
	for(int i =0;i<maxBlockId;i++){

		bool flag = true;
		while(flag){
			int minClass = class_in_block[i][0],maxClass = class_in_block[i][0],minSize = 1e8,maxSize = 0;
			for(int j = 0;j<class_in_block[i].size();j++){
				flag = false;

				int classId = class_in_block[i][j];
				if(robot_in_class[classId].size()<minSize&&robot_in_class[classId].size()<berthInCenter[classId].size()){
					minSize = robot_in_class[classId].size();
					minClass = classId;
					flag = true;
				}
				if(robot_in_class[classId].size()>maxSize&&robot_in_class[classId]>berthInCenter[classId]){
					maxClass = classId;
					maxSize = robot_in_class[classId].size();
				}
			}
			//交换
			if(robot_in_class[maxClass].size()>0){
				robot[robot_in_class[maxClass][0]].setClassId(minClass);
				robot_in_class[maxClass].erase(robot_in_class[maxClass].begin());
				robot_in_class[minClass].push_back(robot_in_class[maxClass][0]);
			}



		}


	}
}

void getStarBerth(){
	for(int c = 0;c<totalClass;c++){
		int maxVelocity = 0;
		int starId = 0;
		for(int b:berthInCenter[c]){
			if(berth[b].getVelocity()>maxVelocity){
				starId = b;
				maxVelocity = berth[b].getVelocity();
			}
		}
		starBerth.insert({c, starId});
	}
}

struct CompareDouble {
	bool operator()(const double& d1, const double& d2) const {
		return d1 > d2;
	}
};

void distributeRobots(){
	for(int b = 0; b < maxBlockId; b++){ //遍历每个连通块
		auto berthss = berth_in_block[b]; //连通块里的泊位id
		//计算类面积，确定每个类要分配的机器人数量
		int robot_number = robot_in_block[b].size(), rest_robot_number = robot_in_block[b].size();
		double total_area = 0;
		std::unordered_map<int, double> class_area; //类id:类面积
		std::multimap<double, int, CompareDouble> class_area_sort; //未分配的比重:类id
		std::unordered_map<int, std::pair<int, bool>> class_robot_number; //类id:类机器人数, 是否已满足硬需求（最少分配一个）
		for(int ber:berthss){
			class_area[berth[ber].getClassId()] += berthArea[ber];
			total_area += berthArea[ber];
		}
		for(auto p:class_area){ //首次分配
			int res = std::min(std::max(int(robot_number * p.second / total_area), 1), rest_robot_number);
			class_robot_number[p.first] = {res, false};
			rest_robot_number -= res; //剩下几个可以分

			double rest = p.second / total_area - res / robot_number; //还有多少比重未分配
			if(rest != 0) class_area_sort.insert({rest, p.first});
		}
		if(rest_robot_number != 0){ //二次分配
			for(auto [area, cid]:class_area_sort){
				if(rest_robot_number == 0) break;
				class_robot_number[cid].first ++;
				rest_robot_number --;
			}
		}


		//初始化分配机器人到最佳泊位
		std::unordered_set<int> free_robots; //闲人id
		std::unordered_map<int, std::pair<int, int>> berth_robot; //berthid：分配的机器人id,距离
		for(int r:robot_in_block[b]){ //遍历连通块里的机器人竞争最佳泊位（泊位选机器人
			free_robots.insert(r);
			auto best_berth = bestBerth[robot[r].getPosition().x][robot[r].getPosition().y];
			if(!berth_robot.count(best_berth.first) || berth_robot[best_berth.first].second > best_berth.second) berth_robot[best_berth.first] = {r, best_berth.second};
		}
		for(auto best_pair:berth_robot){ //分配竞争到最佳泊位的机器人到类里
			robot_in_class[berth[best_pair.first].getClassId()].push_back(best_pair.second.first);
			class_robot_number[berth[best_pair.first].getClassId()].first --;
			class_robot_number[berth[best_pair.first].getClassId()].second = true;
			robot[best_pair.second.first].setClassId(berth[best_pair.first].getClassId());
			free_robots.erase(best_pair.second.first);
		}
		if(!free_robots.size()) continue; //没有闲人，撤退！


		std::unordered_map<int, int> free_class; //需求类id:需求个数
		std::unordered_set<int> must_class; //硬需求类id
		for(auto [cid, i]:class_robot_number){
			if(i.first > 0){
				free_class[cid] = i.first;
				if(i.second==false) must_class.insert(cid);
			}
		}
		//先分给硬需求类（类选机器人
		while(must_class.size()){
			if(!free_robots.size()) break;
			std::unordered_map<int, std::vector<std::pair<int, int>>> res; //类id:机器人id,距离
			for(auto i:free_robots){
				int dist = 0x3f3f3f3f, class_id, tmp; //机器人离哪个类最近
				for(auto j:must_class){
					tmp = manhattanDist(robot[i].getPosition(), classCenterPos[j]);
					if(tmp < dist) class_id = j, dist = tmp;
				}
				if(!res.count(class_id) || (free_robots.size() < must_class.size() && res[class_id].size() < free_class[class_id])){//当闲人比硬需求类个数多时允许排单
					res[class_id].push_back({i, dist});
				}else{
					for(auto v:res[class_id]){
						if(dist < v.second) v = {i, dist};
					}
				}
			}
			for(auto [c_id, v]:res){ //分配竞争到硬需求类的机器人到类里
				for(auto [r_id, dist]:v){
					robot_in_class[c_id].push_back(r_id);
					robot[r_id].setClassId(c_id);
					free_robots.erase(r_id);
					if(free_class.count(c_id)){
						free_class[c_id] --;
						if(free_class[c_id] == 0) free_class.erase(c_id);
					}
				}
				must_class.erase(c_id);
			}
		}


		//再分给软需求类
		while(free_class.size()){
			if(!free_robots.size()) break;
			std::unordered_map<int, std::vector<std::pair<int, int>>> res1; //类id:机器人id,距离
			for(auto i:free_robots){ //机器人离哪个类近
				int dist = 0x3f3f3f3f, class_id, tmp;
				for(auto [cid,n]:free_class){
					tmp = manhattanDist(robot[i].getPosition(), classCenterPos[cid]);
					if(tmp < dist) class_id = cid, dist = tmp;
				}
				if(!res1.count(class_id) || res1[class_id].size() < free_class[class_id]){
					res1[class_id].push_back({i, dist});
				}else{
					for(auto v:res1[class_id]){
						if(dist < v.second) v = {i, dist};
					}
				}
			}
			for(auto [c_id, vect] :res1){
				for(auto [r_id,dist]:vect){
					robot_in_class[c_id].push_back(r_id);
					robot[r_id].setClassId(c_id);
					free_robots.erase(r_id);
					if(free_class.count(c_id)){
						free_class[c_id]--;
						if(free_class[c_id]== 0) free_class.erase(c_id);
					}
				}
			}
		}

		//再分给最佳泊位
		for(auto p:free_robots){
			int best_berth = bestBerth[robot[p].getPosition().x][robot[p].getPosition().y].first;
			robot_in_class[berth[best_berth].getClassId()].push_back(p);
			robot[p].setClassId(berth[best_berth].getClassId());
		}
	}



	/*
	for(int b = 0; b < maxBlockId; b++){
		std::clog << "block" << b << std::endl;
		for(auto c: berth_in_block[b]) std::clog << "berth" << c << "in class" << berth[c].getClassId() << std::endl;
		for(auto c:class_in_block[b]){
			std::clog << "class" << c << std::endl;
			for(int j : robot_in_class[c]) std::clog << "robot" << j << "in class"<< robot[j].getClassId() << std::endl;
		}
	}
	*/
}