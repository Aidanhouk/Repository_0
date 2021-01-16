#pragma once

// ширина клетки поля
const int W{ 80 };

// кол-во строк
const int ROWS{ 9 };

// кол-во столбцов
const int COLS{ 9 };

// далее индекс массива = типу противника/башни

// кол-во hp у противников
const int ENEMIES_HP[5]{ 0,20,60,100,200 };

// кол-во монет, падающих с противников
const int ENEMIES_COINS[5]{ 0,1,3,5,0 };

// стоимости башен
const int TOWERS_PRICE[4]{ 0,10,25,50 };

// урон башен 
const int TOWERS_DAMAGE[4]{ 0,5,15,25 };