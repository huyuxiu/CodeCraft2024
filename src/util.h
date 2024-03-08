#ifndef UTIL_H
#define UTIL_H
#include "const.h"
#include "model.h"
#include "berth.h"
#include<cmath>

int manhattanDist(Position pos1,Position pos2);                             //计算曼哈顿距离
bool Robort_isCollision(Position pos);					                    //机器人碰撞检测
bool isCollision(Position pos);                                             //障碍物碰撞检测
std::deque<Position> aStar(Position start, Position end);                   //A-star算法
int priorityGoodsBerthSHip(Goods good,Berth berth);                         //货物-泊点优先函数

#endif //UTIL_H
