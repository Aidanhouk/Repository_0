#include "consts.h"
#include "globals.h"
#include "field.h"
#include "_AI.h"
#include "drawing.h"

void mainGame()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно игры
	sf::RenderWindow _window(sf::VideoMode(n * 100, n * 100), "Tic-tac-toe", sf::Style::Titlebar | sf::Style::Close, settings);
	window = &_window;

	// поле
	Field _field;
	field = &_field;

	// AI, в параметрах можно указать, за какую фигуру будет играть AI, 1 - крестики, 2 - нолики
	AI _AI((rand() % 2) + 1);

	// конец игры
	bool endOfGame{ 0 };
	// какая фигура победила, 0 - ничья, 1 - выиграли крестики, 2 - нолики
	int whoWon{ 0 };

	// главный цикл игры
	while (window->isOpen())
	{
		// ход игрока
		if (!endOfGame) {
			// получаем координаты курсора мышы
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			int x{ pos.x / W };
			int y{ pos.y / W };

			sf::Event event;
			// обработчик событий
			while (window->pollEvent(event))
			{
				// закрытие окна
				if (event.type == sf::Event::Closed) {
					window->close();
				}
				// если нажата кнопка мыши
				if (event.type == sf::Event::MouseButtonPressed) {
					// если игра с участием игрока и при этом сейчас ход игрока
					if (_WhoVsWho == 1 || (_WhoVsWho == 2 && field->getTurn() != _AI.getAIMark())) {
						// если эта ячейка пустая
						if (!(*field)[x][y]) {
							// добавляем эту ячейку в вектор с ходами, если игра против AI
							if (_WhoVsWho == 2) {
								field->getMovesVector().push_back(y * n + x);
							}
							(*field)[x][y] = field->getTurn();
							field->changeTurn();
							field->decreaseBlanks();
						}
					}
				}
			}
			// проверка на конец игры после хода игрока
			if (_WhoVsWho != 3) {
				whoWon = field->finishedLineCheck();
				// если whoWon = 1, то победили крестики, 2 - нолики
				if (whoWon) {
					endOfGame = 1;
				}
				else {
					// проверка на ничью
					if (field->isDraw()) {
						endOfGame = 1;
					}
				}
			}
		}

		// ход AI
		if (!endOfGame) {
			if (_WhoVsWho == 2 && field->getTurn() == _AI.getAIMark() || _WhoVsWho == 3) {
				// сюда запишутся номера строки и столбца ячейки, которую выбрал AI
				int row, col;
				_AI._AI_makes_move(col, row);
				(*field)[row][col] = field->getTurn();
				field->changeTurn();
				field->decreaseBlanks();
			}
			// проверка на конец игры после хода AI
			if (_WhoVsWho != 1) {
				whoWon = field->finishedLineCheck();
				// если whoWon = 1, то победили крестики, 2 - нолики
				if (whoWon) {
					endOfGame = 1;
				}
				else {
					// проверка на ничью
					if (field->isDraw()) {
						endOfGame = 1;
					}
				}
			}
		}

		// далее происходит отрисовка всех элементов

		// цвет фона
		window->clear(sf::Color(25, 0, 45));
		// отрисовка сетки
		drawField();
		// отрисовка крестиков и ноликов
		drawFigures();
		// перечеркиваем выигрышную линию
		if (endOfGame && whoWon) {
			crossFinishLine();
		}
		window->display();

		// возвращаем значение, кто выиграл
		if (endOfGame) {
			sf::sleep(sf::Time(sf::milliseconds(500)));
			gameResult = whoWon;
			// если player vs AI и при это НЕ ничья, нужно немного изменить обработку результата
			if (_WhoVsWho == 2 && whoWon) {
				// если фигура AI совпадает с фигурой, которая победила, то AI победил (2)
				gameResult = (_AI.getAIMark() == whoWon) ? 2 : 1;
			}
			window->close();
		}

		// паузы между ходами AI vs AI
		if (_WhoVsWho == 3 && !endOfGame) {
			sf::sleep(sf::Time(sf::milliseconds(500)));
		}
	}
}