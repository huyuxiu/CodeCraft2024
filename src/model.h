#ifndef MODEL_H
#define MODEL_H
#include "const.h"

struct Position{
	/*     坐标     */
	int x;
	int y;
	Position(int x,int y) : x(x),y(y) {};
};

struct Goods{
	/*     货物     */
	int money;                                     //货物价格
	Position pos;                                  //货物位置
	Goods(int money,Position& pos) : money(money), pos(pos) {};
};

struct Map{
	char data[conVar::maxX+1][conVar::maxY+1];
};
#endif //MODEL_H