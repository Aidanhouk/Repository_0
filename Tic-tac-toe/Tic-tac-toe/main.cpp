// полноценный AI работает только для поля 3x3
// для других размерностей осуществляется проверка на линию, которую можно закончить,
// чтобы победить или не дать победить противнику, если такой линии нет, то ставиться на случайную клетку
// кто ходит первым - рандом

#include "globals.h"
#include "menu.h"
#include "mainGame.h"
#include "results.h"

// размерность поля
int n;
// кто против кого
int _WhoVsWho;
// результат игры
int gameResult;
// поле игры
Field * field;
// окно игры 
sf::RenderWindow *window;

// пока 1, игра перезапускается
bool gameContinues{ 1 };

int main()
{
	while (gameContinues) {
		// устанавливаем значения по умолчанию
		n = 3, _WhoVsWho = 2, gameResult = -1;

		// открываем меню
		menu();

		// запускаем игру
		mainGame();

		// реузультаты
		results(gameContinues);
	}

	return 0;
}