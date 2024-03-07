#include "robot.h"

Robot::Robot(int id, const Position& pos) : id_(id), pos_(pos) ,carry_(false) {}

Robot::Robot() : id_(0), pos_() ,carry_(false) {}

int Robot::getId() const {
	return id_;
}

Position Robot::getPosition() const {
	return pos_;
}

bool Robot::hasGoods() const {
	return carry_;
}

void Robot::carryGoods(Goods &goods) {
	goods_ = goods;
	carry_ = true;
}

void Robot::setId(int id) {
	id_ = id;
}

void Robot::setPosition(Position pos) {
	pos_ = pos;
}