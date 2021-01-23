#include "mainGame.h"

#include <thread>

#include "consts.h"
#include "cycleFuncions.h"
#include "field.h"
#include "enemiesWave.h"
#include "towersControl.h"
#include "missiles.h"
#include "blocksControl.h"
#include "shop.h"

void mainGame(int &result, int level, int &waveLevel)
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// ���� ����
	sf::RenderWindow window(sf::VideoMode(W * COLS, W * (ROWS + 1.5)), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

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

	// ������ ����� �����������, � ���������� - ������� ����� � ������� �������� ���� ����� 1
	EnemiesWave enemiesWave(0, 5);
	// ������ ��� ���������� �������
	TowersControl towerControl;
	// ������ ��� ������ �� ���������
	Missiles missiles;
	// ����� ��� ���������� ������� �� ������
	BlocksControl blocksControl(field);
	// ������ ��������
	Shop shop;

	// ����������� ������
	int money{ START_MONEY };
	// ��� �����/�����, �� ������� ����� ����� � ��������
	int blockType{ 0 };
	// ����� ����?
	bool endOfGame{ 0 };
	// ����� �����?
	bool endOfWave{ 1 };

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
				// ��������� ������� �� ����� � ����� � ��������
				if (y == ROWS) {
					if (x >= 0 && x < TOWERS_COUNT - 1) {
						if (money >= TOWERS_PRICE[x + 1]) {
							blockType = x + 1;
						}
					}
					if (x >= TOWERS_COUNT - 1 && x < TOWERS_COUNT + FIELD_BLOCKS_COUNT - 2) {
						if (money >= BLOCKS_PRICE[x - TOWERS_COUNT + 2]) {
							blockType = x + 1;
						}
					}
				}
				// ���� ������� �����/����
				if (blockType) {
					// ���� ������ �� ������� ����
					if (y < ROWS) {
						// ���� ������� �����
						if (blockType < TOWERS_COUNT) {
							// ���� ��� ������ ������
							if (!field.getCellValue(y, x)) {
								towerControl.addTower(y, x, blockType);
								money -= TOWERS_PRICE[blockType];
								field.getCell(y, x) = 2;
								blockType = 0;
							}
						}
						// ���� ������ ����
						else {
							// ���� ��� ������ ������
							if (field.getCellValue(y, x) == 1) {
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
		}

		if (!endOfWave) {
			// ����� �����������
			spawnNextEnemyCycle(enemiesWave, field);
			// ���������, ���� �� ����� + ��������� ������
			enemiesWave.checkAlive(money);
		}
		// ���� ������ �� ��������, ����������� �����
		if (!enemiesWave.getEnemiesLeft()) {
			endOfWave = 1;
		}
		// �������� ����� �����
		if (endOfWave) {
			waveBreakCycle(enemiesWave, result, endOfGame, endOfWave);
		}
		// ���������� ���������
		if (!endOfWave) {
			endOfGame = enemiesWave.moveAllEnemies();
		}

		window.clear();
		window.draw(spriteBack);
		// ������ ������ + �����
		field.paintRoad(window);
		// ������ ����� �� ������
		blocksControl.drawAllBlocks(window);

		// ������ �����
		towerControl.drawAllTowers(window);

		// ����� �������� + ���������
		if (!endOfWave) {
		// ��������� �����
		towerControl.towersShoot(field, missiles);
		// ������ ��������
		missiles.drawMissiles(window);
		}
		// ������ ���� ������
		enemiesWave.drawAllEnemies(window);

		// ������ ������� ��������
		shop.drawShop(enemiesWave.getLevel(), money, blockType, window);

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