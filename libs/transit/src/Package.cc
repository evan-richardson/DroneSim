#include "Package.h"

#include "Robot.h"

Package::Package(JsonObject &obj) : IEntity(obj) {
}

Vector3 Package::getDestination() const {
  return destination;
}

std::string Package::getStrategyName() const {
  return strategyName;
}

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::update(double dt) {}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery = false;
  destination = owner->getPosition();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

Robot* Package::getOwner() {
  return owner;
}

std::string Package::getDestinationString() {
  std::string coordinates = "(";

  std::string coordinateVal = "";
  std::string::size_type loc;

  coordinateVal = std::to_string(destination.x);
  loc = coordinateVal.find(".");
  coordinateVal = coordinateVal.substr(0, loc);

  coordinates += coordinateVal + ", ";

  coordinateVal = std::to_string(destination.y);
  loc = coordinateVal.find(".");
  coordinateVal = coordinateVal.substr(0, loc);

  coordinates += coordinateVal + ", ";

  coordinateVal = std::to_string(destination.z);
  loc = coordinateVal.find(".");
  coordinateVal = coordinateVal.substr(0, loc);

  coordinates += coordinateVal + ")";

  return coordinates;
}

std::string Package::getPositionString() {
  std::string coordinates = "(";

  std::string coordinateVal = "";
  std::string::size_type loc;

  coordinateVal = std::to_string(position.x);
  loc = coordinateVal.find(".");
  coordinateVal = coordinateVal.substr(0, loc);

  coordinates += coordinateVal + ", ";

  coordinateVal = std::to_string(position.y);
  loc = coordinateVal.find(".");
  coordinateVal = coordinateVal.substr(0, loc);

  coordinates += coordinateVal + ", ";

  coordinateVal = std::to_string(position.z);
  loc = coordinateVal.find(".");
  coordinateVal = coordinateVal.substr(0, loc);

  coordinates += coordinateVal + ")";

  return coordinates;
}
