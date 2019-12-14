#pragma once
#include "Bar.h"
#include <time.h>
#include "Ball.h"
class Item
{
private:
	int x;
	int y;
	int type;
	bool isExict;
public:
	Item();
	~Item();
	void setX(int x);
	int getX();
	
	void setY(int y);
	int getY();

	void setType(int type);
	int getType();

	void setIsExict(bool type);
	bool getIsExict();

	void renewItem();
	bool checkEat(Ball ball);
	void Draw(clock_t &itemStart, HANDLE _consoleHandle);
	void EffectOfItem(int &score);
	bool checkTime(clock_t itemStart, HANDLE _consoleHandle);
};

