#ifndef ROBOT_H
#define ROBOT_H
#include "postion.h"
class Robot{
	/*     机器人     */
public:
	Robot(int id,const Position& pos);
	int getId() const;
	Position getPosition() const;
private:
	int id_;                    //机器人id
	Position pos_;               //机器人坐标
};


#endif //ROBOT_H
