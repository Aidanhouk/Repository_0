#include "mainGame.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <thread>

#include "consts.h"
#include "drawing.h"
#include "_AI_makes_move.h"
#include "endCheck.h"

void mainGame(int n, int p, int &res)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	srand(static_cast<unsigned int>(time(0)));
	rand();

	// создаем поле размерностью nxn
	int **field = new int*[n];
	for (int i = 0; i < n; ++i) {
		field[i] = new int[n] {0};
	}

	// окно игры
	sf::RenderWindow window(sf::VideoMode(n * 100, n * 100), "Tic-tac-toe", sf::Style::Titlebar | sf::Style::Close, settings);

	// 1 - сейчас должны ставиться крестики, 0 - нолики
	bool turn{ 1 };
	// игра закончена?
	bool endOfGame{ 0 };
	// за кого играет AI, 0 - нолики, 1 - крестики
	bool markAI{ static_cast<bool>(rand() % 2) };
	// нужны, чтобы перечеркнуть выигрышную линию
	int rowOrCol, finishLineDirection;
	// сколько осталось пустых ячеек, если 0, то это ничья
	int blanks{ n*n };
	// сюда запишем результат, 0 - ничья, 1 - выиграли крестики, 2 - нолики
	int whoWin{ 0 };
	// сюда будут записывать все ходы, нужно для работы AI
	std::vector<int> moves;
	moves.reserve(n*n);

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

				// если игра против игрока или против AI и при этом сейчас ход игрока
				if (p == 1 || p == 2 && turn != markAI) {
					// если нажата ЛКМ и это поле пустое
					if (event.mouseButton.button == sf::Mouse::Left && field[x][y] == 0) {
						// добавляем эту ячейку в вектор с ходами
						if (p == 2) {
							moves.push_back(y * n + x);
						}
						// если сейчас должен ставиться крестик
						if (turn) {
							field[x][y] = 1;
							turn = 0;
							--blanks;
						}
						// если сейчас должен ставиться нолик
						else {
							field[x][y] = 2;
							turn = 1;
							--blanks;
						}
					}
				}
			}
		}
		// проверка на конец игры после хода игрока
		if (!endOfGame && p != 3) {
			// если whoWin = 1, то победили крестики, 2 - нолики
			whoWin = finishedLineCheck(field, n, rowOrCol, finishLineDirection);
			if (whoWin) {
				endOfGame = 1;
			}
			// проверка на ничью
			if (!blanks && !endOfGame) {
				endOfGame = 1;
			}
		}

		// ход AI
		if (!endOfGame && (p == 2 && turn == markAI || p == 3)) {
			// сюда запишутся номера строки и столбца ячейки, которую выбрал AI
			int row, col;
			_AI_makes_move(moves, field, n, col, row);
			if (turn) {
				field[row][col] = 1;
				turn = 0;
				--blanks;
			}
			else {
				field[row][col] = 2;
				turn = 1;
				--blanks;
			}
		}
		// проверка на конец игры после хода AI
		if (!endOfGame && p != 1) {
			// если whoWin = 1, то победили крестики, 2 - нолики
			whoWin = finishedLineCheck(field, n, rowOrCol, finishLineDirection);
			if (whoWin) {
				endOfGame = 1;
			}
			// проверка на ничью
			if (!blanks && !endOfGame) {
				endOfGame = 1;
			}
		}

		// далее происходит отрисовка всех элементов

		// цвет фона
		window.clear(sf::Color(25, 0, 45));
		// отрисовка сетки
		drawField(window, n);
		// отрисовка крестиков и ноликов
		drawFigures(window, n, field);
		// перечеркиваем выигрышную линию
		if (endOfGame && whoWin) {
			crossFinishLine(window, n, finishLineDirection, rowOrCol);
		}

		window.display();

		// возвращаем значени, кто выиграл
		if (endOfGame) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			res = whoWin;
			// если player vs AI и при это НЕ ничья, нужно немного изменить вывод результата
			if (p == 2 && whoWin) {
				// если markAI = 0, то присваиваем ему 2
				int _markAI = markAI ? 1 : 2;
				// если фигура AI совпадает с фигурой, которая победила, то AI победил
				if (_markAI == whoWin) {
					res = 2;
				}
				else {
					res = 1;
				}
			}
			window.close();
		}

		// паузы между ходами AI vs AI
		if (p == 3 && !endOfGame) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

	// освобождение памяти под поле
	for (int i = 0; i < n; ++i) {
		delete[] field[i];
	}
	delete[] field;
}