#include <iostream>
#include <conio.h>
#include <Windows.h>


using namespace std;

class Player {
private:
    string name;
    int health = 100;
public:
    
    void setName() {
        cout<<"Enter a char: ";
        cin>>name;
    }
    string getName() {
        return name;
    }
    int getHealth() {
        return health;
    }
    void setHealth(int health) {
        this->health = health;
    }
};

string map;
const int width = 80;
const int height = 20;
char matrixMap[height][width];


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void playOff(bool& flag, int& playerX, int& playerY, Player& player, string& stop) {
    if(playerX == 0 || playerX == 79 || playerY == 0 || playerY == 19) {
        int hp = player.getHealth();
        int damage = rand() % 33 + 1;
        int getDamage = hp - damage;
        if(getDamage > 0) {
            player.setHealth(getDamage);
            playerX = 40;
            playerY = 10;
	        string stop = "stop";
        }
        else {
            gotoxy(31, 10);
            cout<<"Game over..."<<endl;
            gotoxy(31, 11);
            cout<<"  Restart?";
            gotoxy(31, 12);
            cout<<"    Y/n: ";
            while(true){
                if(_kbhit()){
                    char c = _getch();
                    if(c == 'Y' || c == 'y') {
                        playerX = width / 2;  // начальные координаты игрока
                        playerY = height / 2;
                        player.setHealth(100);
                        break;
                    }else if (c == 'N' || c == 'n') {
                        flag = false;
                        break;
                    }else {
                        true;
                    }
                }
            }
        }
    }
}


int main() {
    Player player;
    player.setName();

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                matrixMap[i][j] = '#';
            }else {
                matrixMap[i][j] = ' ';
            }
            map.push_back(matrixMap[i][j]);
        }
        map.push_back('\n');
    }

    int playerX = width / 2;
    int playerY = height / 2;
    bool flag = true;
    
    while(flag == true) {
        Sleep(1);
        gotoxy(0, 0);
        cout << map;

        gotoxy(playerX, playerY);
        string nick = player.getName();
        cout << nick;

        if(_kbhit()) {
            char c = _getch();
            if(c == 'w' || c == 'W' || c == 72) {
                while(playerY > 0 && !_kbhit()) {
                    gotoxy(0, 0);
                    cout << map;
                    gotoxy(playerX, playerY);
                    string nick = player.getName();
                    cout << nick;
                    gotoxy(0, 22);
                    cout<<"                           ";
                    gotoxy(0, 22);
                    cout<<"Health: "<<player.getHealth()+" ";
                    Sleep(120);
                    playerY--;
		            string stop;
                    playOff(flag, playerX, playerY, player, stop);
                    if (stop == "stop") {
                        break;
                    }
                }
            }
            else if(c == 'a' || c == 'A' || c == 75) {
                while(playerX > 0 && !_kbhit()) {
                    gotoxy(0, 0);
                    cout << map;
                    gotoxy(playerX, playerY);
                    string nick = player.getName();
                    cout << nick;
                    gotoxy(0, 22);
                    cout<<"                           ";
                    gotoxy(0, 22);
                    cout<<"Health: "<<player.getHealth()+" ";
                    Sleep(70);
                    playerX--;
		            string stop;
                    playOff(flag, playerX, playerY, player, stop);
                    if (stop == "stop") {
                        break;
                    }
                }
            }
            else if (c == 's' || c == 'S' || c == 80) {
                while(playerY < 19 && !_kbhit()) {
                    gotoxy(0, 0);
                    cout << map;
                    gotoxy(playerX, playerY);
                    string nick = player.getName();
                    cout << nick;
                    
                    gotoxy(0, 22);
                    cout<<"                           ";
                    gotoxy(0, 22);
                    cout<<"Health: "<<player.getHealth()+" ";
                    Sleep(120);
                    playerY++;
		            string stop;
                    playOff(flag, playerX, playerY, player, stop);
                    if (stop == "stop") {
                        break;
                    }
                }
            }
            else if (c =='d' || c == 'D' || c == 77) {
                while (playerX < 79 && !_kbhit()) {
                    gotoxy(0, 0);
                    cout << map;
                    gotoxy(playerX, playerY);
                    string nick = player.getName();
                    cout << nick;
                    gotoxy(0, 22);
                    cout<<"                     ";
                    gotoxy(0, 22);
                    cout<<"Health: "<<player.getHealth() + " ";
                    Sleep(70);
                    playerX++;
		            string stop;
                    playOff(flag, playerX, playerY, player, stop);
                    if (stop == "stop") {
                        break;
                    }
                }   
            }
            else if (c == 'q' || c == 'Q') {
                flag = false;
                break;
            }
        }
    }
    gotoxy(0, 22);
    system("pause");
    return 0;
}