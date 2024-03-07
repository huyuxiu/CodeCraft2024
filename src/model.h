#ifndef MODEL_H
#define MODEL_H
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
};

#endif //MODEL_H