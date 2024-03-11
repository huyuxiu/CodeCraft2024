#ifndef MODEL_H
#define MODEL_H

#include "const.h"
#include "robot.h"
#include "ship.h"
#include "berth.h"

#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <deque>
extern char map[conVar::maxX+1][conVar::maxY+1];                                         //地图
extern Berth berth[conVar::maxBerth];                                                    //泊点
extern Goods goods[5000];                                                                //货物
extern Robot robot[conVar::maxRobot];                                                    //机器人
extern std::unordered_map<int,std::vector<int>> deleteGoods;                             //删除货物<frameid,货物id>
extern int goodsSize;                                                                    //货物数量
extern int k;                                                                            //新增货物数量
extern int goodsId;                                                                      //新增货物id
extern Ship ship[conVar::maxShip];                                                       //船只
extern int frameId;                                                                      //帧编号
extern int money;                                                                        //金钱
extern int shipCapacity;                                                                 //船的容积
extern int dx[4];                                                                        //机器人移动
extern int dy[4];                                                                        //机器人移动
extern std::priority_queue<Goods,std::vector<Goods>,CompareGoodsToBerth>  goodsHeap;     //物品到港口优先队列
extern std::queue<Goods> robotGoodsQueue[10];                                            //机器人拿货队列
extern std::deque<int> robotMoveQueue[10];                                               //机器人指令队列 -1拿货 -2放货
extern int block[conVar::maxX+1][conVar::maxY+1];                                        //标记地图的联通块，-1为不可达
extern std::vector<int> aliveRobotId;                                                    //活着的机器人
extern int maxValue;                                                                     //场上价值最高的货
extern int shipTargetBerth[conVar::maxBerth];
extern std::pair<int,int> berthQueue[conVar::maxX+1][conVar::maxY+1][10];                //地图上某点到泊位的优先队列
#endif //MODEL_H