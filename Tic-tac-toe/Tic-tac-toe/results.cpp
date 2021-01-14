#include <SFML/Graphics.hpp>
#include "results.h"

void results(int res, int p, bool &gameConinues)
{
	using sf::Text;
	using sf::Color;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	sf::RenderWindow result(sf::VideoMode(220, 290), "Tic-tac-toe", sf::Style::Titlebar | sf::Style::Close, settings);

	Text drawText("Draw", font, 35);
	drawText.setFillColor(Color(210, 100, 110));
	drawText.setPosition(70, 20);

	Text player1("Player 1 won", font, 35);
	player1.setFillColor(Color(210, 100, 110));
	player1.setPosition(15, 20);

	Text player2("Player 2 won", font, 35);
	player2.setFillColor(Color(210, 100, 110));
	player2.setPosition(15, 20);

	Text player("Player won", font, 35);
	player.setFillColor(Color(210, 100, 110));
	player.setPosition(25, 20);

	Text _AIwon("AI won", font, 35);
	_AIwon.setFillColor(Color(210, 100, 110));
	_AIwon.setPosition(60, 20);

	Text playAgain("Play again", font, 35);
	playAgain.setFillColor(Color(4, 217, 167));
	playAgain.setPosition(30, 120);

	Text exitText("Exit", font, 35);
	exitText.setFillColor(Color::White);
	exitText.setPosition(80, 220);

	while (result.isOpen())
	{
		// получаем координаты курсора мышы
		sf::Vector2i pos = sf::Mouse::getPosition(result);
		int x{ pos.x };
		int y{ pos.y };

		sf::Event event;
		// обработчик событий
		while (result.pollEvent(event))
		{
			// закрытие окна
			if (event.type == sf::Event::Closed) {
				gameConinues = 0;
				result.close();
			}
			// нажата кнопка мыши?
			if (event.type == sf::Event::MouseButtonPressed) {
				// если ЛКМ
				if (event.mouseButton.button == sf::Mouse::Left) {
					// если нажал на Play again
					if (x > 30 && x < 200 && y > 120 && y < 160) {
						result.close();
					}
					// если нажал на Exit
					if (x > 80 && x < 140 && y > 220 && y < 260) {
						gameConinues = 0;
						result.close();
					}
				}
			}
		}
		// цвет фона
		result.clear(Color(25, 0, 45));

		// обработка результата
		switch (p)
		{
		case 1:
			switch (res)
			{
			case 0:
				// draw
				result.draw(drawText);
				break;
			case 1:
				// 1 player won
				result.draw(player1);
				break;
			case 2:
				// 2 player won
				result.draw(player2);
				break;
			}
			break;
		case 2:
			switch (res)
			{
			case 0:
				// draw
				result.draw(drawText);
				break;
			case 1:
				// player won
				result.draw(player);
				break;
			case 2:
				// AI won
				result.draw(_AIwon);
				break;
			}
			break;
		case 3:
			switch (res)
			{
			case 0:
				// draw
				result.draw(drawText);
				break;
			case 1:
				// 1 AI won
				result.draw(_AIwon);
				break;
			case 2:
				// 2 AI won
				result.draw(_AIwon);
				break;
			}
			break;
		}

		result.draw(playAgain);
		result.draw(exitText);

		result.display();
	}
}