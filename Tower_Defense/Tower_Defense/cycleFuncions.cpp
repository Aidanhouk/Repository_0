#include "cycleFuncions.h"

#include <thread>

// ������� ����� ������� ����������?
static bool breakEnemy{ 0 };
// ���������� ��� ��������� ������� ����� ������� ���������� �������
static std::chrono::time_point<std::chrono::steady_clock> startNextEnemy;
static std::chrono::time_point<std::chrono::steady_clock> endNextEnemy;

void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field)
{
	// ����� ���� ����������
	if (!breakEnemy) {
		enemiesWave.spawnNextEnemy(field.getStartPos());
		startNextEnemy = std::chrono::high_resolution_clock::now();
		breakEnemy = 1;
	}
	// ���������� �� ������� ����� ������� �����?
	if (breakEnemy) {
		endNextEnemy = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakEnemyTime{ endNextEnemy - startNextEnemy };
		// ���� ������ x ���, ��������� ���� �����
		if (breakEnemyTime.count() > 1) {
			breakEnemy = 0;
		}
	}
}

// ����� ����� ���������� �����
static bool breakShoot{ 0 };
// ���������� ��� ��������� ������� ����� ���������� �����
static std::chrono::time_point<std::chrono::steady_clock> startShoot;
static std::chrono::time_point<std::chrono::steady_clock> endShoot;

void towerShootCycle(sf::RenderWindow & window, TowersControl &towerControl, Field &field, Missiles &missiles)
{
	// ����� ��������
	if (!breakShoot) {
		// ������� ������ ��������
		missiles.deleteMissiles();
		// ��������� �����
		towerControl.towersShoot(field, missiles);
		startShoot = std::chrono::high_resolution_clock::now();
		breakShoot = 1;
	}
	// ���������� �� ������� ����� ����������?
	if (breakShoot) {
		// ������ ��������
		missiles.drawMissiles(window);
		endShoot = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakShootTime{ endShoot - startShoot };
		// ���� ������ x ���, ��������
		if (breakShootTime.count() > 0.5) {
			breakShoot = 0;
		}
	}
}

// ����� ����� ��������� ��������
static bool enemiesMove{ 0 };
// ���������� ��� ��������� ������� ����� ��������� �������
static std::chrono::time_point<std::chrono::steady_clock> startMoveEnemy;
static std::chrono::time_point<std::chrono::steady_clock> endMoveEnemy;

void enemyMoveCycle(EnemiesWave &enemiesWave, bool &endOfGame)
{
	// �������� �����
	if (!enemiesMove) {
		// ���� ������ 1, �� ����� ��������
		endOfGame = enemiesWave.moveAllEnemies();
		startMoveEnemy = std::chrono::high_resolution_clock::now();
		enemiesMove = 1;
	}
	if (enemiesMove) {
		endMoveEnemy = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> breakEnemyTime{ endMoveEnemy - startMoveEnemy };
		// ���� �������� ������ x-�� �������
		if (breakEnemyTime.count() > 1.f / 500) {
			enemiesMove = 0;
		}
	}
}

// ������� ����� �������?
static bool _break{ 0 };
// ���������� ��� ��������� ������� ����� �������
static std::chrono::time_point<std::chrono::steady_clock> startWave;
static std::chrono::time_point<std::chrono::steady_clock> endWave;

void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave)
{
	// ���� ����� �����������, ��������� ������ ��� ��������
	if (!_break) {
		// ���� ����� ������ 5 �������, ���� �������������
		if (enemiesWave.getLevel() == 5) {
			result = 1;
			endOfGame = 1;
		}
		startWave = std::chrono::high_resolution_clock::now();
		_break = 1;
	}
	// ���� �������
	if (_break) {
		endWave = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakTime{ endWave - startWave };
		// ���� ������ x ���, �������� ��������� �����
		if (breakTime.count() > 1) {
			enemiesWave.nextWave();
			endOfWave = 0;
			_break = 0;
		}
	}
}