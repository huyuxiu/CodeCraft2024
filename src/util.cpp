#include "util.h"

int manhattanDist(Position pos1,Position pos2){
	return abs(pos1.x-pos2.x)+abs(pos1.y-pos2.y);
}