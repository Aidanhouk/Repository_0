#include "enemy.h"

#include "globals.h"
#include "roadCell.h"
#include "blockOnField.h"
#include "enemiesWave.h"
#include "field.h"

Enemy::Enemy(int type, int currentWaveLevel, sf::Texture * enemyTextures[ENEMIES_COUNT], EnemiesWave * wave)
	: m_type{ type }, m_wave{ wave },
	m_waveLevel{ currentWaveLevel },
	m_hp{ ENEMIES_HP[type] * (1 + 0.3 * currentWaveLevel) },
	m_coins{ ENEMIES_COINS[type] },
	m_enemyTexture{ enemyTextures[type] },
	m_speed{ ENEMIES_SPEED[type] * (1 + 2 * gameSpeed) },
	m_dmg{ ENEMIES_DAMAGE[type] * (1 + 2 * gameSpeed) }
{}

void Enemy::setDirection(RoadCell * currentPosition)
{
	// вычислим разницу между координатами текущей и след ячейки
	std::pair<int, int> coordCurrentPos{ currentPosition->getCoordinates() };
	std::pair<int, int> coordNextPos{ currentPosition->getNextCell()->getCoordinates() };
	std::pair<int, int> coordDifference{ coordNextPos.first - coordCurrentPos.first, coordNextPos.second - coordCurrentPos.second };
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
				m_speed = ENEMIES_SPEED[m_type] * (1 + 2 * gameSpeed) / 3;
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
			m_speed = ENEMIES_SPEED[m_type] * (1 + 2 * gameSpeed) / 3;
			m_distance += m_speed;
			return;
		}
	}
	m_speed = ENEMIES_SPEED[m_type] * (1 + 2 * gameSpeed);
	m_distance += m_speed;
}

bool Enemy::getDamage(int dmg)
{
	m_hp -= dmg;
	if (m_hp <= 0) {
		money += m_coins;
		// устанавливаем, что враг мертв
		m_isAlive = 0;
		m_isKilled = 1;
		// убираем врага с клетки
		m_position->removeEnemyFromCell(this);
		m_wave->reduceEnemiesLeft();
		return 1;
	}
	return 0;
}

void Enemy::changeSpeed()
{
	if (gameSpeed) {
		m_speed *= 3;
	}
	else {
		m_speed /= 3;
	}
}

void Enemy::changeDamage()
{
	if (gameSpeed) {
		m_dmg *= 3;
	}
	else {
		m_dmg /= 3;
	}
}

void Enemy::drawEnemy()
{
	sf::Sprite enemy;
	enemy.setTexture(*m_enemyTexture);
	switch (m_direction)
	{
	case 1:
		switch (m_type)
		{
		case 1:
		case 5:
			enemy.setPosition(W * m_position->getCoordinates().second, W * (m_position->getCoordinates().first + 1) - m_distance);
			enemy.rotate(-90);
			break;
		case 3:
		case 4:
			enemy.setPosition(W * m_position->getCoordinates().second, W * m_position->getCoordinates().first - m_distance);
			break;
		case 2:
			enemy.setPosition(W * m_position->getCoordinates().second, W * m_position->getCoordinates().first - m_distance);
			break;
		}
		break;
	case 2:
		enemy.setPosition(W * m_position->getCoordinates().second + m_distance, W * m_position->getCoordinates().first);
		break;
	case 3:
		switch (m_type)
		{
		case 1:
		case 5:
			enemy.setPosition(W * (m_position->getCoordinates().second + 1), W * m_position->getCoordinates().first + m_distance);
			enemy.rotate(90);
			break;
		case 3:
		case 4:
			enemy.setPosition(W * (m_position->getCoordinates().second + 1), W * (m_position->getCoordinates().first + 1) + m_distance);
			enemy.rotate(180);
			break;
		case 2:
			enemy.setPosition(W * m_position->getCoordinates().second, W * m_position->getCoordinates().first + m_distance);
			break;
		}
		break;
	case 4:
		enemy.setPosition(W * (m_position->getCoordinates().second + 1) - m_distance, W * (m_position->getCoordinates().first));
		enemy.scale(-1, 1);
		break;
	}
	(*window).draw(enemy);
}

void Enemy::drawHPBar()
{
	sf::RectangleShape hpBarRed(sf::Vector2f(W * 0.5, 4));
	hpBarRed.setFillColor(sf::Color::Red);
	sf::RectangleShape hpBarGreen(sf::Vector2f(W * 0.5 * ((float)m_hp / ENEMIES_HP[m_type] / (1 + 0.3 * m_waveLevel)), 4));
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
	(*window).draw(hpBarRed);
	(*window).draw(hpBarGreen);
}