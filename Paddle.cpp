#include "Paddle.h"

Paddle::Paddle() {};
Paddle::Paddle(float x, float y) {};
Paddle::~Paddle() {};

float Paddle::getX() {						//tra ve toa do x cua paddle
	return this->x;
}
void Paddle::setX(float x) {				//Thiet lap toa do x cua paddle
	this->x = x;
}

float Paddle::getY() {						//tra ve toa do y cua paddle
	return this->y;
}
void Paddle::setY(float y) {				//Thiet lap toa do y cua paddle
	this->y = y;
}

int Paddle::getW() {						//tra ve do rong cua paddle
	return this->w;
}
void Paddle::setW(int w) {					//Thiet lap do rong cua paddle
	this->w = w;
}

int Paddle::getH() {						//tra ve chieu cao cua paddle
	return this->h;
}
void Paddle::setH(int h) {					//Thiet lap chieu cao cua paddle
	this->h = h;
}
float Paddle::getSpeed() {					//tra ve toc do cua paddle
	return this->speed;
}
void Paddle::setSpeed(float x) {			//Thiet lap toc do cua paddle
	this->speed = x;
}