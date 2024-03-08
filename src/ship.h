#ifndef SHIP_H
#define SHIP_H
#include "const.h"

class Ship{
    /*    船只    */
private:
    int id_;                            //船只的id
    Position pos_;                      //船只的位置
    int status_;                        //船只的状态： 0表示运输中，1表示装货状态或运输完成状态，2表示泊外等待
    int capacity_;                      //船只容量
    int loaded_cap_;                    //已经装载的容量
    int money_;                         //已经拿到的货物价值  
public:
    Ship(int id, int capacoty, const Position& pos);  //船只构造函数
    Ship();                             //船只默认构造函数
    int getId() const;                  //获取船只id
    int getCapacity() const;            //获取船只容量
    Position getPosition() const;       //获取船只位置
    int getLoaded() const;              //获取船只已经装载的货物容量
    void setLoaded(int &loaded);        //设置船只已经加载的货物容量
};
#endif //SHIP_H
