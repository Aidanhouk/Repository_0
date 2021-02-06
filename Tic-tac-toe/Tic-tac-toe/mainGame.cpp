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

	// ���� ����
	sf::RenderWindow _window(sf::VideoMode(n * 100, n * 100), "Tic-tac-toe", sf::Style::Titlebar | sf::Style::Close, settings);
	window = &_window;

	// ����
	Field _field;
	field = &_field;

	// AI, � ���������� ����� �������, �� ����� ������ ����� ������ AI, 1 - ��������, 2 - ������
	AI _AI((rand() % 2) + 1);

	// ����� ����
	bool endOfGame{ 0 };
	// ����� ������ ��������, 0 - �����, 1 - �������� ��������, 2 - ������
	int whoWon{ 0 };

	// ������� ���� ����
	while (window->isOpen())
	{
		// ��� ������
		if (!endOfGame) {
			// �������� ���������� ������� ����
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			int x{ pos.x / W };
			int y{ pos.y / W };

			sf::Event event;
			// ���������� �������
			while (window->pollEvent(event))
			{
				// �������� ����
				if (event.type == sf::Event::Closed) {
					window->close();
				}
				// ���� ������ ������ ����
				if (event.type == sf::Event::MouseButtonPressed) {
					// ���� ���� � �������� ������ � ��� ���� ������ ��� ������
					if (_WhoVsWho == 1 || (_WhoVsWho == 2 && field->getTurn() != _AI.getAIMark())) {
						// ���� ��� ������ ������
						if (!(*field)[x][y]) {
							// ��������� ��� ������ � ������ � ������, ���� ���� ������ AI
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
			// �������� �� ����� ���� ����� ���� ������
			if (_WhoVsWho != 3) {
				whoWon = field->finishedLineCheck();
				// ���� whoWon = 1, �� �������� ��������, 2 - ������
				if (whoWon) {
					endOfGame = 1;
				}
				else {
					// �������� �� �����
					if (field->isDraw()) {
						endOfGame = 1;
					}
				}
			}
		}

		// ��� AI
		if (!endOfGame) {
			if (_WhoVsWho == 2 && field->getTurn() == _AI.getAIMark() || _WhoVsWho == 3) {
				// ���� ��������� ������ ������ � ������� ������, ������� ������ AI
				int row, col;
				_AI._AI_makes_move(col, row);
				(*field)[row][col] = field->getTurn();
				field->changeTurn();
				field->decreaseBlanks();
			}
			// �������� �� ����� ���� ����� ���� AI
			if (_WhoVsWho != 1) {
				whoWon = field->finishedLineCheck();
				// ���� whoWon = 1, �� �������� ��������, 2 - ������
				if (whoWon) {
					endOfGame = 1;
				}
				else {
					// �������� �� �����
					if (field->isDraw()) {
						endOfGame = 1;
					}
				}
			}
		}

		// ����� ���������� ��������� ���� ���������

		// ���� ����
		window->clear(sf::Color(25, 0, 45));
		// ��������� �����
		drawField();
		// ��������� ��������� � �������
		drawFigures();
		// ������������� ���������� �����
		if (endOfGame && whoWon) {
			crossFinishLine();
		}
		window->display();

		// ���������� ��������, ��� �������
		if (endOfGame) {
			sf::sleep(sf::Time(sf::milliseconds(500)));
			gameResult = whoWon;
			// ���� player vs AI � ��� ��� �� �����, ����� ������� �������� ��������� ����������
			if (_WhoVsWho == 2 && whoWon) {
				// ���� ������ AI ��������� � �������, ������� ��������, �� AI ������� (2)
				gameResult = (_AI.getAIMark() == whoWon) ? 2 : 1;
			}
			window->close();
		}

		// ����� ����� ������ AI vs AI
		if (_WhoVsWho == 3 && !endOfGame) {
			sf::sleep(sf::Time(sf::milliseconds(500)));
		}
	}
}