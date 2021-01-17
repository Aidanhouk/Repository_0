// в заголовке consts.h можно настроить параметры поля и баланса
// в файле field.cpp в функции makeRoad() можно создать любую дорогу по координатам

void mainGame(int &result, int &level);
void result(int result, int level, bool &playAgain);

int main()
{
	// сюда запишем результат игры 0 - закрыл игру, 1 - прошел игру, 2 - проиграл
	int res{ 0 };

	// на какой волне закончилась игра?
	int level{ 0 };

	// играть снова?
	bool playAgain{ 1 };

	while (playAgain) {
		// сбрасываем эти параметры
		res = 0; level = 0;

		// основная игра
		mainGame(res, level);

		// результат
		result(res, level, playAgain);
	}

	return 0;
}