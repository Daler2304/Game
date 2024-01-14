#pragma once
#include "Location.h"

class Enemy : public Location {
private:
    char sym = char(253);
public:
    char getSymbol() const;
};
