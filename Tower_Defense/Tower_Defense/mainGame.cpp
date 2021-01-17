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

	// окно игры
	sf::RenderWindow window(sf::VideoMode(W * COLS, W * (ROWS + 1)), "Tower defense", sf::Style::Titlebar | sf::Style::Close, settings);

	// нужно ограничить фпс
	window.setFramerateLimit(100);

	// объект поля
	Field field;
	// создаем дорогу
	field.makeRoad();

	// объект волны противников, в параметрах - уровень волны с который начнется игра минус 1
	EnemiesWave enemiesWave(0);
	// объект для управления башнями
	TowersControl towerControl;
	// объект для работы со снарядами
	Missiles missiles;

	// изначальные деньги
	int money{ MONEY };
	// тип башни, на которую нажал игрок в магазине
	int type{ 0 };
	// конец игры?
	bool endOfGame{ 0 };
	// конец волны?
	bool endOfWave{ 1 };
	// рисовать снаряды?
	bool drawMissile{ 0 };

	// главный цикл игры
	while (window.isOpen())
	{
		// получаем координаты курсора мышы
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x{ pos.x / W };
		int y{ pos.y / W };

		sf::Event event;
		// обработчик событий
		while (window.pollEvent(event))
		{
			// закрытие окна
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			// если нажата кнопка мыши и игра не закончена
			if (event.type == sf::Event::MouseButtonPressed && !endOfGame) {
				// фиксируем нажатия на башни в магазине
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
				// если выбрана башня
				if (type) {
					// если нажата не область меню
					if (y != ROWS) {
						// если эта ячейка пустая
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
			// спавн противников
			spawnNextEnemyCycle(enemiesWave, field);
			// башни стреляют
			towerShootCycle(towerControl, field, missiles, drawMissile);
			// проверяем, живы ли враги + обновляем монеты
			enemiesWave.checkAlive(money);
		}
		// если врагов не осталось, заканчиваем волну
		if (!enemiesWave.getEnemiesLeft()) {
			endOfWave = 1;
		}
		// противники двигаются
		if (!endOfWave) {
			enemyMoveCycle(enemiesWave, endOfGame);
		}
		// ожидание новой волны
		if (endOfWave) {
			waveBreakCycle(enemiesWave, result, endOfGame, endOfWave);
		}

		// цвет фона
		window.clear(sf::Color(30, 115, 30));
		// рисуем дорогу + финиш
		field.paintRoad(window);
		// рисуем область магазина
		drawShop(enemiesWave.getLevel(), money, type, window);
		// рисуем всех врагов
		enemiesWave.drawAllEnemies(window);
		// рисуем снаряды, если был сделан выстрел
		if (drawMissile) {
			missileDrawCycle(missiles, window, drawMissile);
		}
		// рисуем башни
		towerControl.drawAllTowers(window);
		// отрисовка
		window.display();

		// если игра окончена, то выходим
		if (endOfGame) {
			// если результат = 0 и игра окончена, то она проигрына
			if (!result) {
				result = 2;
			}
			level = enemiesWave.getLevel();
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			window.close();
		}
	}
}