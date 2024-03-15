#ifndef CONRTOL_H
#define CONRTOL_H
#include "model.h"
#include "const.h"
#include "iointerface.h"
#include "util.h"


bool moveRobort(Robot robot,int i);
void robotFindGood(int id);                                       //机器人找货
void robotFindBerth(int id);                                      //机器人送货
int calucateRobotPri(int i,Position goodsPos);
void distributeGoods(int id);                                      //将货物队列分配给机器人
void robotMove();                                                   //移动机器人输出指令序列
void shipToBerth();                                                //船与泊位匹配
void shipFull(int id);
void shipGreedy(int id);
int maxGoodsBerth();
bool findNewBerth(int id);                                         //机器人分配泊位
bool findNewBerthCollision(int id);                                //机器人分配泊位（碰撞版）
void robotAfterCollision(int id);                                  //机器人碰撞
#endif //CONRTOL_H
