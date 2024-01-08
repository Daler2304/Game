#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<ctime>
#include<tuple>


using namespace std;


static void hideCursor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = false;
	SetConsoleCursorInfo(handle, &cci);
}

static void gotoxy(int x, int y) {
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


class Map {
private:
	int width = 50;
	int height = 25;
	string MAP = "";
	char map[25][50];
public:
	void initMap() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (i == 0 || j == 0 || j == width - 1 || i == height - 1) {
					map[i][j] = '#';
				}
				else {
					map[i][j] = ' ';
				}
				MAP.push_back(map[i][j]);
			}
			MAP.push_back('\n');
		}
	}

	void mapDraw() const {
		cout << MAP;
	}
};


class Location {
private:
	int x, y;
public:
	void setLocation(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void getLocation(int& x, int& y) const {
		x = this->x;
		y = this->y;
	}
};


class Player : public Location {
private:
	string name;
	char nick = char(127);
	int health = 3;
	int score = 0;
	
public:

	void setName(string& name) {
		this->name = name;
	}

	string getName() const {
		return name;
	}

	char getNick() const {
		return nick;
	}

	void setHealth(int health) {
		this->health = health;
	}

	int getHealth() const {
		return health;
	}

	void setScore(int score) {
		this->score = score;
	}

	int getScore() const {
		return score;
	}
};


class Enemy : public Location {
private:
	char sym = char(253);
public:
	void setDamage(Player& player) {
		int hp = player.getHealth() - 1;
		player.setHealth(hp);
	}

	char getSymbol() const {
		return sym;
	}
};

class Bullet : public Location{
private:
	char bullet = '*';
	time_t bulletTime;
public:
	char getBullet() const {
		return bullet;
	}
};


class Game {
private:
	vector<Enemy> enemies;
	vector<time_t> enemyTime;
	vector<Bullet> bullets;
public:
	void createBullet(int& playerX, int& playerY) {
		Bullet bullet;
		bullet.setLocation(playerX, playerY - 1);
		bullets.push_back(bullet);
	}

	void moveBullet() {
		if (bullets.size() > 0) {
			for (int i = 0; i < bullets.size(); i++) {
				int bulletX, bulletY;
				bullets[i].getLocation(bulletX, bulletY);
				gotoxy(bulletX, bulletY);
				cout << bullets[i].getBullet();
				bullets[i].setLocation(bulletX, bulletY - 1);
			}
		}
	}

	void checkBulletLocation() {
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

	void shooting() {
		
		moveBullet();
		checkBulletLocation();
	}

	void printBullet() {
		gotoxy(52, 5);
		cout << bullets[0].getBullet();
	}


	int playerX, playerY;
	int temporaryTime = 0;
	void createEnemy(bool& isGame) {
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

	void showEnemy(bool& isGame) {
		if(isGame){
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
	
	void delEnemy(Player& player) {
		time_t currentTime = time(0);
		int i = 0;
		int enemyX, enemyY;
		int bulletX, bulletY;

		while (i < enemies.size()) {
			enemies[i].getLocation(enemyX, enemyY);

			// Check if the enemy has been alive for more than 6 seconds
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
						int score = player.getScore() + rand() % 3 + 1;
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

	void run(Map& map, Player& player, bool& isGame) {
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

	void play(Player& player, bool& start, bool& isGame) {
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

	void gameOver(Player& player, bool& start, bool& isGame) {
		
		isGame = false;
		gotoxy(21, 11);
		cout << "Game Over!";
		gotoxy(22, 12);
		cout << "Restart?";
		gotoxy(23, 13);
		cout << "y/n";

		if (_kbhit()) {
			char c = _getch();
			switch (c) {
			case 'y':
				start = true;
				playerX = 25;
				playerY = 23;
				player.setLocation(playerX, playerY);
				player.setHealth(3);
				player.setScore(0);
				break;

			case 'n':
				start = false;
				gotoxy(0, 26);
				break;
			}
		}
	}
};


int main() {
	hideCursor();
	bool start = true;
	bool isGame = true;

	string name;
	cout << "Enter your name: ";
	cin >> name;

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
