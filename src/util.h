#ifndef UTIL_H
#define UTIL_H
#include "const.h"
#include "berth.h"
#include<cmath>
int manhattanDist(Position pos1,Position pos2);

bool Robort_isCollision(Position pos);					    //机器人碰撞检测

int priorityGoodsBerthSHip(Goods good,Berth berth);

#endif //UTIL_H
