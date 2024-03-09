#include "ship.h"

Ship::Ship(int id, int status,int berthId) : id_(id),  status_(status), loaded_cap_(0), money_(0),berthId_(berthId) {}

Ship::Ship() : id_(), pos_(), status_(1), capacity_(0), loaded_cap_(0), money_(0),berthId_(-1) {}

int Ship::getId() const{
    return id_;
}

int Ship::getCapacity() const{
    return capacity_;
}

Position Ship::getPosition() const{
    return pos_;
}

int Ship::getLoaded() const{
    return loaded_cap_;
}

void Ship::setLoaded(int &loaded){
    loaded_cap_ = loaded;
}

void Ship::setCapacity(int capacity){
	capacity_ = capacity;
}

int Ship::getBerthId() const {
	return berthId_;
}

void Ship::setBerthId(int berthId) {
	berthId_ = berthId;
}

void Ship::setStatus(int status) {
	status_ = status;
}

int Ship::getStatus() const {
	return status_;
}