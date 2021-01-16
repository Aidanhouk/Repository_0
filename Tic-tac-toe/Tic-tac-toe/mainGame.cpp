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
	// �� ���� ������ AI, 0 - ������, 1 - ��������
	bool markAI{ static_cast<bool>(rand() % 2) };
	// �����, ����� ������������ ���������� �����
	int rowOrCol, finishLineDirection;
	// ������� �������� ������ �����, ���� 0, �� ��� �����
	int blanks{ n*n };
	// ���� ������� ���������, 0 - �����, 1 - �������� ��������, 2 - ������
	int whoWin{ 0 };
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
			whoWin = finishedLineCheck(field, n, rowOrCol, finishLineDirection);
			if (whoWin) {
				endOfGame = 1;
			}
			// �������� �� �����
			if (!blanks && !endOfGame) {
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
			whoWin = finishedLineCheck(field, n, rowOrCol, finishLineDirection);
			if (whoWin) {
				endOfGame = 1;
			}
			// �������� �� �����
			if (!blanks && !endOfGame) {
				endOfGame = 1;
			}
		}

		// ����� ���������� ��������� ���� ���������

		// ���� ����
		window.clear(sf::Color(25, 0, 45));
		// ��������� �����
		drawField(window, n);
		// ��������� ��������� � �������
		drawFigures(window, n, field);
		// ������������� ���������� �����
		if (endOfGame && whoWin) {
			crossFinishLine(window, n, finishLineDirection, rowOrCol);
		}

		window.display();

		// ���������� �������, ��� �������
		if (endOfGame) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			res = whoWin;
			// ���� player vs AI � ��� ��� �� �����, ����� ������� �������� ����� ����������
			if (p == 2 && whoWin) {
				// ���� markAI = 0, �� ����������� ��� 2
				int _markAI = markAI ? 1 : 2;
				// ���� ������ AI ��������� � �������, ������� ��������, �� AI �������
				if (_markAI == whoWin) {
					res = 2;
				}
				else {
					res = 1;
				}
			}
			window.close();
		}

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