#include "shop.h"

#include "globals.h"

Shop::Shop()
{
	// скачиваем шрифты
	m_font1 = new sf::Font();
	(*m_font1).loadFromFile("font8bit.ttf");
	m_font2 = new sf::Font();
	(*m_font2).loadFromFile("sansation.ttf");

	// скачиваем и записываем текстуры башен
	for (int i = 1; i < TOWERS_COUNT; ++i) {
		sf::Texture *tower{ new sf::Texture() };
		(*tower).loadFromFile("images/towers/tower" + std::to_string(i) + ".png");
		m_towersTextures[i] = tower;
	}

	// скачиваем и записываем текстуры блоков
	for (int i = 1; i < FIELD_BLOCKS_COUNT; ++i) {
		sf::Texture *block{ new sf::Texture() };
		(*block).loadFromFile("images/fieldBlocks/block" + std::to_string(i) + ".png");
		m_towersTextures[TOWERS_COUNT + i - 1] = block;
	}

	// скачиваем и записываем текстуру монеты
	m_coinTexture = new sf::Texture();
	(*m_coinTexture).loadFromFile("images/other/coin.png");

	// скачиваем и записываем текстуру иконки норм скорости
	m_normalTexture = new sf::Texture();
	(*m_normalTexture).loadFromFile("images/other/normal.png");

	// скачиваем и записываем текстуру иконки быстрой скорости
	m_fasterTexture = new sf::Texture();
	(*m_fasterTexture).loadFromFile("images/other/faster.png");

	// скачиваем и записываем текстуру иконки старта
	m_startTexture = new sf::Texture();
	(*m_startTexture).loadFromFile("images/other/start.png");

	// скачиваем и записываем текстуру иконки пазуы
	m_pauseTexture = new sf::Texture();
	(*m_pauseTexture).loadFromFile("images/other/pause.png");
	
	// скачиваем текстуру окна информации
	m_infoTexture = new sf::Texture();
	(*m_infoTexture).loadFromFile("images/other/infoWindow.png");

	// добавляем прямоугольники для обводки выбранного объекта для покупки
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
	delete m_font1;
	delete m_font2;
	delete m_coinTexture;
	delete m_normalTexture;
	delete m_fasterTexture;
	delete m_startTexture;
	delete m_pauseTexture;
	delete m_infoTexture;
}

void Shop::drawShop(int currentWave, int maxWaveLevel, int blockType)
{
	// область  магазина
	sf::RectangleShape backgroud1(sf::Vector2f(W * 2, W * ROWS));
	backgroud1.move(W * COLS, 0);
	backgroud1.setFillColor(sf::Color::Black);
	(*window).draw(backgroud1);
	sf::RectangleShape backgroud2(sf::Vector2f(W * (COLS + 2), W));
	backgroud2.move(0, W * ROWS);
	backgroud2.setFillColor(sf::Color::Black);
	(*window).draw(backgroud2);

	// текст с деньгами + монета
	sf::Sprite coin(*m_coinTexture);
	coin.setPosition(W * (COLS + 1), 0);
	(*window).draw(coin);
	sf::Text moneyText(std::to_string(money), *m_font2, 40);
	moneyText.setFillColor(sf::Color::Yellow);
	moneyText.setPosition(W * (COLS + 0.1), W / 5);
	(*window).draw(moneyText);

	// иконка старта / паузы
	sf::Sprite pauseIcon;
	if (pause) {
		pauseIcon.setTexture(*m_startTexture);
		pauseIcon.setPosition(W * COLS + 30, W * (ROWS - 1) + 20);
	}
	else {
		pauseIcon.setTexture(*m_pauseTexture);
		pauseIcon.setPosition(W * COLS, W * (ROWS - 1));
	}
	(*window).draw(pauseIcon);

	// иконка скорости игры
	sf::Sprite speedIcon;
	if (gameSpeed) {
		speedIcon.setTexture(*m_normalTexture);
	}
	else {
		speedIcon.setTexture(*m_fasterTexture);
	}
	speedIcon.setPosition(W * (COLS - 1), W * (ROWS));
	(*window).draw(speedIcon);

	// текст с номером волны
	sf::Text levelText("Power  " + std::to_string(currentWave) + "/" + std::to_string(maxWaveLevel), *m_font1, 80);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(W * 3.25, W * ROWS - W * 0.25);
	(*window).draw(levelText);

	// рисуем башни, блоки и их стоимость
	bool x{ 0 };
	double y{ 0 };
	for (int i = 1; i < TOWERS_COUNT + FIELD_BLOCKS_COUNT - 1; ++i) {
		sf::Sprite block(*m_towersTextures[i]);
		block.setPosition(W * (COLS + x), W * (1 + y));
		(*window).draw(block);
		// рисуем их стоимость
		int price{ (i < TOWERS_COUNT) ? TOWERS_PRICE[i] : BLOCKS_PRICE[i - TOWERS_COUNT + 1] };
		sf::Text cost(std::to_string(price), *m_font2, 30);
		if (money >= price) {
			cost.setFillColor(sf::Color::Yellow);
		}
		else {
			cost.setFillColor(sf::Color::Red);
		}
		cost.setPosition(block.getPosition().x + W * 0.25, block.getPosition().y + W);
		(*window).draw(cost);
		if (x) {
			y += 1.5;
			x = 0;
		}
		else {
			x = 1;
		}
	}

	// обводим выбранную башню/блок
	if (blockType) {
		int _x{ (blockType - 1) % 2 };
		int _y{ (blockType - 1) >> 1 };
		(*m_chosenTowerFrame[0]).setPosition(W * (COLS + _x), W * (1 + _y * 1.5));
		(*window).draw(*m_chosenTowerFrame[0]);
		(*m_chosenTowerFrame[1]).setPosition(W * (COLS + _x), W * (1 + _y * 1.5) + W - W / 10);
		(*window).draw((*m_chosenTowerFrame[1]));
		(*m_chosenTowerFrame[2]).setPosition(W * (COLS + _x), W * (1 + _y * 1.5));
		(*window).draw((*m_chosenTowerFrame[2]));
		(*m_chosenTowerFrame[3]).setPosition(W * (COLS + _x) + W - W / 10, W * (1 + _y * 1.5));
		(*window).draw((*m_chosenTowerFrame[3]));
	}
}

int Shop::returnItemNumber(int posX, int posY)
{
	int x{ posX / W };
	int y{ posY / W };
	switch (y)
	{
	case 1:
		if (x == COLS) {
			return 1;
		}
		else {
			return 2;
		}
		break;
	case 2:
		if (posY % W >= (W >> 1)) {
			if (x == COLS) {
				return 3;
			}
			else {
				return 4;
			}
		}
		break;
	case 3:
		if (posY % W < (W >> 1)) {
			if (x == COLS) {
				return 3;
			}
			else {
				return 4;
			}
		}
		break;
	case 4:
		if (x == COLS) {
			return 5;
		}
		else {
			return 6;
		}
		break;
	case 5:
		if (posY % W >= (W >> 1)) {
			if (x == COLS) {
				return 7;
			}
			else {
				return 8;
			}
		}
		break;
	case 6:
		if (posY % W < (W >> 1)) {
			if (x == COLS) {
				return 7;
			}
			else {
				return 8;
			}
		}
		break;
	case 7:
		if (x == COLS) {
			return 9;
		}
		else {
			return 10;
		}
		break;
	default:
		break;
	}
	return 0;
}

void Shop::itemInfo(int itemType)
{
	if (!itemType) { return; }
	sf::Sprite infoSprite(*m_infoTexture);
	int posX{ COLS + ((itemType + 1) % 2) };
	float posY;

	sf::String typeOfTowerText, description;
	switch (itemType)
	{
	default:
		return;
	case 1:
	case 2:
		posY = 1;
		typeOfTowerText = "  Shooting tower";
		description = "  Damage: " + std::to_string((int)(TOWERS_DAMAGE[itemType]) * 60) + "/sec";
		break;
	case 3:
	case 4:
		posY = 2.5f;
		typeOfTowerText = "  Shooting tower";
		description = "  Damage: " + std::to_string((int)(TOWERS_DAMAGE[itemType]) * 60) + "/sec";
		if (itemType == 4) description += "\nAttacks 3 enemies";
		break;
	case 5:
	case 6:
		posY = 4;
		typeOfTowerText = "  Shooting tower";
		description = "  Damage: " + std::to_string((int)(TOWERS_DAMAGE[itemType]) * 60) + "/sec";
		break;
	case 7:
		posY = 5.5f;
		typeOfTowerText = "\tSupport tower";
		description = "Increases damage\nof nearby towers";
		break;
	case 8:
		posY = 5.5f;
		typeOfTowerText = "\tSupport tower";
		description = "Increases range\nof nearby towers";
		break;
	case 9:
		posY = 7;
		typeOfTowerText = "\t\t\t\tZone";
		description = "\t\t Slows down\n\t\t\tenemies";
		break;
	case 10:
		posY = 7;
		typeOfTowerText = "\t\t\t\tZone";
		description = "    Stops enemies";
		break;
	}

	// рисуем окно
	infoSprite.setPosition(posX * W - W * 3, posY * W - W * 0.6f);
	(*window).draw(infoSprite);

	// рисуем текст
	sf::Text infoText(typeOfTowerText + "\n" + description, *m_font1, 30);
	infoText.setFillColor(sf::Color::Black);
	infoText.setPosition(infoSprite.getPosition().x + 5, infoSprite.getPosition().y + 5);
	(*window).draw(infoText);
}