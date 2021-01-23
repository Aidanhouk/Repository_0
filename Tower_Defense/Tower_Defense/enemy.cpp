#include "enemy.h"

#include "roadCell.h"
#include "blockOnField.h"

Enemy::Enemy(int type, int level, sf::Texture * enemyTextures[ENEMIES_COUNT])
	: m_type{ type }, m_waveLevel{ level }, m_enemyTexture{ enemyTextures[type] },
	m_hp{ (int)(ENEMIES_HP[type] * (1 + 0.2 * level)) }, m_coins{ ENEMIES_COINS[type] },
	m_speed{ ENEMIES_SPEED[type] }, m_dmg{ (int)(ENEMIES_DAMAGE[type] * (1 + 0.2 * level)) }
{}

void Enemy::setDirection(RoadCell * currentPosition)
{
	// вычислим разницу между координатами текущей и след ячейки
	std::pair<int, int> coordCurrentPos{ currentPosition->getCoordinates() };
	std::pair<int, int> coordNextPos{ currentPosition->getNextCell()->getCoordinates() };
	std::pair<int, int> coordDifference{ coordNextPos.first - coordCurrentPos.first, coordNextPos.second - coordCurrentPos.second };
	// можно и не создавать доп переменные, но будет слишком много кода в одном выражении
	switch (coordDifference.first)
	{
	case -1:
		m_direction = 1;
		break;
	case 1:
		m_direction = 3;
		break;
	case 0:
		switch (coordDifference.second)
		{
		case -1:
			m_direction = 4;
			break;
		case 1:
			m_direction = 2;
			break;
		}
		break;
	}
}

void Enemy::changePosition()
{
	m_distance = 0;
	// удаляем с текущей клетки врага
	m_position->removeEnemyFromCell(this);
	// переходим на следующую ячейку
	m_position = m_position->getNextCell();
	// добавляем в нее текущего врага
	m_position->setEnemyOnCell(this);
}

void Enemy::enemyMoves()
{
	if (m_position->getNextCell()->getBlockOnCell()) {
		// замедление скорости, если враг идет по замедляющему блоку
		if (m_position->getNextCell()->getBlockOnCell()->getType() == 1) {
			if (m_distance >= (W >> 1)) {
				m_speed = ENEMIES_SPEED[m_type] / 3;
				m_distance += m_speed;
				return;
			}
		}
		// если след блок - останавливающий, то остановка движения + нанесение урона
		else {
			m_speed = 0;
			m_position->getNextCell()->getBlockOnCell()->getDamage(m_dmg);
			return;
		}
	}
	if (m_position->getBlockOnCell()) {
		// замедление скорости, если враг идет по замедляющему блоку
		if (m_distance < (W >> 1)) {
			m_speed = ENEMIES_SPEED[m_type] / 3;
			m_distance += m_speed;
			return;
		}
	}
	m_speed = ENEMIES_SPEED[m_type];
	m_distance += m_speed;
}

void Enemy::drawEnemy(sf::RenderWindow &window)
{
	sf::CircleShape enemy(30, m_type + 2);
	switch (m_direction)
	{
	case 1:
		enemy.setPosition(W * m_position->getCoordinates().second + 10, W * m_position->getCoordinates().first + 10 - m_distance);
		break;
	case 2:
		enemy.setPosition(W * m_position->getCoordinates().second + 10 + m_distance, W * m_position->getCoordinates().first + 10);
		break;
	case 3:
		enemy.setPosition(W * m_position->getCoordinates().second + 10, W * m_position->getCoordinates().first + 10 + m_distance);
		break;
	case 4:
		enemy.setPosition(W * m_position->getCoordinates().second + 10 - m_distance, W * m_position->getCoordinates().first + 10);
		break;
	}
	switch (m_type)
	{
	case 1:
		enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		enemy.setFillColor(sf::Color::Green);
		break;
	case 3:
		enemy.setFillColor(sf::Color::Cyan);
		break;
	case 4:
		enemy.setFillColor(sf::Color::Black);
		break;
	}
	window.draw(enemy);
}

void Enemy::drawHPBar(sf::RenderWindow & window)
{
	sf::RectangleShape hpBarRed(sf::Vector2f(W * 0.5, 4));
	hpBarRed.setFillColor(sf::Color::Red);
	sf::RectangleShape hpBarGreen(sf::Vector2f(W * 0.5 * ((float)m_hp / ENEMIES_HP[m_type] / (1 + 0.2 * m_waveLevel)), 4));
	hpBarGreen.setFillColor(sf::Color::Green);
	switch (m_direction)
	{
	case 1:
		hpBarRed.setPosition(W * m_position->getCoordinates().second + W * 0.25, W * m_position->getCoordinates().first + 10 - m_distance + W * 0.75);
		hpBarGreen.setPosition(W * m_position->getCoordinates().second + W * 0.25, W * m_position->getCoordinates().first + 10 - m_distance + W * 0.75);
		break;
	case 2:
		hpBarRed.setPosition(W * m_position->getCoordinates().second + m_distance + W * 0.25, W * m_position->getCoordinates().first + 10 + W * 0.75);
		hpBarGreen.setPosition(W * m_position->getCoordinates().second + m_distance + W * 0.25, W * m_position->getCoordinates().first + 10 + W * 0.75);
		break;
	case 3:
		hpBarRed.setPosition(W * m_position->getCoordinates().second + W * 0.25, W * m_position->getCoordinates().first + 10 + m_distance + W * 0.75);
		hpBarGreen.setPosition(W * m_position->getCoordinates().second + W * 0.25, W * m_position->getCoordinates().first + 10 + m_distance + W * 0.75);
		break;
	case 4:
		hpBarRed.setPosition(W * m_position->getCoordinates().second - m_distance + W * 0.25, W * m_position->getCoordinates().first + 10 + W * 0.75);
		hpBarGreen.setPosition(W * m_position->getCoordinates().second - m_distance + W * 0.25, W * m_position->getCoordinates().first + 10 + W * 0.75);
		break;
	}
	window.draw(hpBarRed);
	window.draw(hpBarGreen);
}

void Enemy::drawShot(sf::RenderWindow & window)
{
	sf::CircleShape wound(30, m_type + 2);
	switch (m_direction)
	{
	case 1:
		wound.setPosition(W * m_position->getCoordinates().second + 10, W * m_position->getCoordinates().first + 10 - m_distance);
		break;
	case 2:
		wound.setPosition(W * m_position->getCoordinates().second + 10 + m_distance, W * m_position->getCoordinates().first + 10);
		break;
	case 3:
		wound.setPosition(W * m_position->getCoordinates().second + 10, W * m_position->getCoordinates().first + 10 + m_distance);
		break;
	case 4:
		wound.setPosition(W * m_position->getCoordinates().second + 10 - m_distance, W * m_position->getCoordinates().first + 10);
		break;
	}
	wound.setFillColor(sf::Color::Red);
	window.draw(wound);
}