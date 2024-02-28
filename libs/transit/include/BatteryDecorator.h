#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IStrategy.h"

class Drone;

/**
 * @brief this class inhertis from the IStrategy class and represents
 * a battery decorator where the drone will move with respect to a battery charge
 */
class BatteryDecorator : public IStrategy {
  protected:
    IStrategy* strategy = nullptr;

  public:
    /**
     * @brief Construct a new Battery Decorator object
     *
     * @param[in] strategy the strategy to decorate onto
     */
    BatteryDecorator(IStrategy* strategy);

    /**
     * @brief Battery Destructor
     */
    ~BatteryDecorator();

    /**
     * @brief Move the entity with the behavior as described.
     * 
     * @param entity Entity to move
     * @param dt Delta Time
     */
    void move(IEntity* entity, double dt);

    /**
     * @brief Check if the movement is completed by checking the time.
     * @param entity Entity being moved
     * @return True if complete, false if not complete
     */
    bool isCompleted(IEntity* entity);
};

#endif // BATTERY_DECORATOR_H_
