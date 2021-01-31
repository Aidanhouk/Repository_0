#include "enemiesWave.h"

#include "enemy.h"

void EnemiesWave::nextWave()
{
	// если уже макс уровень волны
	if (m_waveLevel != m_maxWave) {
		++m_waveLevel;
		// в зависимости от уровня волны в ней будут разные противники в разном кол-ве
		switch (m_waveLevel)
		{
		case 1:
			m_enemiesLeft = 15;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(1, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(2, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 2:
			m_enemiesLeft = 25;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(1, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 15; ++i) {
				Enemy *enemy = new Enemy(2, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 3:
			m_enemiesLeft = 10;
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(2, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(3, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 4:
			m_enemiesLeft = 20;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(2, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(3, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 5:
			m_enemiesLeft = 15;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(3, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(4, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 6:
			m_enemiesLeft = 15;
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(3, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(4, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 7:
			m_enemiesLeft = 5;
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(5, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 8:
			m_enemiesLeft = 15;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(4, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(5, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 9:
			m_enemiesLeft = 10;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(5, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 10:
			m_enemiesLeft = 15;
			for (int i = 0; i < 15; ++i) {
				Enemy *enemy = new Enemy(5, m_waveLevel, m_enemiesTextures, this);
				m_enemiesList.push_back(enemy);
			}
			break;
		default:
			break;
		}
	}
}
