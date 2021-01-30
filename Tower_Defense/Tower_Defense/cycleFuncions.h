#pragma once

class EnemiesWave;

// сбрасывает static переменные
void setToDefault();

// сбрасывает врем€, нужно дл€ корректной работы паузы
void resetTimeToSpawn();

// функции ниже выполн€ют что-то в определенном промежутке времени

// спавнит след. врага
void spawnNextEnemyCycle(EnemiesWave &enemiesWave);
// перерыв между волнами
void waveBreakCycle(EnemiesWave &enemiesWave, bool &endOfGame, bool &endOfWave);