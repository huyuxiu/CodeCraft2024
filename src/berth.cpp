#include "berth.h"

Berth::Berth(int id, const Position& pos, const int transport_time, const int loading_speed) : id_(id), pos_(pos), transport_time_(transport_time), loading_speed_(loading_speed){}

Berth::Berth() : id_(-1), pos_(), transport_time_(0), loading_speed_(0) {}

int Berth::getId() const {
    return id_;
}

int Berth::getVelocity() const {
	return velocity_;
}

void Berth::setVelocity(int velocity) {
	velocity_ = velocity;
}

Position Berth::getPosition() const {
	return pos_;
}
