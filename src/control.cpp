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

void getGoodsBerthQueue(){
	/*    初始化物品队列     */
	std::priority_queue<Goods,std::vector<Goods>,CompareGoodsToBerth>  goodsHeap(goods.begin(),goods.end());     //物品到港口优先队列
}
