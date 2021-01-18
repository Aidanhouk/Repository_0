#pragma once

#include "enemiesWave.h"
#include "field.h"
#include "towersControl.h"
#include <SFML/Graphics.hpp>

// ��� ������� ��������� ���-�� � ������������ ���������� �������
// ������� �����
void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field);
// ����� ��������
void towerShootCycle(sf::RenderWindow & window, TowersControl &towerControl, Field &field, Missiles &missiles);
// ���� ���������
void enemyMoveCycle(EnemiesWave &enemiesWave, bool &endOfGame);
// ������� ����� �������
void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave);