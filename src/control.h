#ifndef CONRTOL_H
#define CONRTOL_H
#include "model.h"
#include "const.h"
#include "iointerface.h"
#include "util.h"

bool moveRobort(Robot robot,int i);
void robortFindGood(Robot robot);                                       //机器人找货
void robortFindBerth(Robot robot);                                      //机器人送货
int calucateRobotPri(int i,Position goodsPos);
void distributeGoods(int num);                                      //将货物队列分配给机器人
void robotMove();                                                   //移动机器人输出指令序列
#endif //CONRTOL_H
