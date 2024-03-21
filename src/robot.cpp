#include "robot.h"

Robot::Robot(int id, const Position& pos,int status,int carry,int blockId) : id_(id), pos_(pos) ,carry_(carry),status_(status),blockId_(blockId),classId_(-1),berthId_(-1), collision(2){}

Robot::Robot() : id_(0), pos_() ,carry_(0) ,status_(1),blockId_(-1),classId_(-1),berthId_(-1), collision(2) {}

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

void Robot::setBlockId(int blockId) {
	blockId_ = blockId;
}

int Robot::getBlockId() const {
	return blockId_;
}

void Robot::setBerthId(int berthId) {
	berthId_=berthId;
}

int Robot::getBerthId() const {
	return berthId_;
}

int Robot::getClassId() const {
	return classId_;
}

void Robot::setClassId(int classId) {
	classId_ = classId;
}