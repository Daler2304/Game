#include "Player.h"

void Player::setName(const std::string& name) {
    this->name = name;
}

std::string Player::getName() const {
    return name;
}

char Player::getNick() const {
    return nick;
}

void Player::setHealth(int health) {
    this->health = health;
}

int Player::getHealth() const {
    return health;
}

void Player::setScore(int score) {
    this->score = score;
}

int Player::getScore() const {
    return score;
}
