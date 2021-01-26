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

// скорость игры
bool gameSpeed;
// пауза?
bool pause;
// результат игры
int result;
// какой уровень выбран
int level;
// на какой волне закончилась игра
int waveLevel;
// кол-во денег
int money;

void mainGame()
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно игры
	sf::RenderWindow window(sf::VideoMode(W * (COLS + 2), W * ROWS), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	// нужно ограничить фпс
	window.setFramerateLimit(60);

	// объект поля
	Field field(level);
	// создаем дорогу
	field.makeRoad();
	// создаем спрайт блока вне дороги
	sf::Texture emptyBlockTexture;
	emptyBlockTexture.loadFromFile("images/field/emptyBlock.png");
	sf::Sprite spriteBack(emptyBlockTexture);

	// объект волны противников, в параметрах - уровень волны с который начнется игра; уровень последней волны
	EnemiesWave enemiesWave(1, 8);
	// объект для управления башнями
	TowersControl towerControl;
	// объект для работы со снарядами
	Missiles missiles;
	// обект для управления блоками на дороге
	BlocksControl blocksControl(field);
	// объект магазина
	Shop shop;

	// изначальные деньги
	money = START_MONEY[level];
	// конец игры?
	bool endOfGame{ 0 };
	// конец волны?
	bool endOfWave{ 1 };
	// тип башни/блока, на которую нажал игрок в магазине
	int blockType{ 0 };
	// координаты башни, которую выбрал игрок (для удаления)
	std::pair<int, int> clickedTowerCoord;
	clickedTowerCoord.first = -1;
	clickedTowerCoord.second = -1;

	// сбрасываем некоторые параметры (пауза, скорость игры)
	setToDefault();

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
				// переменная для фиксации нажатия на башню для продажи
				bool towerSelected{ 0 };
				if (x < COLS) {
					// выбрана башня на поле
					if (field.getCell(y, x) == 2) {
						towerSelected = 1;
						// если башня уже была выбрана, то удаляем ее
						if (clickedTowerCoord.first == y && clickedTowerCoord.second == x) {
							money += towerControl.deleteTower(y, x);
							clickedTowerCoord.first = -1;
							clickedTowerCoord.second = -1;
							field.getCell(y, x) = 0;
						}
						// отмечаем башню
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
				// если выбрана башня/блок в магазине
				if (blockType && !towerSelected) {
					// если нажата не область меню
					if (x < COLS) {
						// если выбрана башня
						if (blockType < TOWERS_COUNT) {
							// если эта ячейка пустая
							if (!field.getCellValue(y, x)) {
								if (money >= TOWERS_PRICE[blockType]) {
									towerControl.addTower(y, x, blockType);
									money -= TOWERS_PRICE[blockType];
									field.getCell(y, x) = 2;
									blockType = 0;
								}
							}
						}
						// если выбран блок
						else {
							// если эта ячейка дороги
							if (field.getCellValue(y, x) == 1) {
								if (money >= BLOCKS_PRICE[blockType - TOWERS_COUNT + 1]) {
									// если получилось поставить блок
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
				// фиксируем нажатия на кнопки и башни в магазине
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
						// ставим игру на паузу или убираем с паузы
						if (x == COLS + 1) {
							// ускоряем игру
							if (!gameSpeed) {
								gameSpeed = 1;
							}
							// замедляем игру
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
			// спавн противников
			spawnNextEnemyCycle(enemiesWave, field);
		}
		// если врагов не осталось, заканчиваем волну
		if (!enemiesWave.getEnemiesLeft()) {
			endOfWave = 1;
		}
		// ожидание новой волны
		if (endOfWave && !pause) {
			waveBreakCycle(enemiesWave, endOfGame, endOfWave);
		}
		// противники двигаются
		if (!endOfWave && !pause) {
			endOfGame = enemiesWave.moveAllEnemies();
		}

		window.clear();
		// фон
		window.draw(spriteBack);
		// рисуем дорогу + финиш
		field.paintRoad(window);
		// рисуем блоки на дороге
		blocksControl.drawAllBlocks(window);

		// рисуем башни
		towerControl.drawAllTowers(window);

		// башни стреляют + отрисовка
		if (!endOfWave) {
			// обрабатываем снаряды 
			if (!pause) {
				towerControl.towersShoot(field, missiles);
			}
			// рисуем выстрелы
			missiles.drawMissiles(window);
			// рисуем всех врагов
			enemiesWave.drawAllEnemies(window);
		}

		// отмечаем выбранную башню
		if (clickedTowerCoord.first != -1) {
			towerControl.markTowerToDelete(window, clickedTowerCoord.first, clickedTowerCoord.second);
		}

		// рисуем область магазина
		shop.drawShop(enemiesWave.getLevel(), enemiesWave.getMaxLevel(), blockType, window);

		window.display();

		// если игра окончена, то выходим
		if (endOfGame) {
			// если результат = 0, то игра проигрына
			if (!result) {
				result = 2;
			}
			waveLevel = enemiesWave.getLevel();
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			window.close();
		}
	}
}