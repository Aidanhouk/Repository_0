#include "mainGame.h"

#include <SFML/Graphics.hpp>
#include <thread>

#include "field.h"
#include "enemiesWave.h"
#include "towersControl.h"
#include "consts.h"
#include "drawShop.h"
#include "cycleFuncions.h"
#include "missilesControl.h"

void mainGame(int &result, int &level)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// ���� ����
	sf::RenderWindow window(sf::VideoMode(W * COLS, W * (ROWS + 1)), "Tower defense", sf::Style::Titlebar | sf::Style::Close, settings);

	// ����� ���������� ���
	window.setFramerateLimit(100);

	// ������ ����
	Field field;
	// ������� ������
	field.makeRoad();

	// ������ ����� �����������, � ���������� - ������� ����� � ������� �������� ���� ����� 1
	EnemiesWave enemiesWave(0);
	// ������ ��� ���������� �������
	TowersControl towerControl;
	// ������ ��� ������ �� ���������
	Missiles missiles;

	// ����������� ������
	int money{ MONEY };
	// ��� �����, �� ������� ����� ����� � ��������
	int type{ 0 };
	// ����� ����?
	bool endOfGame{ 0 };
	// ����� �����?
	bool endOfWave{ 1 };
	// �������� �������?
	bool drawMissile{ 0 };

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
				// ��������� ������� �� ����� � ��������
				if (x == 0 && y == ROWS) {
					if (money >= TOWERS_PRICE[1]) {
						type = 1;
					}
				}
				if (x == 1 && y == ROWS) {
					if (money >= TOWERS_PRICE[2]) {
						type = 2;
					}
				}
				if (x == 2 && y == ROWS) {
					if (money >= TOWERS_PRICE[3]) {
						type = 3;
					}
				}
				// ���� ������� �����
				if (type) {
					// ���� ������ �� ������� ����
					if (y != ROWS) {
						// ���� ��� ������ ������
						if (!field.getCellValue(y, x)) {
							towerControl.addTower(y, x, type);
							money -= TOWERS_PRICE[type];
							field.getCell(y, x) = 2;
							type = 0;
						}
					}
				}
			}
		}

		if (!endOfWave) {
			// ����� �����������
			spawnNextEnemyCycle(enemiesWave, field);
			// ����� ��������
			towerShootCycle(towerControl, field, missiles, drawMissile);
			// ���������, ���� �� ����� + ��������� ������
			enemiesWave.checkAlive(money);
		}
		// ���� ������ �� ��������, ����������� �����
		if (!enemiesWave.getEnemiesLeft()) {
			endOfWave = 1;
		}
		// ���������� ���������
		if (!endOfWave) {
			enemyMoveCycle(enemiesWave, endOfGame);
		}
		// �������� ����� �����
		if (endOfWave) {
			waveBreakCycle(enemiesWave, result, endOfGame, endOfWave);
		}

		// ���� ����
		window.clear(sf::Color(30, 115, 30));
		// ������ ������ + �����
		field.paintRoad(window);
		// ������ ������� ��������
		drawShop(enemiesWave.getLevel(), money, type, window);
		// ������ ���� ������
		enemiesWave.drawAllEnemies(window);
		// ������ �������, ���� ��� ������ �������
		if (drawMissile) {
			missileDrawCycle(missiles, window, drawMissile);
		}
		// ������ �����
		towerControl.drawAllTowers(window);
		// ���������
		window.display();

		// ���� ���� ��������, �� �������
		if (endOfGame) {
			// ���� ��������� = 0 � ���� ��������, �� ��� ���������
			if (!result) {
				result = 2;
			}
			level = enemiesWave.getLevel();
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			window.close();
		}
	}
}