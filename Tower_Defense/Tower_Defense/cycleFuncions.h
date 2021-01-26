#pragma once

class EnemiesWave;
class Field;

// ���������� static ����������
void setToDefault();

// ���������� �����, ����� ��� ���������� ������ �����
void resetTimeToSpawn();

// ������� ���� ��������� ���-�� � ������������ ���������� �������

// ������� ����. �����
void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field);
// ������� ����� �������
void waveBreakCycle(EnemiesWave &enemiesWave, bool &endOfGame, bool &endOfWave);