#include<iostream>
#include<windows.h>
#include<conio.h>
#include<vector>
using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false; // Устанавливаем видимость курсора в false
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

class Map {
private:
    int width = 60;
    int height = 20;
    char matrixMap[20][60];
    string map;
public:
    void initialization() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    matrixMap[i][j] = '#';
                } else {
                    matrixMap[i][j] = ' ';
                }
                map.push_back(matrixMap[i][j]);
            }
            map.push_back('\n');
        }
    }

    void draw() {
        cout<<map;
    }
};

class Player {
private:
    string name;
    int health;
    int point;
    char nick = 'O';

public:
    char getNick() {
        return nick;
    }
    void setName(string name) {
        this->name = name;
    }

    string getName() {
        return name;
    }

    void setHealth(int& health) {
        this->health = health;
    }

    int getHealth() {
        return health;
    }

    void setPoint(int& point) {
        this->point = point;
    }

    int getPoint() {
        return point;
    }
};

class Armor {
private:
    string name;
    int health;

public:
    string getArmorName() {
        return name;
    }

    int getArmorHealth() {
        return health;
    }
};

class Magic {
private:
    int energy;
    char food = char(253);
public:
    int getMagicEnergy() {
        return energy;
    }
    void setEnergy(int& energy){
        this->energy = energy;
    }

    char getFood() {
        return food;
    }
};

class Location {
private:
    int playerX = 30;
    int playerY = 10;
    int foodX;
    int foodY;
public:
    void getLocation(int& playerX, int& playerY) {
        playerX = this->playerX;
        playerY = this->playerY;
    }

    void setLocation(int& playerX, int& playerY) {
        this->playerX = playerX;
        this->playerY = playerY;
    }
};


class Game {
public:
    Location location;
    Player player;
    int playerX;
    int playerY;
    
    void gameOver(bool& start) {
        gotoxy(25, 10);
        cout<<"Game Over"<<endl;
        gotoxy(26, 11);
        cout<<"Restart?"<<endl;
        gotoxy(28, 12);
        cout<<"Y/N?"<<endl;
        if(_kbhit()) {
            char c = _getch();
            switch (c) {
                case 'y':
                    playerX = 30;
                    playerY = 10;
                    location.setLocation(playerX, playerY);
                    break;
                case 'n':
                    start = false;
                    break;
            }
        }
    }

    void run() {
        Sleep(1);
        Map mapDraw;
        mapDraw.initialization();
        gotoxy(0, 0);
        mapDraw.draw();
        location.getLocation(playerX, playerY);
        gotoxy(playerX, playerY);
        cout<<player.getNick();
        
        gotoxy(62, 0);
        cout<<"x:" << playerX << " y:" << playerY << "  " <<endl;
        gotoxy(62, 1);
        string name = player.getName();
        cout<<name;
    }

    void play(bool& start) {
        location.getLocation(playerX, playerY);
        if(playerX == 0 || playerX == 59 || playerY == 0 || playerY == 19) {
            gameOver(start);
        } else {
            if(_kbhit()) {
                char c = _getch();
                switch (c) {
                    case 'a':
                        if(playerX > 0) {
                            playerX--;
                            location.setLocation(playerX, playerY);
                        }
                        break;
                    case 'd':
                        if(playerX < 59){
                            playerX++;
                            location.setLocation(playerX, playerY);
                        }
                        break;
                    case 'w':
                        if(playerY > 0) {
                            playerY--;
                            location.setLocation(playerX, playerY);
                            }
                        break;
                    case 's':
                        if (playerY < 19) {
                            playerY++;
                            location.setLocation(playerX, playerY);
                        }
                        break;
                    case ' ':
                        cout << "Label";
                        break;
                
                }
            }
        }
    }
};

int main() {
    hideCursor();

    Player player;
    string name;
    cout << "Enter your name: ";
    cin >> name;
    player.setName(name);

    system("cls");
    Game game;
    bool start = true;
    while (start) {
        game.run();
        game.play(start);
    }
    system("pause");
    return 0;
}