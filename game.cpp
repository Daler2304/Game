#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

void Game::createBullet(int& playerX, int& playerY) {
    Bullet bullet;
    bullet.setLocation(playerX, playerY - 1);
    bullets.push_back(bullet);
}

void Game::moveBullet() {
    if (bullets.size() > 0) {
        for (int i = 0; i < bullets.size(); i++) {
            int bulletX = 0, bulletY = 0;
            bullets[i].getLocation(bulletX, bulletY);
            gotoxy(bulletX, bulletY);
            std::cout << bullets[i].getBullet();
            bullets[i].setLocation(bulletX, bulletY - 1);
        }
    }
}

void Game::checkBulletLocation() {
    int i = 0;
    while (i < bullets.size()) {
        int bulletX, bulletY;
        bullets[i].getLocation(bulletX, bulletY);
        if (bulletY == 0) {
            bullets.erase(bullets.begin() + i);
        }
        else {
            i++;
        }
    }
}

void Game::shooting() {
    moveBullet();
    checkBulletLocation();
}

void Game::printBullet() {
    gotoxy(52, 5);
    std::cout << bullets[0].getBullet();
}

void Game::createEnemy(bool& isGame) {
    if (isGame) {
        time_t currentTime = time(0);
        if (currentTime - temporaryTime > 2) {
            Enemy newEnemy;
            newEnemy.setLocation(rand() % 45 + 1, rand() % 22 + 1);
            enemies.push_back(newEnemy);
            enemyTime.push_back(currentTime);
            temporaryTime = currentTime;
        }
    }
}

void Game::showEnemy(bool& isGame) {
    if (isGame) {
        time_t currentTime = time(0);
        for (int i = 0; i < enemyTime.size(); i++) {
            int enemyX, enemyY;
            enemies[i].getLocation(enemyX, enemyY);
            if (currentTime - enemyTime[i] > 3) {
                gotoxy(enemyX, enemyY);
                cout << enemies[i].getSymbol();
            }
        }
    }
}

void Game::delEnemy(Player& player) {
    time_t currentTime = time(0);
    int i = 0;
    int enemyX, enemyY;
    int bulletX, bulletY;

    while (i < enemies.size()) {
        enemies[i].getLocation(enemyX, enemyY);

        if (currentTime - enemyTime[i] > 6) {
            enemies.erase(enemies.begin() + i);
            enemyTime.erase(enemyTime.begin() + i);
        }
        else {
            if (bullets.size() > i) {
                bullets[i].getLocation(bulletX, bulletY);

                if (enemyX == bulletX && enemyY == bulletY) {
                    enemies.erase(enemies.begin() + i);
                    bullets.erase(bullets.begin() + i);
                    enemyTime.erase(enemyTime.begin() + i);
                    int score = player.getScore() + 1;
                    player.setScore(score);
                }
                else {
                    i++;
                }
            }
            else {
                i++;
            }
        }
    }
}

void Game::run(Map& map, Player& player, bool& isGame) {
    createEnemy(isGame);
    Sleep(1);
    gotoxy(0, 0);
    map.mapDraw();
    player.getLocation(playerX, playerY);
    gotoxy(playerX, playerY);
    cout << player.getNick();

    //INFO
    gotoxy(52, 0);
    cout << player.getName();
    gotoxy(52, 1);
    cout << "Score: " << player.getScore();
    gotoxy(52, 2);
    cout << "Health: " << player.getHealth();
}

void Game::play(Player& player, bool& start, bool& isGame) {
    showEnemy(isGame);
    delEnemy(player);

    shooting();

    if (player.getHealth() > 0) {
        if (playerX == 0 || playerY == 0 || playerX == 49 || playerY == 24) {
            int health = player.getHealth() - 1;
            player.setHealth(health);
            playerX = 25;
            playerY = 23;
            player.setLocation(playerX, playerY);
        }
        else {
            if (_kbhit()) {
                char c = _getch();
                switch (c) {
                case 'a':
                    playerX--;
                    player.setLocation(playerX, playerY);
                    break;

                case 'd':
                    playerX++;
                    player.setLocation(playerX, playerY);
                    break;
                case ' ':
                    createBullet(playerX, playerY);
                }

            }
        }
    }
    else {
        gameOver(player, start, isGame);
    }
}

void Game::gameOver(Player& player, bool& start, bool& isGame) {
    isGame = false;
    gotoxy(21, 11);
    std::cout << "Game Over!";
    gotoxy(22, 12);
    std::cout << "Restart?";
    gotoxy(23, 13);
    std::cout << "y/n";

    if (_kbhit()) {
        char c = _getch();
        switch (c) {
        case 'y':
            start = true;
            isGame = true;
            playerX = 25;
            playerY = 23;
            player.setLocation(playerX, playerY);
            player.setHealth(3);
            player.setScore(0);
            gotoxy(52, 1);
            cout << "Score:                        " << endl;
            break;

        case 'n':
            start = false;
            gotoxy(0, 26);
            break;
        }
    }
}

void gotoxy(int x, int y) {
    COORD coord{};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(handle, &cci);
    cci.bVisible = false;
    SetConsoleCursorInfo(handle, &cci);
}
