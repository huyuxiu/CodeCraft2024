#include "util.h"
typedef std::pair<int, Position> PIP;

int manhattanDist(Position pos1,Position pos2){
	return abs(pos1.x-pos2.x)+abs(pos1.y-pos2.y);
}

bool Robort_isCollision(Position pos){
	return map[pos.x][pos.y] == '*' || map[pos.x][pos.y] == '#' || map[pos.x][pos.y] == 'A';
}

bool isCollision(Position pos){
	return map[pos.x][pos.y] == '*' || map[pos.x][pos.y] == '#';
}

std::deque<Position> aStar(Position start, Position end) {
    std::deque<Position> res;
    if (start.x == end.x && start.y == end.y) return res;

    std::unordered_map<Position, int,PositionHash> dist;                                                         //某一点到起点的真实距离
    std::unordered_map<Position, Position> prev;                                                    //某一点是从哪个点走过来的
    std::priority_queue<PIP, std::vector<PIP>, Compare> heap;                             //小根堆 (估价, 坐标)
    heap.push({manhattanDist(start, end), start});

    while (heap.size()) {
        auto t = heap.top();
        heap.pop();

        Position ver = t.second;                                                                    //估价最小坐标
        if (ver.x == end.x && ver.y == end.y) break;

        for (int i = 0; i < 4; i++) {
            Position p(ver.x + dx[i], ver.y + dy[i]);
            if (p.x < 0 || p.x > conVar::maxX || p.y < 0 || p.y > conVar::maxY) continue;            //地图越界
            if (isCollision(p)) continue;                                                       //碰撞检测
            if (!dist.count(p) || dist[p] > dist[ver] + 1) {                                           //第一次遍历or距离更短
                dist[p] = dist[ver] + 1;
                prev[p] = ver;
                heap.push({dist[p] + manhattanDist(p, end), p});
            }
        }
    }
    while (end.x != start.x || end.y != start.y) {
        res.push_front(end);
        end = prev[end];
    }
    return res;
}
int priorityGoodsBerthSHip(Goods good,Berth berth){
	/*     货物-泊点优先函数     */
	return berth.getTransport_time()+manhattanDist(good.pos,berth.getPosition());
}