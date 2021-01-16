#include "drawShop.h"

#include "consts.h"

#include <string>

void drawShop(int level, int money, int type, sf::RenderWindow &window)
{
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// область покупки башен
	sf::RectangleShape border(sf::Vector2f(W * COLS, W));
	border.move(0, W * ROWS);
	border.setFillColor(sf::Color::Black);
	window.draw(border);

	// рисуем деньги
	sf::Text moneyText("Coins:  " + std::to_string(money), font, 40);
	moneyText.setFillColor(sf::Color::Yellow);
	moneyText.setPosition(W * (COLS - 5) + 15, W * ROWS + 15);
	window.draw(moneyText);

	// рисуем уровень
	sf::Text levelText("Wave:  " + std::to_string(level), font, 40);
	levelText.setFillColor(sf::Color::Red);
	levelText.setPosition(W * (COLS - 2), W * ROWS + 15);
	window.draw(levelText);

	sf::CircleShape tower1(25, 10);
	tower1.setPosition(15, W * ROWS + 15);
	tower1.setFillColor(sf::Color(115, 190, 250));

	sf::CircleShape tower2(25, 10);
	tower2.setPosition(15 + W, W * ROWS + 15);
	tower2.setFillColor(sf::Color(240, 85, 85));

	sf::CircleShape tower3(25, 10);
	tower3.setPosition(15 + 2 * W, W * ROWS + 15);
	tower3.setFillColor(sf::Color(210, 40, 255));

	// указывает на выбранную башню
	sf::CircleShape smallCirlce(15, 10);
	smallCirlce.setFillColor(sf::Color::Green);

	// делаем прозрачными те башни, на которые не хватает денег
	if (money < TOWERS_PRICE[1]) {
		tower1.setFillColor(sf::Color(115, 190, 250, 50));
		tower2.setFillColor(sf::Color(240, 85, 85, 50));
		tower3.setFillColor(sf::Color(210, 40, 255, 50));
	}
	else {
		if (money < TOWERS_PRICE[2]) {
			tower2.setFillColor(sf::Color(240, 85, 85, 50));
			tower3.setFillColor(sf::Color(210, 40, 255, 50));
		}
		else {
			if (money < TOWERS_PRICE[3]) {
				tower3.setFillColor(sf::Color(210, 40, 255, 50));
			}
		}
	}

	window.draw(tower1);
	window.draw(tower2);
	window.draw(tower3);

	// подсвечиваем ту башню, которую выбрал игрок
	switch (type)
	{
	case 0:
		break;
	case 1:
		smallCirlce.setPosition(25, W * ROWS + 25);
		window.draw(smallCirlce);
		break;
	case 2:
		smallCirlce.setPosition(25 + 1 * W, W * ROWS + 25);
		window.draw(smallCirlce);
		break;
	case 3:
		smallCirlce.setPosition(25 + 2 * W, W * ROWS + 25);
		window.draw(smallCirlce);
		break;
	}
}