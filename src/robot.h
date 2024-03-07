#ifndef ROBOT_H
#define ROBOT_H
#include "postion.h"
class Robot{
	/*     机器人     */
public:
	Robot(int id,const Position& pos);              //构造函数
	int getId() const;                              //获取机器人id
	Position getPosition() const;                   //获取机器人位置
private:
	int id_;                                        //机器人id
	Position pos_;                                  //机器人坐标
};


#endif //ROBOT_H
