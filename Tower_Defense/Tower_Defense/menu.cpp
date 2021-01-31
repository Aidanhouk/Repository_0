#include "globals.h"

void menu(bool &exitGame)
{
	sf::Font font;
	font.loadFromFile("font8bit.ttf");

	// окно меню
	sf::RenderWindow menuWindow(sf::VideoMode(410, 310), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	sf::Text chooseText("Choose level" , font, 60);
	chooseText.setFillColor(sf::Color(200, 200, 200));
	chooseText.setPosition(50, -10);

	sf::Texture levelTextures[6];
	for (int i = 0; i < 6; ++i) {
		levelTextures[i].loadFromFile("images/levels/level" + std::to_string(i + 1) + ".png");
	}

	sf::Sprite levelSprites[6];
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			levelSprites[i * 3 + j].setTexture(levelTextures[i * 3 + j]);
			levelSprites[i * 3 + j].setPosition(20 + j * (levelTextures[i * 3 + j].getSize().x + 20),
				menuWindow.getSize().y - (2 - i) * (levelTextures[i * 3 + j].getSize().y + 20));
		}
	}

	while (menuWindow.isOpen())
	{
		// получаем координаты курсора мышы
		sf::Vector2i pos = sf::Mouse::getPosition(menuWindow);
		int x{ pos.x };
		int y{ pos.y };

		sf::Event event;
		// обработчик событий
		while (menuWindow.pollEvent(event))
		{
			// закрытие окна
			if (event.type == sf::Event::Closed) {
				exitGame = 1;
				menuWindow.close();
			}
			// если нажата кнопка мыши
			if (event.type == sf::Event::MouseButtonPressed) {
				// первые 3 уровня
				if (y > levelSprites[0].getPosition().y && y < levelSprites[0].getPosition().y + levelTextures[0].getSize().y) {
					if (x > levelSprites[0].getPosition().x && x < levelSprites[0].getPosition().x + levelTextures[0].getSize().x) {
						level = 1;
						menuWindow.close();
					}
					if (x > levelSprites[1].getPosition().x && x < levelSprites[1].getPosition().x + levelTextures[1].getSize().x) {
						level = 2;
						menuWindow.close();
					}
					if (x > levelSprites[2].getPosition().x && x < levelSprites[2].getPosition().x + levelTextures[2].getSize().x) {
						level = 3;
						menuWindow.close();
					}
				}
				// вторые 3 уровня
				if (y > levelSprites[3].getPosition().y && y < levelSprites[3].getPosition().y + levelTextures[3].getSize().y) {
					if (x > levelSprites[3].getPosition().x && x < levelSprites[3].getPosition().x + levelTextures[3].getSize().x) {
						level = 4;
						menuWindow.close();
					}
					if (x > levelSprites[4].getPosition().x && x < levelSprites[4].getPosition().x + levelTextures[4].getSize().x) {
						level = 5;
						menuWindow.close();
					}
					if (x > levelSprites[5].getPosition().x && x < levelSprites[5].getPosition().x + levelTextures[5].getSize().x) {
						level = 6;
						menuWindow.close();
					}
				}
			}
		}

		menuWindow.clear(sf::Color::Black);

		menuWindow.draw(chooseText);
		for (auto & var : levelSprites) {
			menuWindow.draw(var);
		}

		menuWindow.display();
	}
}