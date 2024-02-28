#include "DroneObserver.h"

DroneObserver::DroneObserver(Drone &drone) : IObserver(), drone_(drone) {
    this->drone_.attach(this);
}

DroneObserver::~DroneObserver() {}

void DroneObserver::update(const std::string &message) {
    message_ = message;
}

void DroneObserver::removeFromList() {
    drone_.detach(this);
}
