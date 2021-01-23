#include "menu.h"

#include <SFML/Graphics.hpp>

void menu(int &level)
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно игры
	sf::RenderWindow window(sf::VideoMode(410, 200), "Tower defense", sf::Style::Titlebar | sf::Style::Close);

	sf::Text chooseText("Choose level" , font, 40);
	chooseText.setFillColor(sf::Color(200, 200, 200));
	chooseText.setPosition(90, 15);

	sf::Texture level1Texture;
	level1Texture.loadFromFile("images/levels/level1.png");
	sf::Sprite level1;
	level1.setTexture(level1Texture);
	level1.setPosition(20, window.getSize().y - 20 - level1Texture.getSize().y);

	sf::Texture level2Texture;
	level2Texture.loadFromFile("images/levels/level2.png");
	sf::Sprite level2;
	level2.setTexture(level2Texture);
	level2.setPosition(20 + level2Texture.getSize().x + 20, window.getSize().y - 20 - level2Texture.getSize().y);

	sf::Texture level3Texture;
	level3Texture.loadFromFile("images/levels/level3.png");
	sf::Sprite level3;
	level3.setTexture(level3Texture);
	level3.setPosition(20 + 2 * (level3Texture.getSize().x + 20), window.getSize().y - 20 - level3Texture.getSize().y);

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
				window.close();
			}
			// если нажата кнопка мыши
			if (event.type == sf::Event::MouseButtonPressed) {
				if (y > level1.getPosition().y && y < level1.getPosition().y + level1Texture.getSize().y) {
					// level 1
					if (x > level1.getPosition().x && x < level1.getPosition().x + level1Texture.getSize().x) {
						level = 1;
						window.close();
					}
					// level 2
					if (x > level2.getPosition().x && x < level2.getPosition().x + level2Texture.getSize().x) {
						level = 2;
						window.close();
					}
					// level 3
					if (x > level3.getPosition().x && x < level3.getPosition().x + level3Texture.getSize().x) {
						level = 3;
						window.close();
					}
				}
			}
		}

		window.clear(sf::Color(0, 0, 0));

		window.draw(chooseText);
		window.draw(level1);
		window.draw(level2);
		window.draw(level3);

		window.display();
	}
}