#include "results.h"

#include <SFML/Graphics.hpp>
#include <string>

void result(int result, int waveLevel, bool &playAgain)
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно игры
	sf::RenderWindow window(sf::VideoMode(300, 250), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	// сюда запиш текст с результатом игры
	sf::Text resultText;

	switch (result)
	{
		// если закрыл окно
	case 0:
		resultText = sf::Text("Tower Defense", font, 35);
		resultText.setPosition(30, 20);
		break;
		// если прошел игру
	case 1:
		resultText = sf::Text("You won!", font, 35);
		resultText.setPosition(75, 20);
		break;
		// если проиграл
	case 2:
		resultText = sf::Text("You got to wave  " + std::to_string(waveLevel), font, 35);
		resultText.setPosition(10, 20);
		break;
	}
	resultText.setFillColor(sf::Color(200, 200, 200));

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
			// если нажата кнопка мыши
			if (event.type == sf::Event::MouseButtonPressed) {
				// play again
				if (x > playAgainText.getPosition().x && x < window.getSize().x - playAgainText.getPosition().x
					&& y > playAgainText.getPosition().y && y < playAgainText.getPosition().y + 45) {
					window.close();
				}
				// exit
				if (x > exitText.getPosition().x && x < window.getSize().x - exitText.getPosition().x
					&& y > exitText.getPosition().y && y < exitText.getPosition().y + 40) {
					playAgain = 0;
					window.close();
				}
			}
		}

		window.clear(sf::Color(0, 0, 0));
		
		window.draw(resultText);
		window.draw(playAgainText);
		window.draw(exitText);

		window.display();
	}
}