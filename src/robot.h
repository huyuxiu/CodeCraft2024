#ifndef ROBOT_H
#define ROBOT_H
#include "const.h"
#include "util.h"

class Robot{
	/*     机器人     */
public:
	Robot(int id,const Position& pos);              //机器人构造函数
	Robot();                                        //机器人默认构造函数
	int getId() const;                              //获取机器人id
	bool hasGoods() const;                          //获取机器人是否携带货物
	Position getPosition() const;                   //获取机器人位置
	void carryGoods(Goods &goods);                  //机器人改变携带信息
	void setId(int id);                             //机器人设置id
	void setPosition(Position pos);                 //机器人设置位置
	void setStatus(int status);                     //机器人设置状态
	int getStatus() const;                          //机器人获取状态
private:
	int id_;                                        //机器人id
	Position pos_;                                  //机器人坐标
	bool carry_;                                    //是否携带货物
	Goods goods_;                                   //货物
	bool status_;                                   //货物状态
};

#endif //ROBOT_H
