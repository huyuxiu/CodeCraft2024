#ifndef MODEL_H
#define MODEL_H
#include "const.h"
#include "robot.h"

char map[conVar::maxX+1][conVar::maxY+1];                               //地图
Robot robot[conVar::maxRobot];                                          //机器人
Goods goods[20000];                                                     //货物
int k = 0;                                                              //货物数量
Berth berth[conVar::maxBerth];                                          //泊点
Ship ship[conVar::maxShip];                                             //船只
int frameId = 0;                                                        //帧编号
int money = 0;                                                          //金钱
int shipCapacity = 0;                                                   //船的容积
#endif //MODEL_H