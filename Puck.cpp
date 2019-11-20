#include "Puck.h"

Puck::Puck() {};
Puck::Puck(float x, float y, float dx, float dy) {};
Puck::~Puck() {};

float Puck::getX() {			//tra ve toa do x cua puck
	return this->x;
}
void Puck::setX(float x) {		//Thiet lap toa do x cua puck
	this->x = x;
}

float Puck::getY() {			//tra ve toa do x cua puck
	return this->y;
}
void Puck::setY(float y) {		//Thiet lap toa do x cua puck
	this->y = y;
}

float Puck::getDx() {			//tra ve dx cua puck
	return this->dx;
}
void Puck::setDx(float dx) {	//Thiet lap huong dx cua puck
	this->dx = dx;
}

float Puck::getDy() {			//tra ve dy cua puck
	return this->dy;
}
void Puck::setDy(float dy) {	//Thiet lap huong dy cua puck
	this->dy = dy;
}

float Puck::getSpeed() {		//tra ve toc do cua puck
	return this->speed;
}
void Puck::setSpeed(float speed) {	//Thiet lap toc do cua puck
	this->speed = speed;
}

int Puck::getSize() {			//tra ve kich thuoc cua puck
	return this->size;
}
void Puck::setSize(int size) {	//Thiet lap kich thuoc cua puck
	this->size = size;
}