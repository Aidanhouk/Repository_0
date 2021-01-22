#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class Shop
{
private:
	// шрифт текстов
	sf::Font *m_font;
	// фон магазина
	sf::RectangleShape *m_border;
	// тектуры башен
	sf::Texture* m_towersTextures[TOWERS_COUNT]{ nullptr };
	// рамка выбранной башни
	sf::RectangleShape* m_chosenTowerFrame[4];
public:
	Shop();
	~Shop();
	// отрисовываем весь магазин
	void drawShop(int level, int money, int type, sf::RenderWindow &window);
};