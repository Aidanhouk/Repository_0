// в заголовке consts.h можно настроить параметры поля и баланса
// в файле field.cpp в функции makeRoad() можно создать любую дорогу по координатам

void menu(int &level, bool &exitGame);
void mainGame(int &result, int level, int &waveLevel);
void result(int result, int waveLevel, bool &exitGame);

int main()
{
	// сюда запишем результат игры 0 - закрыл игру, 1 - прошел игру, 2 - проиграл
	int res{ 0 };
	// какой уровень выбран?
	int level{ 1 };
	// на какой волне закончилась игра?
	int waveLevel{ 0 };
	// закрыть игру?
	bool exitGame{ 0 };

	while (1) {
		// сбрасываем эти параметры
		res = 0; level = 1; waveLevel = 0;

		// выбор уровня
		menu(level, exitGame);
		if (exitGame) {
			break;
		}

		// основная игра
		mainGame(res, level, waveLevel);

		// результат
		result(res, waveLevel, exitGame);
		if (exitGame) {
			break;
		}
	}

	return 0;
}