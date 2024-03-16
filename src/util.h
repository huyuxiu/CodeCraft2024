#ifndef UTIL_H
#define UTIL_H
#include "const.h"
#include "model.h"
#include "berth.h"
#include<cmath>
#include<cstring>
#include <random>
#include<algorithm>
#include<map>
#include<numeric>
typedef std::pair<int, Position> PIP;
typedef std::pair<Position, int> PPI;
typedef std::pair<int,int> PII;
int manhattanDist(Position pos1,Position pos2);                             //计算曼哈顿距离
bool isCollision(Position pos);                                             //障碍物碰撞检测
std::deque<PPI> aStar(Position start, Position end);                        //A-star算法
void floodFill(Position pos,int blockid);                                   //floodfill算法
int getBlockId(Position pos);                                               //获取blockid
int calPriorityGoodsBerth(int value,int dist);                              //通过距离和价格计算得到节点优先级
bool robotIsCollision(Position pos);                                        //考虑下一帧机器人的碰撞检测
std::deque<PPI> aStar2(Position start, Position end, bool &isGet);          //碰撞A*
std::deque<PPI> bfsTarget(Position startPos, char target);                  //bfs寻路
void multiSourceBFS();                                                      //初始化时多源bfs找当前点最近泊位
void clusteringBerth();                                                     //初始化时给泊位分类
void calCenterPos();
void distributeRobots();                                                    //初始化时分配机器人到类
#endif //UTIL_H
