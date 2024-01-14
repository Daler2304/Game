#pragma once

#include <windows.h>
#include <vector>
#include <ctime>
#include "Enemy.h"
#include "Bullet.h"
#include "Map.h"
#include "Player.h"



class Game {
private:
    std::vector<Enemy> enemies;
    std::vector<time_t> enemyTime;
    std::vector<Bullet> bullets;
    int playerX, playerY;
    int temporaryTime = 0;
    int enemyX, enemyY;
    int bulletX, bulletY;
public:
    void createBullet(int& playerX, int& playerY);
    void moveBullet();
    void checkBulletLocation();
    void shooting();
    void printBullet();

    void createEnemy(bool& isGame);
    void showEnemy(bool& isGame);
    void delEnemy(Player& player);

    void run(Map& map, Player& player, bool& isGame);
    void play(Player& player, bool& start, bool& isGame);
    void gameOver(Player& player, bool& start, bool& isGame);
};

void gotoxy(int x, int y);

void hideCursor();