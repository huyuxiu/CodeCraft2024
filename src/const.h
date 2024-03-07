#ifndef CONST_H
#define CONST_H

/*      题目常量       */
namespace conVar{
	const int minX = 0;                                               //地图边界
	const int maxX = 199;                                             //地图边界
	const int minY = 0;                                               //地图边界
	const int maxY = 199;                                             //地图边界
	const int maxRobot = 10;                                          //机器人数量
	const int maxBerth = 10;                                          //泊位数量
	const int maxShip = 5;                                            //轮船数量
	const int maxFrame = 15000;                                       //比赛时间
	const int moveBerthFrame = 500;                                   //移动到泊位帧数
	const int collisionFrame = 20;                                    //碰撞停止帧数
	const int goodsStayFrame = 1000;                                  //货物停留帧数
}

/*     运行参数     */
namespace Parameter{

}

/*    常用结构体    */
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
#endif // CONST_H
