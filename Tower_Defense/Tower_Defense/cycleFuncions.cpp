#include "cycleFuncions.h"

#include <thread>

// перерыв между спавном противника?
static bool breakEnemy{ 0 };
// переменные для измерения времени между спавном следующего монстра
static std::chrono::time_point<std::chrono::steady_clock> startNextEnemy;
static std::chrono::time_point<std::chrono::steady_clock> endNextEnemy;

void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field)
{
	// спавн след противника
	if (!breakEnemy) {
		enemiesWave.spawnNextEnemy(field.getStartPos());
		startNextEnemy = std::chrono::high_resolution_clock::now();
		breakEnemy = 1;
	}
	// закончился ли перерыв между спавном врага?
	if (breakEnemy) {
		endNextEnemy = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakEnemyTime{ endNextEnemy - startNextEnemy };
		// если прошло x сек, выпускаем след врага
		if (breakEnemyTime.count() > 1) {
			breakEnemy = 0;
		}
	}
}

// пазуа емжду выстрелами башен
static bool breakShoot{ 0 };
// переменные для измерения времени между выстрелами башен
static std::chrono::time_point<std::chrono::steady_clock> startShoot;
static std::chrono::time_point<std::chrono::steady_clock> endShoot;

void towerShootCycle(TowersControl &towerControl, Field &field, Missiles &missiles, bool &drawMissiles)
{
	// башни стреляют
	if (!breakShoot) {
		towerControl.towersShoot(field, missiles);
		startShoot = std::chrono::high_resolution_clock::now();
		breakShoot = 1;
	}
	// закончился ли перерыв между выстрелами?
	if (breakShoot) {
		endShoot = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakShootTime{ endShoot - startShoot };
		// если прошло x сек, стреляем
		if (breakShootTime.count() > 0.5) {
			drawMissiles = 1;
			breakShoot = 0;
		}
	}
}

// пауза между движением монстров
static bool enemiesMove{ 0 };
// переменные для измерения времени между движением монстра
static std::chrono::time_point<std::chrono::steady_clock> startMoveEnemy;
static std::chrono::time_point<std::chrono::steady_clock> endMoveEnemy;

void enemyMoveCycle(EnemiesWave &enemiesWave, bool &endOfGame)
{
	// движение врага
	if (!enemiesMove) {
		// если вернет 1, то игрок проиграл
		endOfGame = enemiesWave.moveAllEnemies();
		startMoveEnemy = std::chrono::high_resolution_clock::now();
		enemiesMove = 1;
	}
	// ждем 1/60 секунды
	if (enemiesMove) {
		endMoveEnemy = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> breakEnemyTime{ endMoveEnemy - startMoveEnemy };
		// враг движется каждую x-ую секунды
		if (breakEnemyTime.count() > 1.f / 500) {
			enemiesMove = 0;
		}
	}
}

// перерыв между волнами?
static bool _break{ 0 };
// переменные для измерения времени между волнами
static std::chrono::time_point<std::chrono::steady_clock> startWave;
static std::chrono::time_point<std::chrono::steady_clock> endWave;

void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave)
{
	// если волна закончилась, запускаем таймер для перерыва
	if (!_break) {
		// если игрок прошел 5 уровень, игра заканчивается
		if (enemiesWave.getLevel() == 5) {
			result = 1;
			endOfGame = 1;
		}
		startWave = std::chrono::high_resolution_clock::now();
		_break = 1;
	}
	// если перерыв
	if (_break) {
		endWave = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakTime{ endWave - startWave };
		// если прошло x сек, начинаем следующую волну
		if (breakTime.count() > 1) {
			enemiesWave.nextWave();
			endOfWave = 0;
			_break = 0;
		}
	}
}

// рисовать снаряды?
static bool shooting{ 0 };
// переменные для измерения времени между отрисовками снарядов
static std::chrono::time_point<std::chrono::steady_clock> startShooting;
static std::chrono::time_point<std::chrono::steady_clock> endShooting;

void missileDrawCycle(Missiles & missiles, sf::RenderWindow & window, bool & drawMissiles)
{
	if (!shooting) {
		startShooting = std::chrono::high_resolution_clock::now();
		shooting = 1;
	}
	if (shooting) {
		missiles.drawMissiles(window);
		endShooting = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timeShooting{ endShooting - startShooting };
		// рисуем снаряды x секунд
		if (timeShooting.count() > 0.5) {
			missiles.deleteMissiles();
			shooting = 0;
			drawMissiles = 0;
		}
	}
}