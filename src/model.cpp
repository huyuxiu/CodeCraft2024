#include "model.h"

char map[conVar::maxX+1][conVar::maxY+1];                       // 地图
Robot robot[conVar::maxRobot];                                  // 机器人
std::vector<Goods> goods;                                       // 货物
std::unordered_map<int, std::vector<int>> deleteGoods;          // 删除货物<frameid,货物id>
int goodsSize = 0;                                              // 货物数量
int k = 0;                                                      // 新增货物数量
int goodsId = 0;                                                // 新增货物id
Berth berth[conVar::maxBerth];                                  // 泊点
Ship ship[conVar::maxShip];                                     // 船只
int frameId = 0;                                                // 帧编号
int money = 0;                                                  // 金钱
int shipCapacity = 0;                                           // 船的容积
int dx[4] = {0, 0, -1, 1};                      // 机器人移动
int dy[4] = {1, -1, 0, 0};                      // 机器人移动
std::unordered_map<Position,int> posToInstruction;              //相对位置到指令

