#ifndef CONST_H
#define CONST_H
#include <cstddef>
#include <functional>

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
	const int outGoodsHeapSurplusFrame = 200;                          //出物品队列剩余帧数
	const int goodsPermitDeathFrame = 40;                              //货物消失容许误差帧数
	const int berthMaxPresure = 1;                                     //泊位最大压力
	const int maxRobotGoodsQueue = 1;                                  //机器人货物队列最大值
}

/*    常用结构体    */
struct Position{
	/*     坐标     */
	int x;                                                                                          //x坐标
	int y;                                                                                          //y坐标
	Position(int x,int y) : x(x),y(y) {};                                                           //坐标构造函数
	Position() : x(0),y(0) {};                                                                      //坐标默认构造函数
	bool operator==(const Position& other) const {
		/* 相等性比较操作符重载 */
		return x == other.x && y == other.y;
	}
	Position operator-(const Position& other) const {
		/*     相减运算符重载     */
		return Position(x - other.x, y - other.y);
	}
};
struct PositionHash {
	size_t operator()(const Position& p) const {
		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
	}
};
namespace std {
	template<> struct hash<Position> {
		size_t operator()(const Position& p) const {
			return hash<int>()(p.x) ^ hash<int>()(p.y);
		}
	};
}
struct Goods{
	/*     货物     */
	int value;                                                                                                    //货物价格
	Position pos;                                                                                                 //货物位置
	int deathId;                                                                                                  //这一帧到的时候货物消失
	int berthDist;                                                                                                //到泊点和虚拟点最近距离
	int berthId;                                                                                                  //泊点数组的下标，下标越小距离泊点越近
	int priority;                                                                                                 //优先级
	std::pair<int,int> berthQueue[10];                                                                            //泊点队列
	Goods(int value, const Position pos,int deathId) : value(value), pos(pos),deathId(deathId),priority(1e8) {}   //货物构造函数
	Goods() : value(0), pos(),deathId(0),priority(1e8) {}                                                         //货物默认构造函数

};

struct Compare {
	/*      比较PIP        */
	bool operator()(const std::pair<int, Position>& a, const std::pair<int, Position>& b) const {
		return a.first > b.first;
	}
};

struct CompareGoodsToBerth {
	/*      维护货物到港口优先队列       */
	bool operator()(const Goods& a, const Goods& b) const {
		return a.priority < b.priority;
	}
};


#endif // CONST_H