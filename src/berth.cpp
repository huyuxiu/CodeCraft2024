#include "berth.h"

Berth::Berth(int id, const Position& pos, const int transport_time, const int velocity) : id_(id), pos_(pos), transport_time_(transport_time), velocity_(velocity), money_(0){}

Berth::Berth() : id_(-1), pos_(), transport_time_(0), velocity_(0), money_(0) {}

int Berth::getId() const {
    return id_;
}

int Berth::getTransport_time() const {
    return transport_time_;
}

int Berth::getVelocity() const {
    return velocity_;
}

int Berth::getMoney() const {
    return money_;
}

int Berth::getStatus() const {
    return status_;
}

int Berth::getGoods_size() const {
    return goods_num_;
}

Position Berth::getPosition() const {
    return pos_;
}

void Berth::uploadGoods() {

}

void Berth::setVelocity(int velocity) {
	velocity_ = velocity;
}

void Berth::setTransport_time(int time){
	transport_time_ = time;
}

void Berth::setPos(Position pos){
	pos_ = pos;
}

void Berth::setId(int id){
	id_ = id;
}

void Berth::setStatus(int status){
    status_ = status;
}

void Berth::carryGoods(int num) {
    goods_num_ -= num;
}