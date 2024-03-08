#ifndef BERTH_H
#define BERTH_H
#include "const.h"
#include <queue>

class Berth{
    /*    船只    */
private:
    int id_;                                //泊位的id
    Position pos_;                          //泊位的位置
    int status_;                            //泊位的状态： 0表示空闲，1表示忙碌中
    std::queue<Goods> goods_;               //泊位上的货物队列
    int transport_time_;                    //泊位到虚拟点的传送时间
    int velocity_;                          //泊位的装载速度
public:
    Berth(int id, const Position& pos, const int transport_time, const int velocity);     //泊位构造函数
    Berth();                                //船只默认构造函数
    int getId() const;                      //获取泊位id
    int getTransport_time() const;          //获取泊位达到虚拟点的时间
    Position getPosition() const;           //获取泊位位置
    int getVelocity() const;           //获取泊位装载速度
    void uploadGoods();                     //装载货物

};
#endif //BERTH_H