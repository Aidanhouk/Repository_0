#include "results.h"

#include <SFML/Graphics.hpp>
#include <string>

void result(int result, int level, bool &playAgain)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно игры
	sf::RenderWindow window(sf::VideoMode(300, 250), "Tower defense", sf::Style::Titlebar | sf::Style::Close, settings);

	sf::Text lostText("You got to level  " + std::to_string(level), font, 35);
	lostText.setFillColor(sf::Color(200, 200, 200));
	lostText.setPosition(10, 20);

	sf::Text wonText("You won!", font, 35);
	wonText.setFillColor(sf::Color(200, 200, 200));
	wonText.setPosition(75, 20);

	sf::Text closedText("You can do it", font, 35);
	closedText.setFillColor(sf::Color(200, 200, 200));
	closedText.setPosition(50, 20);

	sf::Text playAgainText("Play again", font, 35);
	playAgainText.setFillColor(sf::Color(200, 200, 200));
	playAgainText.setPosition(65, 100);

	sf::Text exitText("Exit", font, 35);
	exitText.setFillColor(sf::Color(200, 200, 200));
	exitText.setPosition(120, 180);

	// главный цикл игры
	while (window.isOpen())
	{
		// получаем координаты курсора мышы
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x{ pos.x };
		int y{ pos.y };

		sf::Event event;
		// обработчик событий
		while (window.pollEvent(event))
		{
			// закрытие окна
			if (event.type == sf::Event::Closed) {
				playAgain = 0;
				window.close();
			}
			// если нажата кнопка мыши и игра не закончена
			if (event.type == sf::Event::MouseButtonPressed) {
				// play again
				if (x > 65 && x < 300 - 65 && y > 100 && y < 100 + 45) {
					window.close();
				}
				// exit
				if (x > 120 && x < 300 - 120 && y > 180 && y < 180 + 45) {
					playAgain = 0;
					window.close();
				}
			}
		}

		window.clear(sf::Color(30, 115, 30));
		
		switch (result)
		{
		case 0:
			window.draw(closedText);
			break;
		case 1:
			window.draw(wonText);
			break;
		case 2:
			window.draw(lostText);
			break;
		}
		window.draw(playAgainText);
		window.draw(exitText);

		window.display();
	}
}