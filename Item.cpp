#include "Item.h"



Item::Item()
{
	this->x = 2 + rand() % 42;
	this->y = 5 + rand() % 22;
	this->type = rand() % 2;
	this->isExict = false;
	//for (int i = 0; i < blocks.size(); i++) {
	//	//Dieu kien trung = dk va cham.
	//}
}


Item::~Item()
{
	this->isExict = false;
}

void Item::setX(int x) {
	this->x = x;
}
int Item::getX() {
	return this->x;
}

void Item::setY(int y) {
	this->y = y;
}
int Item::getY() {
	return this->y;
}

void Item::setType(int type) {
	this->type = type;
}
int Item::getType() {
	return this->type;
}

void Item::setIsExict(bool type) {
	this->isExict = type;
}
bool Item::getIsExict() {
	return this->isExict;
}
void Item::renewItem() {
	this->x = 2 + rand() % 42;
	do { this->y = 5 + rand() % 22; } while (this->y == 7);
	this->type = rand() % 2;
	this->isExict = false;
}

bool Item::checkEat(Ball _b) {
	if (_b.GetX() >= this->x && _b.GetX() <= this->x + 1) {
		if (_b.GetY() > this->y - 2 && _b.GetY() <this->y + 2) {
			//_b.SetY(this->y - _b.GetVy() / abs(_b.GetVy()));
			//_b.SetVy(_b.GetVy() * -1); // Set vận tốc Vy của bóng cho đi ngược lại
			return true;
		}
	}

	/*if (_b.GetY() < _block[i].GetY() + 1 && _b.GetY() > _block[i].GetY() - 1) {
		if (_b.GetX() > _block[i].GetX() - _block[i].GetSize() - 1 && _b.GetX() < _block[i].GetX() - _block[i].GetSize() + 1) {
			_b.SetVx(_b.GetVx() * -1);
			_b.SetX(_block[i].GetX() - _block[i].GetSize() - 1);
			y_Score += 10;
			_block[i].setIsCrash(true);
			count_block++;
		}
		if (_b.GetX() < _block[i].GetX() + _block[i].GetSize() + 1 && _b.GetX() > _block[i].GetX() + _block[i].GetSize() - 1) {
			_b.SetVx(_b.GetVx() * -1);
			_b.SetX(_block[i].GetX() + _block[i].GetSize() + 1);
			y_Score += 10;
			_block[i].setIsCrash(true);
			count_block++;
		}
	}*/
	return false;
}

void Item::Draw(clock_t &itemStart, HANDLE _consoleHandle) { //Vẽ
	this->isExict = true;
	if (this->isExict) {
		COORD _pos;
		_pos.X = this->x;
		_pos.Y = this->y;

		SetConsoleCursorPosition(_consoleHandle, _pos); // dua con tro toi vi tri moi cua bong
		SetConsoleTextAttribute(_consoleHandle, 12);
		cout << "??";
		_pos.X = this->x;
		_pos.Y = this->y+1;

		SetConsoleCursorPosition(_consoleHandle, _pos); // dua con tro toi vi tri moi cua bong
		cout << "??";
		itemStart = clock();
		SetConsoleTextAttribute(_consoleHandle, 15);
	}
}
void Item::EffectOfItem(int &score) { //Tác động của item tới trò chơi
	switch (this->type) {
	case 0: //Nhan 2 diem
		score *= 2;
		break;
	case 1:
		score /= 2;
		break;
	case 2:
		break;
	}
}
bool Item::checkTime(clock_t itemStart, HANDLE _consoleHandle) {
	clock_t currentTime = clock();
	if ((currentTime - itemStart) / CLOCKS_PER_SEC == 10) {		//qua 10s thi false
		COORD _pos;
		_pos.X = this->x;
		_pos.Y = this->y;

		SetConsoleCursorPosition(_consoleHandle, _pos); // dua con tro toi vi tri moi cua bong
		SetConsoleTextAttribute(_consoleHandle, 12);
		cout << "  ";
		_pos.X = this->x;
		_pos.Y = this->y+1;
		SetConsoleCursorPosition(_consoleHandle, _pos);
		cout << "  ";
		SetConsoleTextAttribute(_consoleHandle, 15);
		this->isExict = false;
		return false;
	}
	return true;
}
