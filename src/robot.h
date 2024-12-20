#ifndef ROBOT_H
#define ROBOT_H
#include "const.h"

class Robot{
	/*     机器人     */
public:
	Robot(int id,const Position& pos,int status,int carry,int blockId);              //机器人构造函数
	Robot();                                        //机器人默认构造函数
	int getId() const;                              //获取机器人id
	bool hasGoods() const;                          //获取机器人是否携带货物
	Position getPosition() const;                   //获取机器人位置
	void carryGoods(Goods goods);                  //机器人改变携带信息
	void setId(int id);                             //机器人设置id
	void setPosition(Position pos);                 //机器人设置位置
	void setStatus(int status);                     //机器人设置状态
	void setCarry(int carry);						//设置机器人状态
	int getStatus() const;                          //机器人获取状态1:正常运行
	Goods getGoods() const;                         //获取机器人货物
	int getBlockId() const;                         //获取机器人联通块id
	void setBlockId(int blockId);                              //设置机器人联通块id
	int getClassId() const;                         //获取机器人类id
	void setClassId(int classId);                   //设置机器人类id
	int getBerthId() const;                         //获取机器人泊位id
	void setBerthId(int berthId);                   //设置机器人泊位id
	int collision;									//机器人是否要撞到了
private:
	int id_;                                        //机器人id
	int berthId_;                                   //机器人目标泊位id
	int classId_;                                   //机器人所在类
	Position pos_;                                  //机器人坐标
	int carry_;                                     //是否携带货物
	Goods goods_;                                   //货物
	bool status_;                                   //货物状态
	int blockId_;                                   //机器人所处联通块,-1就是死掉了
};

#endif //ROBOT_H
