#ifndef CONRTOL_H
#define CONRTOL_H
#include "model.h"
#include "const.h"
#include "iointerface.h"
#include "util.h"


void robotFindGood(int id);                                       //机器人找货
void robotFindBerth(int id);                                      //机器人送货
void distributeGoods(int id);                                      //将货物队列分配给机器人
void robotMove();                                                   //移动机器人输出指令序列
void shipToBerth();                                                //船与泊位匹配
int maxGoodsBerth();
void robotAfterCollision(int id);                                  //机器人碰撞
void shipFull(int id);
void shipGreedy(int id);
int findNewRobot(int classId,int berthId);
void shipModerate(int id);

#endif //CONRTOL_H
