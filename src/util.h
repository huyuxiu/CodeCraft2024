#ifndef UTIL_H
#define UTIL_H
#include "const.h"
#include "model.h"
#include "berth.h"
#include<cmath>

typedef std::pair<int, Position> PIP;
typedef std::pair<Position, int> PPI;
typedef std::pair<int,int> PII;
int manhattanDist(Position pos1,Position pos2);                             //计算曼哈顿距离
bool Robort_isCollision(Position pos);					                    //机器人碰撞检测
bool isCollision(Position pos);                                             //障碍物碰撞检测
std::deque<PPI> aStar(Position start, Position end);                        //A-star算法
int priorityGoodsBerthSHip(Goods good,Berth berth);                         //货物-泊点优先函数
void floodFill(Position pos,int blockid);                                   //floodfill算法
#endif //UTIL_H
