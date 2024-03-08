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
extern char map[conVar::maxX+1][conVar::maxY+1];                               //地图
extern Berth berth[conVar::maxBerth];                                          //泊点
extern std::vector<Goods> goods;                                               //货物
extern Robot robot[conVar::maxRobot];                                          //机器人
extern std::unordered_map<int,std::vector<int>> deleteGoods;                   //删除货物<frameid,货物id>
extern int goodsSize;                                                          //货物数量
extern int k;                                                                  //新增货物数量
extern int goodsId;                                                            //新增货物id
extern Ship ship[conVar::maxShip];                                             //船只
extern int frameId;                                                            //帧编号
extern int money;                                                              //金钱
extern int shipCapacity;                                                       //船的容积
extern int dx[4];                                                              //机器人移动
extern int dy[4];                                                              //机器人移动

#endif //MODEL_H