#include "results.h"

#include <SFML/Graphics.hpp>
#include <string>

#include "globals.h"

void results(bool &exitGame)
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно игры
	sf::RenderWindow resultsWindow(sf::VideoMode(320, 250), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	// сюда запиш текст с результатом игры
	sf::Text resultText;

	switch (result)
	{
		// если закрыл окно
	case 0:
		resultText = sf::Text("Tower Defense", font, 35);
		resultText.setPosition(40, 20);
		break;
		// если прошел игру
	case 1:
		resultText = sf::Text("You won!", font, 35);
		resultText.setPosition(85, 20);
		break;
		// если проиграл
	case 2:
		resultText = sf::Text("You got to wave " + std::to_string(waveLevel), font, 35);
		resultText.setPosition(15, 20);
		break;
	}
	resultText.setFillColor(sf::Color(200, 200, 200));

	sf::Text playAgainText("Play again", font, 35);
	playAgainText.setFillColor(sf::Color(200, 200, 200));
	playAgainText.setPosition(75, 100);

	sf::Text exitText("Exit", font, 35);
	exitText.setFillColor(sf::Color(200, 200, 200));
	exitText.setPosition(130, 180);

	while (resultsWindow.isOpen())
	{
		// получаем координаты курсора мышы
		sf::Vector2i pos = sf::Mouse::getPosition(resultsWindow);
		int x{ pos.x };
		int y{ pos.y };

		sf::Event event;
		// обработчик событий
		while (resultsWindow.pollEvent(event))
		{
			// закрытие окна
			if (event.type == sf::Event::Closed) {
				resultsWindow.close();
				exitGame = 1;
			}
			// если нажата кнопка мыши
			if (event.type == sf::Event::MouseButtonPressed) {
				// play again
				if (x > playAgainText.getPosition().x && x < resultsWindow.getSize().x - playAgainText.getPosition().x
					&& y > playAgainText.getPosition().y && y < playAgainText.getPosition().y + 45) {
					resultsWindow.close();
				}
				// exit
				if (x > exitText.getPosition().x && x < resultsWindow.getSize().x - exitText.getPosition().x
					&& y > exitText.getPosition().y && y < exitText.getPosition().y + 40) {
					exitGame = 1;
					resultsWindow.close();
				}
			}
		}

		resultsWindow.clear(sf::Color(0, 0, 0));
		
		resultsWindow.draw(resultText);
		resultsWindow.draw(playAgainText);
		resultsWindow.draw(exitText);

		resultsWindow.display();
	}
}