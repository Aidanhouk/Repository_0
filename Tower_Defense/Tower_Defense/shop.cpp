#include "shop.h"

#include <string>

Shop::Shop()
{
	// скачиваем шрифт
	m_font = new sf::Font();
	(*m_font).loadFromFile("sansation.ttf");

	// создаем объект фона магазина
	m_border = new sf::RectangleShape(sf::Vector2f(W * COLS, W * 1.5));
	(*m_border).move(0, W * ROWS);
	(*m_border).setFillColor(sf::Color::Black);

	// скачиваем и записываем текстуры башен
	for (int i = 1; i < TOWERS_COUNT; ++i) {
		sf::Texture *tower{ new sf::Texture() };
		(*tower).loadFromFile("images/towers/tower" + std::to_string(i) + ".png");
		m_towersTextures[i] = tower;
	}

	// добавляем прямоугольники для обводки выбранно башни
	sf::RectangleShape *chosenTower1{ new sf::RectangleShape(sf::Vector2f(W, W / 10)) };
	(*chosenTower1).setFillColor(sf::Color(0, 255, 0));
	m_chosenTowerFrame[0] = chosenTower1;
	m_chosenTowerFrame[1] = chosenTower1;
	sf::RectangleShape *chosenTower2{ new sf::RectangleShape(sf::Vector2f(W / 10, W)) };
	(*chosenTower2).setFillColor(sf::Color(0, 255, 0));
	m_chosenTowerFrame[2] = chosenTower2;
	m_chosenTowerFrame[3] = chosenTower2;
}

Shop::~Shop()
{
	for (auto var : m_towersTextures) {
		if (var) {
			delete var;
		}
	}
	delete m_chosenTowerFrame[0];
	delete m_chosenTowerFrame[2];
	delete m_font;
	delete m_border;
}

void Shop::drawShop(int level, int money, int type, sf::RenderWindow & window)
{
	// область покупки башен
	window.draw(*m_border);

	// рисуем деньги
	sf::Text moneyText("Coins:  " + std::to_string(money), *m_font, 40);
	moneyText.setFillColor(sf::Color::Yellow);
	moneyText.setPosition(W * (COLS - 2.5), W * ROWS + 10);
	window.draw(moneyText);

	// рисуем уровень
	sf::Text levelText("Wave:  " + std::to_string(level), *m_font, 40);
	levelText.setFillColor(sf::Color::Red);
	levelText.setPosition(W * (COLS - 2.4), W * ROWS + W * 0.7);
	window.draw(levelText);

	// рисуем башни и их стоимость
	for (int i = 1; i < TOWERS_COUNT; ++i) {
		sf::Sprite tower(*m_towersTextures[i]);
		tower.setPosition(W * (i - 1), W * ROWS);
		window.draw(tower);
		sf::Text cost(std::to_string(TOWERS_PRICE[i]), *m_font, 30);
		cost.setFillColor(sf::Color::Yellow);
		cost.setPosition(W * (i - 1) + W * 0.3, W * (ROWS + 1));
		window.draw(cost);
	}

	// обводим выбранную башню
	(*m_chosenTowerFrame[0]).setPosition(W * (type - 1), W * ROWS);
	window.draw(*m_chosenTowerFrame[0]);
	(*m_chosenTowerFrame[1]).setPosition(W * (type - 1), W * ROWS + W - W / 10);
	window.draw((*m_chosenTowerFrame[1]));
	(*m_chosenTowerFrame[2]).setPosition(W * (type - 1), W * ROWS);
	window.draw((*m_chosenTowerFrame[2]));
	(*m_chosenTowerFrame[3]).setPosition(W * (type - 1) + W - W / 10, W * ROWS);
	window.draw((*m_chosenTowerFrame[3]));
}
