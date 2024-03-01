#pragma once

#include "Location.h"

class Bullet : public Location {
private:
    char bullet = '*';

public:
    char getBullet() const;
};
