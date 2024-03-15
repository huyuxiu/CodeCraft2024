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



int calPriorityGoodsBerth(int value,int dist){
	/*      通过距离和价格计算得到节点优先级       */
	return value-dist;
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

std::deque<PPI> bfsTarget(Position startPos, char target) {
	std::deque<PPI> res;
	std::queue<Position>q;
	std::unordered_map<Position, PPI> prev;
	std::unordered_map<Position, bool> visitited;
	visitited[startPos] = true;

	bool isGet = false;
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

void multiSourceBFS(){
	/*     多源bfs给地图上每个点分配一个泊位(更新bestBerth)     */
	bool vis[conVar::maxX+1][conVar::maxY+1];
	//初始化为{-1，-1}
	for (int i = 0; i <= conVar::maxX; ++i) {
		for (int j = 0; j <= conVar::maxY; ++j) {
			bestBerth[i][j] = {-1,-1};
		}
	}
	std::queue<Position> q;
	memset(vis,false,sizeof vis);
	for(int i = 0; i < conVar::maxBerth; i++){
		Position p = berth[i].getPosition();
		bestBerth[p.x][p.y].first = i;
		bestBerth[p.x][p.y].second = 0;
		q.push(p);
	}
	while(!q.empty()){
		Position t = q.front();
		q.pop();
		for(int i =0;i<4;i++){
			int a = t.x+dx[i];
			int b = t.y+dy[i];
			if(a<0||a>conVar::maxX||b<0||b>conVar::maxY) continue;
			if(isCollision(Position(a,b))) continue;
			if(bestBerth[a][b].first!=-1) continue;
			bestBerth[a][b].first = bestBerth[t.x][t.y].first;
			bestBerth[a][b].second = bestBerth[t.x][t.y].second+1;
			q.push(Position(a,b));
		}
	}
}


//void clusteringBerth(){
//  roll点版本
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

void clusteringBerth(){
	int cnt = 0; //class个数
	for(int i = 0; i < conVar::maxBerth; i++){
		berth_in_block[berth[i].getBlockId()].push_back(i);
	}

	for(auto p : berth_in_block){
		auto q = p.second;
		if(q.size() > 2){ //需要再分类
			int k = std::ceil(q.size() / 2); //需要分成的类数
			totalClass += k;//记录所有连通块分为几类
			int max_iterations = 100;


			/*      kmeans聚类        */
			std::vector<int> cx, cy; //初始化k个中心
			for(int i = 0; i < k; i++){
				cx.push_back(berth[q[1 + i * q.size() / k]].getPosition().x);
				cy.push_back(berth[q[1 + i * q.size() / k]].getPosition().y);
			}

			for(int i = 0; i < max_iterations; i++){ //迭代
				berthInCenter.clear();
				for(int j = 0; j < q.size(); j++){ //分配每个样本到最近的中心
					int min = 0, min_dist = 1e8, dist;
					for(int s = 0; s < k; s++){
						dist = manhattanDist(berth[q[j]].getPosition(), Position(cx[s], cy[s]));
						if(dist < min_dist) min_dist = dist, min = s;
					}
					berthInCenter[min].push_back(q[j]);
				}

				for(int s = 0; s < k; s++){ //更新聚类中心
					cx[s] = 0, cy[s] = 0;
					for(auto b : berthInCenter[s]) cx[s] += berth[b].getPosition().x, cy[s] += berth[b].getPosition().y;
					cx[s] /= berthInCenter[s].size(), cy[s] /= berthInCenter[s].size();
				}
			}

			for(int s = 0; s < k; s++){
				for(auto b : berthInCenter[s]) berth[b].setClassId(cnt);
				class_in_block[p.first].push_back(cnt++);
			}
		}else{
			for(auto b:q) berth[b].setClassId(cnt);
			class_in_block[p.first].push_back(cnt++);
		}
	}
}

void calCenterPos(){
	for(int i =0;i<totalClass;i++){
		Position p(0,0);
		for(int j =0;j<berthInCenter[i].size();j++){
			p.x+=berth[berthInCenter[i][j]].getPosition().x;
			p.y+=berth[berthInCenter[i][j]].getPosition().y;
		}
		p.x/=berthInCenter[i].size();
		p.y/=berthInCenter[i].size();
		classCenterPos.insert(std::make_pair(0,p));
	}
}


