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

	// ������� ���� ������������ nxn
	int **field = new int*[n];
	for (int i = 0; i < n; ++i) {
		field[i] = new int[n] {0};
	}

	// ���� ����
	sf::RenderWindow window(sf::VideoMode(n * 100, n * 100), "Tic-tac-toe", sf::Style::Titlebar | sf::Style::Close, settings);

	// 1 - ������ ������ ��������� ��������, 0 - ������
	bool turn{ 1 };
	// ���� ���������?
	bool endOfGame{ 0 };
	// ���� ����������� ������?
	bool draw{ 0 };
	// �� ���� ������ AI, 0 - ������, 1 - ��������
	bool markAI{ static_cast<bool>(rand() % 2) };
	// �����, ����� ������������ ���������� �����
	int rowOrCol, dir;
	// ������� �������� ������ �����, ���� 0, �� ��� �����
	int blanks{ n*n };
	// ���� ����� ���������� ��� ����, ����� ��� ������ AI
	std::vector<int> moves;
	moves.reserve(n*n);

	// ������� ���� ����
	while (window.isOpen())
	{
		// �������� ���������� ������� ����
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x{ pos.x / W };
		int y{ pos.y / W };

		sf::Event event;
		// ���������� �������
		while (window.pollEvent(event))
		{
			// �������� ����
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			// ���� ������ ������ ���� � ���� �� ���������
			if (event.type == sf::Event::MouseButtonPressed && !endOfGame) {

				// ���� ���� ������ ������ ��� ������ AI � ��� ���� ������ ��� ������
				if (p == 1 || p == 2 && turn != markAI) {
					// ���� ������ ��� � ��� ���� ������
					if (event.mouseButton.button == sf::Mouse::Left && field[x][y] == 0) {
						// ��������� ��� ������ � ������ � ������
						if (p == 2) {
							moves.push_back(y * n + x);
						}
						// ���� ������ ������ ��������� �������
						if (turn) {
							field[x][y] = 1;
							turn = 0;
							--blanks;
						}
						// ���� ������ ������ ��������� �����
						else {
							field[x][y] = 2;
							turn = 1;
							--blanks;
						}
					}
				}
			}
		}
		// �������� �� ����� ���� ����� ���� ������
		if (!endOfGame && p != 3) {
			// ���� whoWin = 1, �� �������� ��������, 2 - ������
			int whoWin{ finishedLineCheck(field, n, rowOrCol, dir) };
			if (whoWin) {
				endOfGame = 1;
			}
			// �������� �� �����
			if (!blanks && !endOfGame) {
				draw = 1;
				endOfGame = 1;
			}
		}



		// ��� AI
		if (!endOfGame && (p == 2 && turn == markAI || p == 3)) {
			// ���� ��������� ������ ������ � ������� ������, ������� ������ AI
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
		// �������� �� ����� ���� ����� ���� AI
		if (!endOfGame && p != 1) {
			// ���� whoWin = 1, �� �������� ��������, 2 - ������
			int whoWin{ finishedLineCheck(field, n, rowOrCol, dir) };
			if (whoWin && !endOfGame) {
				endOfGame = 1;
			}
			// �������� �� �����
			if (!blanks && !endOfGame) {
				draw = 1;
				endOfGame = 1;
			}
		}



		// ����� ���������� ��������� ���� ���������

		// ���� ����
		window.clear(sf::Color(25, 0, 45));

		// ��������� �����
		for (int i = 1; i < n; ++i) {
			// �� ���������
			RectangleShape bordersV(Vector2f(5, n * W));
			bordersV.move(W * i, 0);
			bordersV.setFillColor(Color(80, 44, 112));
			window.draw(bordersV);
			// �� �����������
			RectangleShape bordersH(Vector2f(n * W, 5));
			bordersH.move(0, W * i);
			bordersH.setFillColor(Color(80, 44, 112));
			window.draw(bordersH);
		}

		// ��������� ��������� � �������
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				// ��������
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
				// ������
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

		// ������������� ���������� �����
		if (endOfGame && !draw) {
			RectangleShape line;
			// ���-�� �������� �� ����
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

		// ����� ����� ������ AI vs AI
		if (p == 3 && !endOfGame) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

	// ������������ ������ ��� ����
	for (int i = 0; i < n; ++i) {
		delete[] field[i];
	}
	delete[] field;
}