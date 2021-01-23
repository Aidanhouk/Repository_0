#include "results.h"

#include <SFML/Graphics.hpp>
#include <string>

void result(int result, int waveLevel, bool &playAgain)
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// ���� ����
	sf::RenderWindow window(sf::VideoMode(300, 250), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	// ���� ����� ����� � ����������� ����
	sf::Text resultText;

	switch (result)
	{
		// ���� ������ ����
	case 0:
		resultText = sf::Text("Tower Defense", font, 35);
		resultText.setPosition(30, 20);
		break;
		// ���� ������ ����
	case 1:
		resultText = sf::Text("You won!", font, 35);
		resultText.setPosition(75, 20);
		break;
		// ���� ��������
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

	// ������� ���� ����
	while (window.isOpen())
	{
		// �������� ���������� ������� ����
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x{ pos.x };
		int y{ pos.y };

		sf::Event event;
		// ���������� �������
		while (window.pollEvent(event))
		{
			// �������� ����
			if (event.type == sf::Event::Closed) {
				playAgain = 0;
				window.close();
			}
			// ���� ������ ������ ����
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