#ifndef CHARGE_STATION_H_
#define CHARGE_STATION_H_

#include "IEntity.h"

/**
 *@brief Charge Station in a physical system, used to charge drones.
 **/
class ChargeStation : public IEntity {
  public:
    /**
     * @brief Constructor
     * @param details JSON object containing the charge station's information
     */
    ChargeStation(JsonObject& details);

    /**
     * @brief Destructor for ChargeStation class.
     */
    ~ChargeStation();

    /**
     * @brief Updates the charge station's position
     * @param dt Delta time
     */
    void update(double dt);
};

#endif
