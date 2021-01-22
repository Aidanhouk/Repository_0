#include "mainGame.h"

//#include <SFML/Graphics.hpp>
#include <thread>

#include "field.h"
#include "enemiesWave.h"
#include "towersControl.h"
#include "consts.h"
#include "cycleFuncions.h"
#include "missilesControl.h"
#include "shop.h"

void mainGame(int &result, int &level)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно игры
	sf::RenderWindow window(sf::VideoMode(W * COLS, W * (ROWS + 1.5)), "Tower defense", sf::Style::Titlebar | sf::Style::Close, settings);

	// нужно ограничить фпс
	window.setFramerateLimit(60);

	// объект поля
	Field field;
	// создаем дорогу
	field.makeRoad();
	// создаем спрайт блока вне дороги
	sf::Texture emptyBlockTexture;
	emptyBlockTexture.loadFromFile("images/field/emptyBlock.png");
	sf::Sprite spriteBack(emptyBlockTexture);

	// объект волны противников, в параметрах - уровень волны с который начнется игра минус 1
	EnemiesWave enemiesWave(0, 5);
	// объект для управления башнями
	TowersControl towerControl;
	// объект для работы со снарядами
	Missiles missiles;
	// объект магазина
	Shop shop;

	// изначальные деньги
	int money{ START_MONEY };
	// тип башни, на которую нажал игрок в магазине
	int type{ 0 };
	// конец игры?
	bool endOfGame{ 0 };
	// конец волны?
	bool endOfWave{ 1 };

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
				if (y == ROWS) {
					if (x >= 0 && x < TOWERS_COUNT) {
						if (money >= TOWERS_PRICE[x + 1]) {
							type = x + 1;
						}
					}
				}
				// если выбрана башня
				if (type) {
					// если нажата не область меню
					if (y < ROWS) {
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
			// проверяем, живы ли враги + обновляем монеты
			enemiesWave.checkAlive(money);
		}
		// если врагов не осталось, заканчиваем волну
		if (!enemiesWave.getEnemiesLeft()) {
			endOfWave = 1;
		}
		// ожидание новой волны
		if (endOfWave) {
			waveBreakCycle(enemiesWave, result, endOfGame, endOfWave);
		}
		// противники двигаются
		if (!endOfWave) {
			endOfGame = enemiesWave.moveAllEnemies();
		}

		window.clear();
		window.draw(spriteBack);
		// рисуем дорогу + финиш
		field.paintRoad(window);
		// рисуем область магазина
		shop.drawShop(enemiesWave.getLevel(), money, type, window);
		// рисуем всех врагов
		enemiesWave.drawAllEnemies(window);

		// рисуем башни
		towerControl.drawAllTowers(window);

		// башни стреляют + отрисовка
		if (!endOfWave) {
		// добавляем новые
		towerControl.towersShoot(field, missiles);
		// рисуем выстрелы
		missiles.drawMissiles(window);
		}

		// отрисовка окна
		window.display();

		// если игра окончена, то выходим
		if (endOfGame) {
			// если результат = 0, то игра проигрына
			if (!result) {
				result = 2;
			}
			level = enemiesWave.getLevel();
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			window.close();
		}
	}
}