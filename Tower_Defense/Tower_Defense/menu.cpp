#include "menu.h"

#include <SFML/Graphics.hpp>
#include <string>

#include "globals.h"

void menu(bool &exitGame)
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// ���� ����
	sf::RenderWindow window(sf::VideoMode(410, 310), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	sf::Text chooseText("Choose level" , font, 40);
	chooseText.setFillColor(sf::Color(200, 200, 200));
	chooseText.setPosition(90, 15);

	sf::Texture levelTextures[6];
	for (int i = 0; i < 6; ++i) {
		levelTextures[i].loadFromFile("images/levels/level" + std::to_string(i + 1) + ".png");
	}

	sf::Sprite levelSprites[6];
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			levelSprites[i * 3 + j].setTexture(levelTextures[i * 3 + j]);
			levelSprites[i * 3 + j].setPosition(20 + j * (levelTextures[i * 3 + j].getSize().x + 20),
				window.getSize().y - (2 - i) * (levelTextures[i * 3 + j].getSize().y + 20));
		}
	}

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
				exitGame = 1;
				window.close();
			}
			// ���� ������ ������ ����
			if (event.type == sf::Event::MouseButtonPressed) {
				// ������ 3 ������
				if (y > levelSprites[0].getPosition().y && y < levelSprites[0].getPosition().y + levelTextures[0].getSize().y) {
					if (x > levelSprites[0].getPosition().x && x < levelSprites[0].getPosition().x + levelTextures[0].getSize().x) {
						level = 1;
						window.close();
					}
					if (x > levelSprites[1].getPosition().x && x < levelSprites[1].getPosition().x + levelTextures[1].getSize().x) {
						level = 2;
						window.close();
					}
					if (x > levelSprites[2].getPosition().x && x < levelSprites[2].getPosition().x + levelTextures[2].getSize().x) {
						level = 3;
						window.close();
					}
				}
				// ������ 3 ������
				if (y > levelSprites[3].getPosition().y && y < levelSprites[3].getPosition().y + levelTextures[3].getSize().y) {
					if (x > levelSprites[3].getPosition().x && x < levelSprites[3].getPosition().x + levelTextures[3].getSize().x) {
						level = 4;
						window.close();
					}
					if (x > levelSprites[4].getPosition().x && x < levelSprites[4].getPosition().x + levelTextures[4].getSize().x) {
						level = 5;
						window.close();
					}
					if (x > levelSprites[5].getPosition().x && x < levelSprites[5].getPosition().x + levelTextures[5].getSize().x) {
						level = 6;
						window.close();
					}
				}
			}
		}

		window.clear(sf::Color(0, 0, 0));

		window.draw(chooseText);
		for (auto & var : levelSprites) {
			window.draw(var);
		}

		window.display();
	}
}