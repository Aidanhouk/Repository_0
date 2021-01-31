// в заголовке consts.h можно настроить параметры баланса

#include "globals.h"
#include "menu.h"
#include "mainGame.h"
#include "results.h"

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
// поле
Field * field;
// окно
sf::RenderWindow * window;

int main()
{
	// закрыть игру?
	bool exitGame{ 0 };

	while (1) {
		// сбрасываем параметры игры
		result = 0; waveLevel = 0;

		// выбор уровня
		menu(exitGame);
		if (exitGame) {
			break;
		}

		// основная игра
		mainGame();

		// результат
		results(exitGame);
		if (exitGame) {
			break;
		}
	}

	return 0;
}