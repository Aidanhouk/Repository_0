#pragma once

#include <SFML/Graphics.hpp>

class EnemiesWave;
class Field;

// ������� ���� ��������� ���-�� � ������������ ���������� �������

// ������� ����. �����
void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field);
// ������� ����� �������
void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave);