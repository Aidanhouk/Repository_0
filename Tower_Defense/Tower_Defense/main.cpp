// в заголовке consts.h можно настроить параметры поля и баланса
// в файле field.cpp в функции makeRoad() можно создать любую дорогу по координатам

void menu(int &level);
void mainGame(int &result, int level, int &waveLevel);
void result(int result, int waveLevel, bool &playAgain);

int main()
{
	// сюда запишем результат игры 0 - закрыл игру, 1 - прошел игру, 2 - проиграл
	int res{ 0 };
	// какой уровень выбран?
	int level{ 1 };
	// на какой волне закончилась игра?
	int waveLevel{ 0 };
	// играть снова?
	bool playAgain{ 1 };

	while (playAgain) {
		// сбрасываем эти параметры
		res = 0; level = 1; waveLevel = 0;

		// выбор уровня
		menu(level);

		// основная игра
		mainGame(res, level, waveLevel);

		// результат
		result(res, waveLevel, playAgain);
	}

	return 0;
}