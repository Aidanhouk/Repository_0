#pragma once

#include <SFML/Graphics.hpp>

class Field;

// ����������� ����
extern int n;
// ��� ������ ���� (1 - player vs player, 2 - player vs AI, 3 - AI vs AI)
extern int _WhoVsWho;
// ��������� ����
extern int gameResult;
// ���� ����
extern Field * field;
// ���� ���� 
extern sf::RenderWindow *window;