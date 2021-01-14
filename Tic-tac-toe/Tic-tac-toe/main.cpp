// AI работает только для поля 3x3, для других размерностей - полный рандом
// кто ходит первым - рандом

#include <SFML/Graphics.hpp>
#include "menu.h"
#include "mainGame.h"
#include "results.h"

int main()
{
	// размерность поля + значение по умолчанию
	int n{ 3 };
	// кто vs кто? 1 - player vs player, 2 - player vs AI, 3 - AI vs AI
	int p{ 2 };
	// сюда запишем результат игры
	int res{ 0 };
	// пока 1, игра перезапускается
	bool gameContinues{ 1 };

	while (gameContinues) {
		// открываем меню
		openMenu(n, p);

		// запускаем игру
		mainGame(n, p, res);

		// реузультаты
		results(res, p, gameContinues);
	}

	return 0;
}