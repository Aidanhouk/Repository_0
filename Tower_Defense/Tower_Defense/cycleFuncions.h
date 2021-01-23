#pragma once

#include <SFML/Graphics.hpp>

class EnemiesWave;
class Field;

// функции ниже выполняют что-то в определенном промежутке времени

// спавнит след. врага
void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field);
// перерыв между волнами
void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave);