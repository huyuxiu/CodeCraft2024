#include "util.h"
#include "model.h"

int manhattanDist(Position pos1,Position pos2){
	return abs(pos1.x-pos2.x)+abs(pos1.y-pos2.y);
}

bool Robort_isCollision(Position pos){
	return map[pos.x][pos.y] == '*' && map[pos.x][pos.y] != '#' && map[pos.x][pos.y] != 'A';
}

bool isCollision(Position pos){
	return map[pos.x][pos.y] != '*' && map[pos.x][pos.y] != '#';
}
