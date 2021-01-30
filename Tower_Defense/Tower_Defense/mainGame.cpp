#include "mainGame.h"

#include <thread>

#include "consts.h"
#include "globals.h"
#include "cycleFuncions.h"
#include "field.h"
#include "enemiesWave.h"
#include "towersControl.h"
#include "missiles.h"
#include "blocksControl.h"
#include "shop.h"

#include <SFML/Audio.hpp>

// �������� ����
bool gameSpeed;
// �����?
bool pause;
// ��������� ����
int result;
// ����� ������� ������
int level;
// �� ����� ����� ����������� ����
int waveLevel;
// ���-�� �����
int money;
// ����
Field * field;
// ����
sf::RenderWindow * window;

void mainGame()
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// ���� ����
	sf::RenderWindow _window(sf::VideoMode(W * (COLS + 2), W * (ROWS + 1)), "Tower defense", sf::Style::Titlebar | sf::Style::Close);
	window = &_window;

	// ����� ���������� ���
	(*window).setFramerateLimit(60);

	// ������ ����
	Field _field(level);
	field = &_field;
	// ������� ������
	(*field).makeRoad();
	// ������� ������ ����� ��� ������
	sf::Texture emptyBlockTexture;
	emptyBlockTexture.loadFromFile("images/field/emptyBlock.png");
	sf::Sprite spriteBack(emptyBlockTexture);

	// ������ ����� �����������, � ���������� - ������� ����� � ������� �������� ����; ������� ��������� �����
	EnemiesWave enemiesWave(1, 10);
	// ������ ��� ���������� �������
	TowersControl towerControl;
	// ������ ��� ������ �� ���������
	Missiles missiles;
	// ����� ��� ���������� ������� �� ������
	BlocksControl blocksControl;
	// ������ ��������
	Shop shop;

	// ����������� ������
	money = START_MONEY[level];
	// ����� ����?
	bool endOfGame{ 0 };
	// ����� �����?
	bool endOfWave{ 1 };
	// ��� �����/�����, �� ������� ����� ����� � ��������
	int blockType{ 0 };
	// ���������� �����, ������� ������ ����� (��� ��������)
	std::pair<int, int> clickedTowerCoord;
	clickedTowerCoord.first = -1;
	clickedTowerCoord.second = -1;

	// ���������� ��������� ��������� (�����, �������� ����)
	setToDefault();

	sf::Music music;
	if (level == 0) {
		pause = 0;
		music.openFromFile("sounds/secretSong.ogg");
		music.play();
	}

	// ������� ���� ����
	while ((*window).isOpen())
	{
		// �������� ���������� ������� ����
		sf::Vector2i pos = sf::Mouse::getPosition(*window);
		int x{ pos.x / W };
		int y{ pos.y / W };

		sf::Event event;
		// ���������� �������
		while ((*window).pollEvent(event))
		{
			// �������� ����
			if (event.type == sf::Event::Closed) {
				(*window).close();
			}
			// ���� ������ ������ ���� � ���� �� ���������
			if (event.type == sf::Event::MouseButtonPressed) {
				// 1 ���������� ��� �������� ������� �� �����/���� ��� �������
				bool towerSelected{ 0 };
				if (x < COLS && y < ROWS) {
					// ������� �����/���� �� ����
					switch ((*field).getCellValue(y, x))
					{
					case 2:
					case 3:
						towerSelected = 1;
						// ���� �����/���� ��� ���� �������, �� ������� ��
						if (clickedTowerCoord.first == y && clickedTowerCoord.second == x) {
							if ((*field).getCellValue(y, x) == 2) {
								money += towerControl.deleteTower(y, x);
								(*field).removeTowerFromCell(y, x);
								(*field).setCellValue(y, x, 0);
								towerControl.checkTowersForBuffs();
							}
							else {
								money += blocksControl.deleteBlock(y, x);
								(*field).setCellValue(y, x, 1);
							}
							clickedTowerCoord.first = -1;
							clickedTowerCoord.second = -1;
						}
						// �������� �����/����
						else {
							clickedTowerCoord.first = y;
							clickedTowerCoord.second = x;
						}
						break;
					default:
						clickedTowerCoord.first = -1;
						clickedTowerCoord.second = -1;
						break;
					}
				}
				// 2 ���� ������� �����/���� � ��������
				if (blockType && !towerSelected) {
					// ���� ������ ������ ����
					if (x < COLS && y < ROWS) {
						// ���� ������� �����
						if (blockType < TOWERS_COUNT) {
							// ���� ��� ������ ������
							if (!(*field).getCellValue(y, x)) {
								if (money >= TOWERS_PRICE[blockType]) {
									towerControl.addTower(y, x, blockType);
									(*field).setCellValue(y, x, 2);
									money -= TOWERS_PRICE[blockType];
									towerControl.checkTowersForBuffs();
									blockType = 0;
								}
							}
						}
						// ���� ������ ����
						else {
							// ���� ��� ������ ������
							if ((*field).getCellValue(y, x) == 1) {
								if (money >= BLOCKS_PRICE[blockType - TOWERS_COUNT + 1]) {
									// ���� ���������� ��������� ����
									if (blocksControl.placeBlockOnField(y, x, blockType - TOWERS_COUNT + 1)) {
										(*field).setCellValue(y, x, 3);
										money -= BLOCKS_PRICE[blockType - TOWERS_COUNT + 1];
										blockType = 0;
									}
								}
							}
						}
					}
				}
				// 3 ��������� ������� �� ������ � ����� � ��������
				if (x >= COLS) {
					clickedTowerCoord.first = -1;
					clickedTowerCoord.second = -1;
					switch (y)
					{
					case 1:
						if (x == COLS) {
							blockType = 1;
						}
						else {
							blockType = 2;
						}
						break;
					case 2:
						if (pos.y % W >= (W >> 1)) {
							if (x == COLS) {
								blockType = 3;
							}
							else {
								blockType = 4;
							}
						}
						break;
					case 3:
						if (pos.y % W < (W >> 1)) {
							if (x == COLS) {
								blockType = 3;
							}
							else {
								blockType = 4;
							}
						}
						break;
					case 4:
						if (x == COLS) {
							blockType = 5;
						}
						else {
							blockType = 6;
						}
						break;
					case 5:
						if (pos.y % W >= (W >> 1)) {
							if (x == COLS) {
								blockType = 7;
							}
							else {
								blockType = 8;
							}
						}
						break;
					case 6:
						if (pos.y % W < (W >> 1)) {
							if (x == COLS) {
								blockType = 7;
							}
							else {
								blockType = 8;
							}
						}
						break;
					case 7:
						if (x == COLS) {
							blockType = 9;
						}
						else {
							blockType = 10;
						}
						break;
					case 8:
						break;
					case 9:
					case 10:
						// ������ ���� �� ����� ��� ������� � �����
						pause = !pause;
						if (!pause) {
							resetTimeToSpawn();
						}
						break;
					}
				}
				// 4 ������� � ������ �������
				if (y == ROWS) {
					if (x == COLS - 1) {
						// �������� ����
						if (!gameSpeed) {
							gameSpeed = 1;
						}
						// ��������� ����
						else {
							gameSpeed = 0;
						}
						enemiesWave.changeEnemiesSpeed();
						enemiesWave.changeEnemiesDamage();
						towerControl.changeTowersDamage();
					}
				}
			}
		}

		if (!endOfWave && !pause) {
			// ����� �����������
			spawnNextEnemyCycle(enemiesWave);
		}
		// ���� ������ �� ��������, ����������� �����
		if (!enemiesWave.getEnemiesLeft()) {
			endOfWave = 1;
		}
		// �������� ����� �����
		if (endOfWave && !pause) {
			waveBreakCycle(enemiesWave, endOfGame, endOfWave);
		}
		// ���������� ���������
		if (!endOfWave && !pause) {
			endOfGame = enemiesWave.moveAllEnemies();
		}

		(*window).clear();
		// ���
		(*window).draw(spriteBack);
		// ������ ������ + �����
		(*field).paintRoad();
		// ������ ����� �� ������
		blocksControl.drawAllBlocks();

		// ������ �����
		towerControl.drawAllTowers();

		// ����� �������� + ���������
		if (!endOfWave) {
			// ������������ ������� 
			if (!pause) {
				towerControl.towersShoot(missiles);
			}
			// ������ ��������
			missiles.drawMissiles();
			// ������� � ���������� ����� � �����
			if (enemiesWave.getEnemiesLeft() == 1) {
				enemiesWave.drawLastEnemyEffects();
			}
			// ������ ���� ������
			enemiesWave.drawAllEnemies();
		}

		// �������� ��������� �����/����
		if (clickedTowerCoord.first != -1) {
			towerControl.markTowerToDelete(clickedTowerCoord.first, clickedTowerCoord.second);
		}

		// ��������� �� ����� ��� ��������� ��������� �������� �����
		if (y < ROWS&& x < COLS && y >= 0 && x >= 0 && !endOfGame) {
			if ((*field).getTowerOnCell(y, x)) {
				(*field).drawRange(y, x);
			}
		}

		// ������ ������� ��������
		shop.drawShop(enemiesWave.getLevel(), enemiesWave.getMaxLevel(), blockType);

		(*window).display();

		// ���� ���� ��������, �� �������
		if (endOfGame) {
			// ���� ��������� = 0, �� ���� ���������
			if (!result) {
				result = 2;
			}
			waveLevel = enemiesWave.getLevel();
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			(*window).close();
		}
	}
}