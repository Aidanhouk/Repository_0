#include <SFML/Audio.hpp>

#include "consts.h"
#include "globals.h"
#include "cycleFuncions.h"
#include "field.h"
#include "enemiesWave.h"
#include "towersControl.h"
#include "missiles.h"
#include "blocksControl.h"
#include "shop.h"

void mainGame()
{
	// окно игры
	sf::RenderWindow _window(sf::VideoMode(W * (COLS + 2), W * (ROWS + 1)), "Tower defense", sf::Style::Titlebar | sf::Style::Close);
	window = &_window;

	// нужно ограничить фпс
	(*window).setFramerateLimit(60);

	// объект поля
	Field _field;
	field = &_field;
	// создаем дорогу
	(*field).makeRoad();
	// создаем спрайт блока вне дороги
	sf::Texture emptyBlockTexture;
	emptyBlockTexture.loadFromFile("images/field/emptyBlock.png");
	sf::Sprite spriteBack(emptyBlockTexture);

	// объект волны противников, в параметрах - уровень волны с который начнется игра; уровень последней волны
	EnemiesWave enemiesWave(1, 10);
	// объект для управления башнями
	TowersControl towerControl;
	// объект для работы со снарядами
	Missiles missiles;
	// обект для управления блоками на дороге
	BlocksControl blocksControl;
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
	
	// влючаем саундтрек
	sf::Music music;
	music.setLoop(true);
	int musicN{ rand() % 3 + 1 };
	music.openFromFile("music/song" + std::to_string(musicN) + ".ogg");
	music.play();

	// главный цикл игры
	while ((*window).isOpen())
	{
		// получаем координаты курсора мыши
		sf::Vector2i pos = sf::Mouse::getPosition(*window);
		int x{ pos.x / W };
		int y{ pos.y / W };

		sf::Event event;
		// обработчик событий
		while ((*window).pollEvent(event))
		{
			// закрытие окна
			if (event.type == sf::Event::Closed) {
				(*window).close();
			}
			// если нажата кнопка мыши и игра не закончена
			if (event.type == sf::Event::MouseButtonPressed) {
				// 1 переменная для фиксации нажатия на башню/блок для продажи
				bool towerSelected{ 0 };
				if (x < COLS && y < ROWS) {
					// выбрана башня/блок на поле
					switch ((*field).getCellValue(y, x))
					{
					case 2:
					case 3:
						towerSelected = 1;
						// если башня/блок уже была выбрана, то удаляем ее
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
						// отмечаем башню/блок
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
				// 2 если выбрана башня/блок в магазине
				if (blockType && !towerSelected) {
					// если нажата облать поля
					if (x < COLS && y < ROWS) {
						// если выбрана башня
						if (blockType < TOWERS_COUNT) {
							// если эта ячейка пустая
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
						// если выбран блок
						else {
							// если эта ячейка дороги
							if ((*field).getCellValue(y, x) == 1) {
								if (money >= BLOCKS_PRICE[blockType - TOWERS_COUNT + 1]) {
									// если получилось поставить блок
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
				// 3 фиксируем нажатия на кнопки и башни в магазине
				if (x >= COLS) {
					clickedTowerCoord.first = -1;
					clickedTowerCoord.second = -1;
					if (y == 9 || y == 10) {
						// ставим игру на паузу или убираем с паузы
						pause = !pause;
						if (!pause) {
							resetTimeToSpawn();
						}
						break;
					}
					else {
						blockType = shop.returnItemNumber(pos.x, pos.y);
					}
				}
				// 4 нажатия в нижней области
				if (y == ROWS) {
					if (x == COLS - 1) {
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
				}
			}
		}

		if (!endOfWave && !pause) {
			// спавн противников
			spawnNextEnemyCycle(enemiesWave);
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

		(*window).clear();
		// фон
		(*window).draw(spriteBack);
		// рисуем дорогу + финиш
		(*field).paintRoad();
		// рисуем блоки на дороге
		blocksControl.drawAllBlocks();

		// рисуем башни
		towerControl.drawAllTowers();

		// башни стреляют + отрисовка
		if (!endOfWave) {
			// обрабатываем снаряды 
			if (!pause) {
				towerControl.towersShoot(missiles);
			}
			// рисуем выстрелы
			missiles.drawMissiles();
			// эффекты у последнего врага в волне
			if (enemiesWave.getEnemiesLeft() == 1) {
				enemiesWave.drawLastEnemyEffects();
			}
			// рисуем всех врагов
			enemiesWave.drawAllEnemies();
		}

		// отмечаем выбранную башню/блок
		if (clickedTowerCoord.first != -1) {
			towerControl.markTowerToDelete(clickedTowerCoord.first, clickedTowerCoord.second);
		}

		// наведение на башню для отрисовки дальности действия башни
		if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
			if ((*field).getTowerOnCell(y, x)) {
				(*field).drawRange(y, x);
			}
		}

		// рисуем область магазина
		shop.drawShop(enemiesWave.getLevel(), enemiesWave.getMaxLevel(), blockType);

		// наведение на башни и блоки в магазине для выведения инфы о них
		if (x >= COLS && x <= COLS + 1) {
			int itemType{ shop.returnItemNumber(pos.x, pos.y) };
			shop.itemInfo(itemType);
		}

		(*window).display();

		// если игра окончена, то выходим
		if (endOfGame) {
			// если результат = 0, то игра проигрына
			if (!result) {
				result = 2;
			}
			waveLevel = enemiesWave.getLevel();
			sf::sleep(sf::Time(sf::milliseconds(700)));
			(*window).close();
		}
	}
}