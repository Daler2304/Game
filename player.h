#pragma once
#include "Location.h"
#include <string>

class Player : public Location {
private:
    std::string name;
    char nick = char(127);
    int health = 3;
    int score = 0;

public:
    void setName(const std::string& name);
    std::string getName() const;
    char getNick() const;
    void setHealth(int health);
    int getHealth() const;
    void setScore(int score);
    int getScore() const;
};
