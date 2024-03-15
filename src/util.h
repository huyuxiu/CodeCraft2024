#ifndef UTIL_H
#define UTIL_H
#include "const.h"
#include "model.h"
#include "berth.h"
#include<cmath>
#include<cstring>
typedef std::pair<int, Position> PIP;
typedef std::pair<Position, int> PPI;
typedef std::pair<int,int> PII;
int manhattanDist(Position pos1,Position pos2);                             //计算曼哈顿距离
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
void robotCollision(int id);                                           //机器人碰撞避免
bool robotIsCollision(Position pos);                                        //考虑下一帧机器人的碰撞检测
bool isLinked(Position start,Position end);                                 //碰撞检测连通性
std::deque<PPI> aStar2(Position start, Position end, bool &isGet);          //碰撞A*
std::deque<PPI> bfsTarget(Position startPos, char target);                  //bfs寻路
void multiSourceBFS();
#endif //UTIL_H
