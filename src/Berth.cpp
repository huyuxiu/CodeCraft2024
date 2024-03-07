#include "Berth.h"

Berth::Berth(int id, const Position& pos, const int transport_time, const int loading_speed) : id_(id), pos_(pos), transport_time_(transport_time), loading_speed_(loading_speed){}

Berth::Berth() : id_(-1), pos_(), transport_time_(0), loading_speed_(0) {}

int Berth::getId() const {
    return id_;
}

int Ber








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
