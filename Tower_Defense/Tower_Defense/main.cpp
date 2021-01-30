// в заголовке consts.h можно настроить параметры поля и баланса
// в файле field.cpp в функции makeRoad() можно создать любую дорогу по координатам

#include "globals.h"
#include "menu.h"
#include "mainGame.h"
#include "results.h"

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