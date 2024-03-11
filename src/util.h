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
int getBlockId(Position pos);                                               //获取blockid
void bfsBerth(Position start, int dist[conVar::maxX+5][conVar::maxY+5]);//暴搜最近泊位
bool sortGoodsBerthDist(std::pair<int,int>& a,std::pair<int,int>& b);       //泊位距离排序函数
int calPriorityGoodsBerth(int value,int dist);                              //通过距离和价格计算得到节点优先级
int findBerthId(Goods g);                                                   //寻找最近的泊点id
int findNextBerthId(Goods g);                                               //寻找下一个泊点id
#endif //UTIL_H
