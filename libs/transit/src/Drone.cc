#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "BatteryDecorator.h"
#include "ChargeStation.h"

#include "Package.h"
#include "SimulationModel.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  charging = false;
  charge = 100;
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (toChargeStation) delete toChargeStation;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    fprintf(stdout, "Drone::getNextDelivery() 1\n");
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      fprintf(stdout, "Drone::getNextDelivery() 2\n");
      // drone is moving to pick up package for owner at package coordinates
      createMessage(name + std::to_string(id) + " is moving to pick up: " +
      package->getName() + std::to_string(package->getId()) + "\n"
      " for owner: " + package->getOwner()->getName() +
      std::to_string(package->getOwner()->getId()) + "\n"
      " at: " + package->getPositionString());

      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage =
        new BatteryDecorator(
          new BeelineStrategy(position, packagePosition));
      fprintf(stdout, "Drone::getNextDelivery() 3\n");

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination =
          new JumpDecorator(
            new BatteryDecorator(
              new AstarStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
        fprintf(stdout, "Drone::getNextDelivery() 4\n");
      } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new BatteryDecorator(
                new DfsStrategy(
                  packagePosition,
                  finalDestination,
                  model->getGraph()))));
      } else if (strat == "bfs") {
        toFinalDestination =
          new SpinDecorator(
            new SpinDecorator(
              new BatteryDecorator(
                new BfsStrategy(
                  packagePosition,
                  finalDestination,
                  model->getGraph()))));
      } else if (strat == "dijkstra") {
        toFinalDestination =
          new JumpDecorator(
            new SpinDecorator(
              new BatteryDecorator(
                new DijkstraStrategy(
                  packagePosition,
                  finalDestination,
                  model->getGraph()))));
      } else {
        toFinalDestination =
          new BatteryDecorator(
            new BeelineStrategy(
              packagePosition,
              finalDestination));
      }
    }
  }
}

void Drone::update(double dt) {
  if (available)
    getNextDelivery();

  if (toPackage) {
    //fprintf(stdout, "Drone::update() 1\n");
    toPackage->move(this, dt);
    //fprintf(stdout, "Drone::update() 2\n");

    if (toPackage->isCompleted(this)) {
      //fprintf(stdout, "Drone::update() 3\n");
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;

      // drone has picked up package for owner at package coordinates
      createMessage(name + std::to_string(id) + " has picked up: " +
      package->getName() + std::to_string(package->getId()) + "\n"
      " for owner: " + package->getOwner()->getName() +
      std::to_string(package->getOwner()->getId()) + "\n"
      " at: " + package->getPositionString() + "\n\n" +

      // drone is moving to drop off
      // package for owner at destination coordinates
      name + std::to_string(id) + " is moving to drop off: " +
      package->getName() + std::to_string(package->getId()) + "\n"
      " for owner: " + package->getOwner()->getName() +
      std::to_string(package->getOwner()->getId()) + "\n"
      " at: " + package->getDestinationString());
    }
  } else if (toFinalDestination) {
    //fprintf(stdout, "Drone::update() 4\n");
    toFinalDestination->move(this, dt);
    //fprintf(stdout, "Drone::update() 5\n");
    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted(this)) {
      //fprintf(stdout, "Drone::update() 6\n");
      // drone has dropped off package for owner at destination coordinates
      createMessage(name + std::to_string(id) + " has dropped off: " +
      package->getName() + std::to_string(package->getId()) + "\n"
      " for owner: " + package->getOwner()->getName() +
      std::to_string(package->getOwner()->getId()) + "\n"
      " at: " + package->getDestinationString());

      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  } else if (toChargeStation) {
    //fprintf(stdout, "Drone::update() 7\n");
    toChargeStation->move(this, dt);
    //fprintf(stdout, "Drone::update() 8\n");
    if (toChargeStation->isCompleted(this)) {
      //fprintf(stdout, "Drone::update() 9\n");
      delete toChargeStation;
      toChargeStation = nullptr;
      charging = false;
      station = nullptr;
      charge = 100;
      model->updateBatteryPercent(charge);
      createMessage(name + std::to_string(id) + " has recharged\n");
    }
  }
}

void Drone::attach(IObserver *observer) {
  list_observer_.push_back(observer);
}

void Drone::detach(IObserver *observer) {
  list_observer_.remove(observer);
}

bool Drone::hasObserver() {
  return list_observer_.size() != 0;
}

void Drone::notify() {
  std::list<IObserver*>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->update(message_);
    ++iterator;
  }
}

void Drone::createMessage(std::string message) {
  message_ = message;
  notify();
}

double Drone::getCharge() {
  //fprintf(stdout, "Drone::getCharge(): %f", charge);
  return charge;
}

void Drone::setCharge(double level) {
  charge = level;
  model->updateBatteryPercent(charge);
}

bool Drone::isCharging() {
  return charging;
}

void Drone::recharge() {
  fprintf(stdout, "Drone::recharge()\n");
  charging = true;
  station = (ChargeStation*) model->findEntity("chargestation");
  toChargeStation =
    new SpinDecorator(
      new BatteryDecorator(
        new BeelineStrategy(
          position,
          station->getPosition())));
}