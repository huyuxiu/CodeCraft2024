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

void Robot::carryGoods(Goods goods) {
	goods_ = goods;
}

void Robot::setCarry(int carry) {
	carry_ = carry;
}

void Robot::setId(int id) {
	id_ = id;
}

void Robot::setPosition(Position pos) {
	pos_ = pos;
}

int Robot::getStatus() const {
	return status_;
}

void Robot::setStatus(int status) {
	status_ = status;
}

Goods Robot::getGoods() const{
	return goods_;
}
