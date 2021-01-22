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

// ������� ����� �������?
static bool _break{ 0 };
// ���������� ��� ��������� ������� ����� �������
static std::chrono::time_point<std::chrono::steady_clock> startWave;
static std::chrono::time_point<std::chrono::steady_clock> endWave;

void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave)
{
	// ���� ����� �����������, ��������� ������ ��� ��������
	if (!_break) {
		enemiesWave.cleanWave();
		// ���� ����� ������ ���� �������, ���� �������������
		if (enemiesWave.getLevel() == enemiesWave.getMaxLevel()) {
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