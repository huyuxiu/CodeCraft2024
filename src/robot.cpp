#include "robot.h"

Robot::Robot(int id, const Position& pos) : id_(id), pos_(pos) {}

int Robot::getId() const {
	return id_;
}

Position Robot::getPosition() const {
	return pos_;
}
