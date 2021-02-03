#pragma once

#include <SFML/Graphics.hpp>

class Field;

// размерность поля
extern int n;
// кто против кого (1 - player vs player, 2 - player vs AI, 3 - AI vs AI)
extern int _WhoVsWho;
// результат игры
extern int gameResult;
// поле игры
extern Field * field;
// окно игры 
extern sf::RenderWindow *window;