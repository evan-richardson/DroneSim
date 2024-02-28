#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "IObserver.h"
#include <list>
#include "math/vector3.h"

class ChargeStation;
class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();


  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief attaches an observer to this drone
   */
  void attach(IObserver *observer);

  /**
   * @brief detaches an observer from this drone
   */
  void detach(IObserver *observer);

  /**
   * @brief returns whether there is an observer attached to this drone
   * 
   * @return true if there is at least one observer, false otherwise
   */
  bool hasObserver();

  /**
   * @brief passes the string contained within the private message_ variable 
   * to every observer attached to this drone
   */
  void notify();

  /**
   * @brief sets private variable message_ with parameter message
   * @param message later passed to the observer
   */
  void createMessage(std::string message);

  /**
   * @brief Returns the current level of this battery.
   * 
   * @returns Double level of battery
   */
  double getCharge();

  /**
   * @brief Set the battery level.
   *
   * @param level battery level
   */
  void setCharge(double level);

   /**
   * @brief Checks if drone is in the process of charging.
   *
   * @return True if drone is moving to charge station, otherwise false
   */
  bool isCharging();

   /**
   * @brief Find and begin moving to a nearby charge station.
   */
  void recharge();

 private:
  bool available = false;
  bool pickedUp = false;
  bool charging = false;
  double charge;
  ChargeStation* station = nullptr;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  IStrategy* toChargeStation = nullptr;
  std::list<IObserver*> list_observer_;
  std::string message_;
};

#endif
