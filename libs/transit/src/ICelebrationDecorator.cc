#include "ICelebrationDecorator.h"

ICelebrationDecorator::ICelebrationDecorator(IStrategy* strategy, double time) {
  this->strategy = strategy;
  this->time = time;
}

ICelebrationDecorator::~ICelebrationDecorator() {
  // Delete dynamically allocated variables
  if (strategy) delete strategy;
}

void ICelebrationDecorator::move(IEntity* entity, double dt) {
  if (!strategy->isCompleted(entity)) {
    strategy->move(entity, dt);
  } else if (!isCompleted(entity)) {
    celebrate(entity, dt);
    time -= dt;
  }
}

bool ICelebrationDecorator::isCompleted(IEntity* entity) {
  return time <= 0;
}

