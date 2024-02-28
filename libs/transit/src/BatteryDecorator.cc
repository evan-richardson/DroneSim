#include "BatteryDecorator.h"
#include "Drone.h"

BatteryDecorator::BatteryDecorator(IStrategy* strategy) : IStrategy() {
  this->strategy = strategy;
}

BatteryDecorator::~BatteryDecorator() {
  // Delete dynamically allocated variables
  if (strategy) delete strategy;
}

void BatteryDecorator::move(IEntity* entity, double dt) {
  if ((std::string) entity->getDetails()["type"] == "drone") {
    Drone* drone = (Drone*) entity;
    if(drone->getCharge() > 0) {
      if (!strategy->isCompleted(drone)) {
        drone->setCharge(drone->getCharge() - 0.25 * dt);
        strategy->move(drone, dt);
      }
      if (!drone->isCharging() && drone->getCharge() < 50) {
        drone->recharge();
      }
    }
  }
}

bool BatteryDecorator::isCompleted(IEntity* entity) {
  if (strategy->isCompleted(entity)) {
    return true;
  }
}