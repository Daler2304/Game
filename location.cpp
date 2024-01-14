#include "Location.h"

void Location::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

void Location::getLocation(int& x, int& y) const {
    x = this->x;
    y = this->y;
}
