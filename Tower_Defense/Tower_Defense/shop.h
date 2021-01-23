#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

// класс, отвечающий за область покупки
class Shop
{
private:
	// шрифт текстов
	sf::Font *m_font;
	// фон магазина
	sf::RectangleShape *m_border;
	// тектуры башен и блоков
	sf::Texture* m_towersTextures[TOWERS_COUNT + FIELD_BLOCKS_COUNT - 1]{ nullptr };
	// рамка выбранной башни/блока
	sf::RectangleShape* m_chosenTowerFrame[4];
public:
	Shop();
	~Shop();
	// отрисовываем весь магазин
	void drawShop(int level, int money, int type, sf::RenderWindow &window);
};