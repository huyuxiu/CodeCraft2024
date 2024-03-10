#include "model.h"

char map[conVar::maxX+1][conVar::maxY+1];                                         // 地图
Robot robot[conVar::maxRobot];                                                    // 机器人
Goods goods[5000];                                                                // 货物
std::unordered_map<int, std::vector<int>> deleteGoods;                            // 删除货物<frameid,货物id>
int goodsSize = 0;                                                                // 货物数量
int k = 0;                                                                        // 新增货物数量
int goodsId = 0;                                                                  // 新增货物id
Berth berth[conVar::maxBerth];                                                    // 泊点
Ship ship[conVar::maxShip];                                                       // 船只
int frameId = 0;                                                                  // 帧编号
int money = 0;                                                                    // 金钱
int shipCapacity = 0;                                                             // 船的容积
int dx[4] = {0, 0, -1, 1};                                        // 机器人移动
int dy[4] = {1, -1, 0, 0};                                        // 机器人移动
std::unordered_map<Position,int> posToInstruction;                                //相对位置到指令
std::priority_queue<Goods,std::vector<Goods>,CompareGoodsToBerth>  goodsHeap;     //物品到港口优先队列
std::queue<Goods> robotGoodsQueue[10];                                          //机器人拿货队列
std::deque<int> robotMoveQueue[10];                                               //机器人指令队列 -1拿货 -2放货
int block[conVar::maxX+1][conVar::maxY+1];                                        //标记地图的联通块，-1为不可达
std::vector<int> aliveRobotId;                                                          //活的机器人

