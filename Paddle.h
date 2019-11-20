#ifndef Paddle_h
#define Paddle_h

#include <iostream>
using namespace std;

class Paddle {
private:
	float x, y;			//gia tri vi tri
	int w, h;			//w: dong rong, h: chieu cao
	float speed;		//toc do di chuyen
public:
	Paddle();
	Paddle(float x, float y);
	~Paddle();

	float getX();
	void setX(float x);

	float getY();
	void setY(float y);

	int getW();
	void setW(int w);

	int getH();
	void setH(int h);

	float getSpeed();
	void setSpeed(float x);
};
#endif
