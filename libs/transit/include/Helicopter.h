#ifndef Helicopter_H_
#define Helicopter_H_

#include "IEntity.h"
#include "IStrategy.h"

class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopters are created with a name
   * @param obj JSON object containing the human's information
   */
  Helicopter(JsonObject& obj);

  /**
   * @brief Helicopter destructor
   */
  ~Helicopter();

  /**
   * @brief Updates the helicopter's position
   * @param dt Delta time
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif
