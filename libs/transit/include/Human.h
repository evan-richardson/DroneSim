#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

class Human : public IEntity {
 public:
  /**
   * @brief Humans are created with a name
   * @param obj JSON object containing the human's information
   */
  Human(JsonObject& obj);

  /**
   * @brief Human destructor
   */
  ~Human();

  /**
   * @brief Updates the human's position
   * @param dt Delta time
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif
