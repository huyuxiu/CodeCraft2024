#include "model.h"
#include "util.h"
#include "iointerface.h"

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

void shipToBearth(){
    /*      船和泊位的匹配      */
    for (int i = 0; i < conVar::maxShip; i++){
        if (ship[i].getBerthId() == -1 && ship[i].getStatus() == 1){            //当船达到虚拟点空闲的时候
            int temp_max = 0, target_bearth = 0;
            for (int j = 0; j < conVar::maxBerth; j++){
                if (berth[j].getMoney() > temp_max && berth[j].getStatus() == 0){
                    temp_max = berth[j].getMoney();
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