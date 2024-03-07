#ifndef MODEL_H
#define MODEL_H
#include "const.h"

struct Position{
	/*     坐标     */
	int x;                                                             //x坐标
	int y;                                                             //y坐标
	Position(int x,int y) : x(x),y(y) {};                              //坐标构造函数
	Position() : x(0),y(0) {};                                         //坐标默认构造函数
};

struct Goods{
	/*     货物     */
	int value;                                                          //货物价格
	Position pos;                                                       //货物位置
	Goods(int value, const Position& pos) : value(value), pos(pos) {}   //货物构造函数
	Goods() : value(0), pos() {}                                        //货物默认构造函数
};

struct Map{
	char data[conVar::maxX+1][conVar::maxY+1];
};
#endif //MODEL_H