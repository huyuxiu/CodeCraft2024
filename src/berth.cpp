#include "berth.h"

Berth::Berth(int id, const Position& pos, const int transport_time, const int Velocity) : id_(id), pos_(pos), transport_time_(transport_time), Velocity_(Velocity){}

Berth::Berth() : id_(-1), pos_(), transport_time_(0), Velocity_(0) {}

int Berth::getId() const {
    return id_;
}

int Berth::getTransport_time() const {
    return transport_time_;
}

int Berth::getVelocity() const {
    return velocity_;
}

Position Berth::getPosition() const {
    return pos_;
}

void Berth::uploadGoods() {

}


