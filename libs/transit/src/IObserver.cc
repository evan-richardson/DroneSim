#include "IObserver.h"

IObserver::IObserver() {}

IObserver::~IObserver() {}

std::string IObserver::getMessage() {
    return message_;
}

void IObserver::clearMessage() {
    message_ = "";
}
