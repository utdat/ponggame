#ifndef Puck_h
#define Puck_h

#include <iostream>
using namespace std;

class Puck {
private:
	float x, y;			//toa do vi tri
	float dx, dy;		//dx: huong di chuyen sang ngang, dy: duong di chuyen theo chieu doc
	float speed;		//toc do di chuyen
	int size;			//kich thuoc cua puck (ban kinh)
public:
	Puck();
	Puck(float x, float y, float dx, float dy);
	~Puck();

	float getX();
	void setX(float x);

	float getY();
	void setY(float y);

	float getDx();
	void setDx(float dx);

	float getDy();
	void setDy(float dy);

	float getSpeed();
	void setSpeed(float speed);

	int getSize();
	void setSize(int size);
};
#endif

