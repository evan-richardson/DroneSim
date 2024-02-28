#define _USE_MATH_DEFINES
#include "ChargeStation.h"

#include <cmath>
#include <limits>

ChargeStation::ChargeStation(JsonObject& details) : IEntity(details) {}

ChargeStation::~ChargeStation() {}

void ChargeStation::update(double dt) {}