#ifndef I_OBSERVER_H_
#define I_OBSERVER_H_
#include <string>

/**
 * @class IObserver
 * @brief Represents a generic observer class. 
 * All observers inherit from IObserver.
 * The base class stores, passes, and resets the message for the subclass.
 */
class IObserver {
 public:
  /**
   * @brief DroneObservers consist of a stored message_ string that is empty upon creation.
   */
  IObserver();

  /**
   * @brief destructor
   */
  virtual ~IObserver();

  /**
   * @brief returns the string stored in message_
   *
   * @return the stored message
   */
  std::string getMessage();

  /**
   * @brief resets message_ to an empty string
   */
  void clearMessage();

  /**
   * @brief sets message_ to the contents of the message parameter
   * @param message the new message_
   */
  virtual void update(const std::string &message) = 0;

 protected:
  std::string message_ = "";
};

#endif
