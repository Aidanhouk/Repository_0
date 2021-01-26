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

void mainGame()
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// ���� ����
	sf::RenderWindow window(sf::VideoMode(W * (COLS + 2), W * ROWS), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	// ����� ���������� ���
	window.setFramerateLimit(60);

	// ������ ����
	Field field(level);
	// ������� ������
	field.makeRoad();
	// ������� ������ ����� ��� ������
	sf::Texture emptyBlockTexture;
	emptyBlockTexture.loadFromFile("images/field/emptyBlock.png");
	sf::Sprite spriteBack(emptyBlockTexture);

	// ������ ����� �����������, � ���������� - ������� ����� � ������� �������� ����; ������� ��������� �����
	EnemiesWave enemiesWave(1, 8);
	// ������ ��� ���������� �������
	TowersControl towerControl;
	// ������ ��� ������ �� ���������
	Missiles missiles;
	// ����� ��� ���������� ������� �� ������
	BlocksControl blocksControl(field);
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

	// ������� ���� ����
	while (window.isOpen())
	{
		// �������� ���������� ������� ����
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x{ pos.x / W };
		int y{ pos.y / W };

		sf::Event event;
		// ���������� �������
		while (window.pollEvent(event))
		{
			// �������� ����
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			// ���� ������ ������ ���� � ���� �� ���������
			if (event.type == sf::Event::MouseButtonPressed && !endOfGame) {
				// ���������� ��� �������� ������� �� ����� ��� �������
				bool towerSelected{ 0 };
				if (x < COLS) {
					// ������� ����� �� ����
					if (field.getCell(y, x) == 2) {
						towerSelected = 1;
						// ���� ����� ��� ���� �������, �� ������� ��
						if (clickedTowerCoord.first == y && clickedTowerCoord.second == x) {
							money += towerControl.deleteTower(y, x);
							clickedTowerCoord.first = -1;
							clickedTowerCoord.second = -1;
							field.getCell(y, x) = 0;
						}
						// �������� �����
						else {
							clickedTowerCoord.first = y;
							clickedTowerCoord.second = x;
						}
					}
					else {
						clickedTowerCoord.first = -1;
						clickedTowerCoord.second = -1;
					}
				}
				// ���� ������� �����/���� � ��������
				if (blockType && !towerSelected) {
					// ���� ������ �� ������� ����
					if (x < COLS) {
						// ���� ������� �����
						if (blockType < TOWERS_COUNT) {
							// ���� ��� ������ ������
							if (!field.getCellValue(y, x)) {
								if (money >= TOWERS_PRICE[blockType]) {
									towerControl.addTower(y, x, blockType);
									money -= TOWERS_PRICE[blockType];
									field.getCell(y, x) = 2;
									blockType = 0;
								}
							}
						}
						// ���� ������ ����
						else {
							// ���� ��� ������ ������
							if (field.getCellValue(y, x) == 1) {
								if (money >= BLOCKS_PRICE[blockType - TOWERS_COUNT + 1]) {
									// ���� ���������� ��������� ����
									if (blocksControl.placeBlockOnField(y, x, blockType - TOWERS_COUNT + 1)) {
										money -= BLOCKS_PRICE[blockType - TOWERS_COUNT + 1];
										field.getCell(y, x) = 3;
										blockType = 0;
									}
								}
							}
						}
					}
				}
				// ��������� ������� �� ������ � ����� � ��������
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
					case 8:
						pause = !pause;
						if (!pause) {
							resetTimeToSpawn();
						}
						break;
					case 9:
						// ������ ���� �� ����� ��� ������� � �����
						if (x == COLS + 1) {
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
						break;
					}
				}
			}
		}

		if (!endOfWave && !pause) {
			// ����� �����������
			spawnNextEnemyCycle(enemiesWave, field);
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

		window.clear();
		// ���
		window.draw(spriteBack);
		// ������ ������ + �����
		field.paintRoad(window);
		// ������ ����� �� ������
		blocksControl.drawAllBlocks(window);

		// ������ �����
		towerControl.drawAllTowers(window);

		// ����� �������� + ���������
		if (!endOfWave) {
			// ������������ ������� 
			if (!pause) {
				towerControl.towersShoot(field, missiles);
			}
			// ������ ��������
			missiles.drawMissiles(window);
			// ������ ���� ������
			enemiesWave.drawAllEnemies(window);
		}

		// �������� ��������� �����
		if (clickedTowerCoord.first != -1) {
			towerControl.markTowerToDelete(window, clickedTowerCoord.first, clickedTowerCoord.second);
		}

		// ������ ������� ��������
		shop.drawShop(enemiesWave.getLevel(), enemiesWave.getMaxLevel(), blockType, window);

		window.display();

		// ���� ���� ��������, �� �������
		if (endOfGame) {
			// ���� ��������� = 0, �� ���� ���������
			if (!result) {
				result = 2;
			}
			waveLevel = enemiesWave.getLevel();
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			window.close();
		}
	}
}