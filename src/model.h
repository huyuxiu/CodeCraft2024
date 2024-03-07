#ifndef MODEL_H
#define MODEL_H
#include "const.h"
#include "robot.h"

char map[conVar::maxX+1][conVar::maxY+1];                               //地图
Robot robot[conVar::maxRobot];                                          //机器人
Goods goods[20000];                                                     //货物
int k = 0;                                                              //货物数量
Berth berth[conVar::maxBerth];                                          //泊点

#endif //MODEL_H