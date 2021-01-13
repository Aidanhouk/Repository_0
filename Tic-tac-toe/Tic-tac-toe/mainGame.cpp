#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <thread>

#include "mainGame.h"
#include "_AI_makes_move.h"
#include "endCheck.h"

void mainGame(int n, int p)
{
	using sf::RectangleShape;
	using sf::Vector2f;
	using sf::Color;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	srand(static_cast<unsigned int>(time(0)));
	rand();

	sf::Text drawText("DRAW", font, 70);
	drawText.setFillColor(Color::White);
	drawText.setPosition((n - 2) * 50, 110);

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
	// игра закончилась ничьей?
	bool draw{ 0 };
	// за кого играет AI, 0 - нолики, 1 - крестики
	bool markAI{ static_cast<bool>(rand() % 2) };
	// нужны, чтобы перечеркнуть выигрышную линию
	int rowOrCol, dir;
	// сколько осталось пустых ячеек, если 0, то это ничья
	int blanks{ n*n };
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
			int whoWin{ finishedLineCheck(field, n, rowOrCol, dir) };
			if (whoWin) {
				endOfGame = 1;
			}
			// проверка на ничью
			if (!blanks && !endOfGame) {
				draw = 1;
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
			int whoWin{ finishedLineCheck(field, n, rowOrCol, dir) };
			if (whoWin && !endOfGame) {
				endOfGame = 1;
			}
			// проверка на ничью
			if (!blanks && !endOfGame) {
				draw = 1;
				endOfGame = 1;
			}
		}



		// Далее происходит отрисовка всех элементов

		// цвет фона
		window.clear(sf::Color(25, 0, 45));

		// отрисовка сетки
		for (int i = 1; i < n; ++i) {
			// по вертикали
			RectangleShape bordersV(Vector2f(5, n * W));
			bordersV.move(W * i, 0);
			bordersV.setFillColor(Color(80, 44, 112));
			window.draw(bordersV);
			// по горизонтали
			RectangleShape bordersH(Vector2f(n * W, 5));
			bordersH.move(0, W * i);
			bordersH.setFillColor(Color(80, 44, 112));
			window.draw(bordersH);
		}

		// отрисовка крестиков и ноликов
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				// крестики
				if (field[i][j] == 1) {
					RectangleShape cross(Vector2f(5, 60));
					cross.move(W * i + 30, W * j + 30);
					cross.rotate(-45.f);
					cross.setFillColor(Color(4, 217, 167));
					window.draw(cross);
					RectangleShape cross2(Vector2f(5, 60));
					cross2.move(W * i + 72, W * j + 26);
					cross2.rotate(45.f);
					cross2.setFillColor(Color(4, 217, 167));
					window.draw(cross2);
				}
				// нолики
				if (field[i][j] == 2) {
					sf::CircleShape nought(30);
					nought.move(W * i + 23, W * j + 23);
					nought.setFillColor(Color(210, 100, 110));
					window.draw(nought);
					sf::CircleShape nought2(22);
					nought2.move(W * i + 31, W * j + 31);
					nought2.setFillColor(Color(25, 0, 45));
					window.draw(nought2);
				}
			}
		}

		// перечеркиваем выигрышную линию
		if (endOfGame && !draw) {
			RectangleShape line;
			// кол-во пикселей от края
			int pixels = 15;
			switch (dir) {
			case 1:
				line = RectangleShape(Vector2f(5, n * W - pixels * 2));
				line.move(W * rowOrCol + 50, pixels);
				break;
			case 2:
				line = RectangleShape(Vector2f(n * W - pixels * 2, 5));
				line.move(pixels, W * rowOrCol + 50);
				break;
			case 3:
				line = RectangleShape(Vector2f(n * W * 1.41f - pixels * 2, 5));
				line.move(pixels, pixels);
				line.rotate(45.f);
				break;
			case 4:
				line = RectangleShape(Vector2f(n * W * 1.41f - pixels * 2, 5));
				line.move(pixels, W * n - pixels);
				line.rotate(-45.f);
				break;
			}
			line.setFillColor(Color::Yellow);
			window.draw(line);
		}
		if (draw) {
			//window.clear(sf::Color(25, 0, 45));
			window.draw(drawText);
		}

		window.display();

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