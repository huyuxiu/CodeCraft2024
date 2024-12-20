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
#include <unordered_set>
#include <cmath>
#include <algorithm>
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
extern std::priority_queue<Goods,std::vector<Goods>,CompareGoodsToBerth>  goodsHeap[10]; //物品到港口优先队列
extern std::priority_queue<Goods,std::vector<Goods>,CompareGoodsToRobot> robotGoodsQueue[10];//机器人拿货队列
extern std::deque<int> robotMoveQueue[10];                                               //机器人指令队列 -1拿货 -2放货
extern int block[conVar::maxX+1][conVar::maxY+1];                                        //标记地图的联通块，-1为不可达
extern std::vector<int> aliveRobotId;                                                    //活着的机器人
extern int maxValue;                                                                     //场上价值最高的货
extern int maxBlockId;                                                                   //连通块数量
extern int shipTargetBerth[conVar::maxBerth];											 //船的目标泊位
extern int goodsTargetBerth[conVar::maxBerth];											   //货物前往的泊位标志
extern int maxShipRestTime;																 //给船回去预留的帧数
extern std::pair<int, std::pair<int, Position>> bestBerth[conVar::maxX + 1][conVar::maxY + 1];               //地图上某点的(最近泊位id, (距离，最近泊位坐标))
extern int robotMap[conVar::maxX+1][conVar::maxY+1];                                     //当前/下帧机器人在的点
extern int totalClass;                                                                   //总共类的数量
extern std::unordered_map<int, std::vector<int>> berth_in_block;                        //blockid:包含的泊位id
extern std::unordered_map<int, std::vector<int>> robot_in_block;                       //blockid:包含的机器人id
extern std::unordered_map<int,std::vector<int>> class_in_block;                        //blockid:包含的类id
extern std::unordered_map<int, int> berthArea;                                                 //berthid:berth面积
extern std::unordered_map<int,std::vector<int>> robot_in_class;                         //classid:包含的机器人id，初始化时候安排
extern std::unordered_map<int, std::vector<int>> berthInCenter;                         //中心，泊位id
extern std::unordered_map<int, Position> classCenterPos;                                //类中心位置
extern std::unordered_map<int,int> starBerth;                                           //类内运输能力高的泊位
extern std::unordered_map<int, int> berthArea;                                         //berthid:berth面积
#endif //MODEL_H