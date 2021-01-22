#pragma once

// ширина клетки пол€ в пиксел€х, Ќ≈ »«ћ≈Ќя“№
const int W{ 80 };

// остальные параметры можно измен€ть дл€ настройки размера пол€ и баланса

// кол-во строк
const int ROWS{ 9 };
// кол-во столбцов
const int COLS{ 9 };

// стартовые деньги
const int START_MONEY{ 30 };

// далее индекс массива равен типу противника/башни

// кол-во типов противников минус 1
const int ENEMIES_COUNT{ 5 };
// кол-во hp у противников
const int ENEMIES_HP[ENEMIES_COUNT]{ 0,120,360,600,1200 };
// кол-во монет, падающих с противников
const int ENEMIES_COINS[ENEMIES_COUNT]{ 0,1,3,5,10 };
// скорость противников
const double ENEMIES_SPEED[ENEMIES_COUNT]{ 0,2,2.4,1.8,1.8 };

// кол-во типов башен минус 1
const int TOWERS_COUNT{ 7 };
// стоимости башен
const int TOWERS_PRICE[TOWERS_COUNT]{ 0,10,30,50,80,120,150 };
// урон башен каждый кадр
const int TOWERS_DAMAGE[TOWERS_COUNT]{ 0,1,3,5,8,12,15 };