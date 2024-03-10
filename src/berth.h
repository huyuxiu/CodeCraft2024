#ifndef BERTH_H
#define BERTH_H
#include "const.h"

class Berth{
    /*    泊位    */
private:
    int id_;                                //泊位的id
    Position pos_;                          //泊位的位置
    int status_;                            //泊位的状态： 0表示空闲，1表示忙碌中
    int goods_num_;                         //泊位上的货物数量
    int transport_time_;                    //泊位到虚拟点的传送时间
    int velocity_;                          //泊位的装载速度
	int blockId_;                                    //泊位所处联通块
public:
    Berth(int id, const Position& pos, const int transport_time, const int velocity,int blockId);     //泊位构造函数
    Berth();                                //船只默认构造函数
    int getId() const;                      //获取泊位id
    int getTransport_time() const;          //获取泊位达到虚拟点的时间
    Position getPosition() const;           //获取泊位位置
    int getVelocity() const;                //获取泊位装载速度
    int getStatus() const;                  //获取泊位的状态
    int getGoods_size() const;              //获取泊位货物数量
	void setVelocity(int velocity);         //设定泊位装载速度
    void uploadGoods();                     //装载货物
	void setTransport_time(int time);       //设定泊位到虚拟点传送时间
	void setPos(Position pos);              //设定泊位位置
	void setId(int id);                     //设定id
    void setStatus(int status);             //设置泊位的状态
    void carryGoods(int num);               //搬运货物
    void pullGoods();                       //机器人放下货物
	int getBlockId() const;                 //获取泊位联通块id
	void setBlockId(int blockId);           //设置泊位联通块id

};
#endif //BERTH_H