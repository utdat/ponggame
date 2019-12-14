#include "Ball.h"

Ball::Ball(int _x, int _y) {
	this->x = float(_x);
	this->y = float(_y);
	this->ox = float(_x);
	this->oy = float(_y);
	this->vx = 0;
	this->vy = 0;
}

void  Ball::SetX(float _x) {
	this->x = _x;
}
float Ball::GetX() {
	return this->x;
}

void  Ball::SetY(float _y) {
	this->y = _y;
}
float Ball::GetY() {
	return this->y;
}

void  Ball::SetOx(float _ox) {
	this->ox = _ox;
}
float Ball::GetOx() {
	return this->ox;
}

void  Ball::SetOy(float _oy) {
	this->oy = _oy;
}
float Ball::GetOy() {
	return this->oy;
}

void  Ball::SetVx(float _vx) {
	this->vx = _vx;
}
float Ball::GetVx() {
	return this->vx;
}

void  Ball::SetVy(float _vy) {
	this->vy = _vy;
}
float Ball::GetVy() {
	return this->vy;
}

void Ball::Draw(HANDLE _consoleHandle) {
	// Input: _consoleHandle(con trỏ đại diện cho màn hình console)
	// Output: Không
	// Chức năng: Vẽ quả bóng

	COORD _pos; // Toa do _pos

	_pos.X = int(this->ox);
	_pos.Y = int(this->oy);

	SetConsoleCursorPosition(_consoleHandle, _pos); // dua co tro toi vi tri cu cua bong

	cout << ' '; // xoa qua bong tai vi tri cu

	_pos.X = int(this->x);
	_pos.Y = int(this->y);

	SetConsoleCursorPosition(_consoleHandle, _pos); // dua con tro toi vi tri moi cua bong
	SetConsoleTextAttribute(_consoleHandle, 12); // set mau cua qua bong

	cout << 'o'; // ve qua bong tai vi tri moi

	SetConsoleTextAttribute(_consoleHandle, 15);

	this->ox = this->x;
	this->oy = this->y;
}