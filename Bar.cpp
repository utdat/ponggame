#include "Bar.h"

Bar::Bar(int _x, int _y, int _size) {
	this->x = float(_x);
	this->y = float(_y);
	this->size = _size;
	this->ox = float(_x);
	this->oy = float(_y);
}

void  Bar::SetX(float _x) {
	this->x = _x;
}
float Bar::GetX() {
	return this->x;
}

void  Bar::SetY(float _y) {
	this->y = _y;
}
float Bar::GetY() {
	return this->y;
}

void  Bar::SetOx(float _ox) {
	this->ox = _ox;
}
float Bar::GetOx() {
	return this->ox;
}

void  Bar::SetOy(float _oy) {
	this->oy = _oy;
}
float Bar::GetOy() {
	return this->oy;
}

void  Bar::SetVx(float _vx) {
	this->vx = _vx;
}
float Bar::GetVx() {
	return this->vx;
}

void Bar::SetSize(int _size) {
	this->size = _size;
}
int Bar::GetSize() {
	return this->size;
}

void Bar::Draw(HANDLE _consoleHandle) {
	// Input: _consoleHandle(con trỏ đại diện cho màn hình console)
	// Output: Không
	// Chức năng: Vẽ thanh trượt

	COORD _pos; // toa do _pos

	_pos.X = int(this->ox) - this->size;
	_pos.Y = int(this->oy);

	SetConsoleCursorPosition(_consoleHandle, _pos); // dua con tro toi vi tri cu cua thanh truot

	for (int i = -this->size; i < this->size; i++) { // xoa thanh truot tai vi tri cu
		cout << ' ';
	}

	_pos.X = int(this->x) - this->size;
	_pos.Y = int(this->y);

	SetConsoleCursorPosition(_consoleHandle, _pos); // dua con tro toi vi tri moi cua thanh truot
	SetConsoleTextAttribute(_consoleHandle, 10); // set mau xanh

	for (int i = -this->size; i < this->size; i++) { // ve thanh truot tai vi tri moi
		cout << static_cast<char>(219);
	}

	SetConsoleTextAttribute(_consoleHandle, 15); // set lai mau binh thuong

	this->ox = this->x;
	this->oy = this->y;
}
