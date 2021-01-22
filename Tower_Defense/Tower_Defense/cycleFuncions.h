#pragma once

#include "enemiesWave.h"
#include "field.h"
#include "towersControl.h"
#include <SFML/Graphics.hpp>

// ������� ���� ��������� ���-�� � ������������ ���������� �������

// ������� ����. �����
void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field);
// ������� ����� �������
void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave);