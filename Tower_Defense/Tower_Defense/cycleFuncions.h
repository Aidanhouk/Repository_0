#pragma once

class EnemiesWave;
class Field;

// ������� ���� ��������� ���-�� � ������������ ���������� �������

// ������� ����. �����
void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field);
// ������� ����� �������
void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave);