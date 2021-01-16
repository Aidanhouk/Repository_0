#include "drawing.h"

#include "consts.h"

void drawField(sf::RenderWindow & window, int n)
{
	for (int i = 1; i < n; ++i) {
		// по вертикали
		sf::RectangleShape bordersV(sf::Vector2f(5, n * W));
		bordersV.move(W * i, 0);
		bordersV.setFillColor(sf::Color(80, 44, 112));
		window.draw(bordersV);
		// по горизонтали
		sf::RectangleShape bordersH(sf::Vector2f(n * W, 5));
		bordersH.move(0, W * i);
		bordersH.setFillColor(sf::Color(80, 44, 112));
		window.draw(bordersH);
	}
}

void drawFigures(sf::RenderWindow & window, int n, int **field)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// крестики
			if (field[i][j] == 1) {
				sf::RectangleShape cross(sf::Vector2f(5, 60));
				cross.move(W * i + 30, W * j + 30);
				cross.rotate(-45.f);
				cross.setFillColor(sf::Color(4, 217, 167));
				window.draw(cross);
				sf::RectangleShape cross2(sf::Vector2f(5, 60));
				cross2.move(W * i + 72, W * j + 26);
				cross2.rotate(45.f);
				cross2.setFillColor(sf::Color(4, 217, 167));
				window.draw(cross2);
			}
			// нолики
			if (field[i][j] == 2) {
				sf::CircleShape nought(30);
				nought.move(W * i + 23, W * j + 23);
				nought.setFillColor(sf::Color(210, 100, 110));
				window.draw(nought);
				sf::CircleShape nought2(22);
				nought2.move(W * i + 31, W * j + 31);
				nought2.setFillColor(sf::Color(25, 0, 45));
				window.draw(nought2);
			}
		}
	}
}

void crossFinishLine(sf::RenderWindow & window, int n, int finishLineDirection, int rowOrCol)
{
	sf::RectangleShape line;
	// кол-во пикселей от края
	int pixels = 15;
	switch (finishLineDirection) {
	case 1:
		line = sf::RectangleShape(sf::Vector2f(5, n * W - pixels * 2));
		line.move(W * rowOrCol + 50, pixels);
		break;
	case 2:
		line = sf::RectangleShape(sf::Vector2f(n * W - pixels * 2, 5));
		line.move(pixels, W * rowOrCol + 50);
		break;
	case 3:
		line = sf::RectangleShape(sf::Vector2f(n * W * 1.41f - pixels * 2, 5));
		line.move(pixels, pixels);
		line.rotate(45.f);
		break;
	case 4:
		line = sf::RectangleShape(sf::Vector2f(n * W * 1.41f - pixels * 2, 5));
		line.move(pixels, W * n - pixels);
		line.rotate(-45.f);
		break;
	}
	line.setFillColor(sf::Color::Yellow);
	window.draw(line);
}