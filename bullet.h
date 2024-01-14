#pragma once

#include "Location.h"
#include <ctime>

class Bullet : public Location {
private:
    char bullet = '*';
    time_t bulletTime;

public:
    char getBullet() const;
};
