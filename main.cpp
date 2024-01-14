#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "Game.h"

int main() {
    hideCursor();
    bool start = true;
    bool isGame = true;

    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    Player player{};
    player.setName(name);
    player.setLocation(25, 23);
    player.setHealth(3);
    player.setScore(0);

    Game game{};
    system("cls");
    Map map;
    map.initMap();
    while (start) {
        game.run(map, player, isGame);
        game.play(player, start, isGame);
    }

    return 0;
}
