#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {}

void PathStrategy::move(IEntity* entity, double dt) {
  //fprintf(stdout, "PathStrategy::move() 1\n");
  if (isCompleted(entity))
    return;

  Vector3 vi(path[index][0], path[index][1], path[index][2]);
  Vector3 dir = (vi - entity->getPosition()).unit();

  entity->setPosition(entity->getPosition() + dir*entity->getSpeed()*dt);
  entity->setDirection(dir);

  if (entity->getPosition().dist(vi) < 4)
    index++;
}

bool PathStrategy::isCompleted(IEntity* entity) {
  //fprintf(stdout, "PathStrategy::isCompleted() 1\n");
  return index >= path.size();
}
