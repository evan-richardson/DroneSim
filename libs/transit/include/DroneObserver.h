#ifndef DRONE_OBSERVER_H_
#define DRONE_OBSERVER_H_

#include "IObserver.h"
#include "Drone.h"

/**
 * @class DroneObserver
 * @brief Represents an observer used to track Drones.
 * A DroneObserver attaches itself to a Drone upon creation.
 * Messages are then sent from the Drone, to the DroneObserver,
 * and then to the SimulationModel
 */
class DroneObserver : public IObserver {
 public:
  /**
   * @brief DroneObservers are created with a Drone attached
   * @param drone the drone this observer is tracking
   */
  DroneObserver(Drone &drone);

  /**
   * @brief destructor
   */
  virtual ~DroneObserver();

  /**
   * @brief updates the current message_ stored by the observer to the message parameter
   * @param message the message to be stored
   */
  void update(const std::string &message);

  /**
   * @brief detaches this observer from the drone_
   */
  void removeFromList();

 private:
  Drone &drone_;
};

#endif
