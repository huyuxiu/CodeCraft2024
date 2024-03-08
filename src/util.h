#ifndef UTIL_H
#define UTIL_H
#include "const.h"

#include<cmath>
int manhattanDist(Position pos1,Position pos2){
	return abs(pos1.x-pos2.x)+abs(pos1.y-pos2.y);
}


#endif //UTIL_H
