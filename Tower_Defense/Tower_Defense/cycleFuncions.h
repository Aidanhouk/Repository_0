#pragma once

#include "enemiesWave.h"
#include "field.h"
#include "towersControl.h"
#include <SFML/Graphics.hpp>

// эти функции выполняют что-то в определенном промежутке времени
// спавнит враго
void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field);
// башни стреляют
void towerShootCycle(sf::RenderWindow & window, TowersControl &towerControl, Field &field, Missiles &missiles);
// враг двигается
void enemyMoveCycle(EnemiesWave &enemiesWave, bool &endOfGame);
// перерыв между волнами
void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave);