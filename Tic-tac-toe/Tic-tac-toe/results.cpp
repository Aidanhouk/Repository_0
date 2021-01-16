#include "results.h"

#include <SFML/Graphics.hpp>

void results(int res, int p, bool &gameConinues)
{
	using sf::Text;
	using sf::Color;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	sf::RenderWindow result(sf::VideoMode(220, 290), "Tic-tac-toe", sf::Style::Titlebar | sf::Style::Close, settings);
	
	Text whoWonText;
	// обработка результата
	switch (p)
	{
	case 1:
		switch (res)
		{
		case -1:
			break;
		case 0:
			// draw
			whoWonText = Text("Draw", font, 35);
			whoWonText.setPosition(70, 20);
			break;
		case 1:
			// 1 player won
			whoWonText = Text("Player 1 won", font, 35);
			whoWonText.setPosition(15, 20);
			break;
		case 2:
			// 2 player won
			whoWonText = Text("Player 2 won", font, 35);
			whoWonText.setPosition(10, 20);
			break;
		}
		break;
	case 2:
		switch (res)
		{
		case -1:
			break;
		case 0:
			// draw
			whoWonText = Text("Draw", font, 35);
			whoWonText.setPosition(70, 20);
			break;
		case 1:
			// player won
			whoWonText = Text("Player won", font, 35);
			whoWonText.setPosition(25, 20);
			break;
		case 2:
			// AI won
			whoWonText = Text("AI won", font, 35);
			whoWonText.setPosition(60, 20);
			break;
		}
		break;
	case 3:
		switch (res)
		{
		case -1:
			break;
		case 0:
			// draw
			whoWonText = Text("Draw", font, 35);
			whoWonText.setPosition(70, 20);
			break;
		case 1:
			// 1 AI won
			whoWonText = Text("AI won", font, 35);
			whoWonText.setPosition(60, 20);
			break;
		case 2:
			// 2 AI won
			whoWonText = Text("AI won", font, 35);
			whoWonText.setPosition(60, 20);
			break;
		}
		break;
	}
	whoWonText.setFillColor(Color(210, 100, 110));

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
		// текст, кто победил
		if (res != -1) {
			result.draw(whoWonText);
		}
		// текст Play again
		result.draw(playAgain);
		// текст Exit
		result.draw(exitText);

		result.display();
	}
}