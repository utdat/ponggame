#include "Block.h"

Block::Block(int _x, int _y, int _size){
    this->x = float(_x);
    this->y = float(_y);
    this->size = _size;
    this->isCrash = false;
}

void  Block::SetX(float _x) {
    this->x = _x;
}
float Block::GetX() {
    return this->x;
}

void  Block::SetY(float _y) {
    this->y = _y;
}
float Block::GetY() {
    return this->y;
}

void Block::SetSize(int _size){
    this->size = _size;
}
int Block::GetSize(){
    return this->size;
}

void Block::setIsCrash(bool check){
    this->isCrash = check;
}
bool Block::getIsCrash(){
    return this->isCrash;
}

void Block::Draw(HANDLE _consoleHandle, int color){
    COORD _pos; // Toa do _pos
    
    _pos.X = int(this->x) - this->size;
    _pos.Y = int(this->y);

    SetConsoleCursorPosition(_consoleHandle, _pos);
    
    if (this->isCrash){
        for (int i = -this->size; i < this->size; i++)
            cout << " ";
    }
    else {
        SetConsoleTextAttribute(_consoleHandle, color);
        for (int i = -this->size; i < this->size; i++)
            cout << static_cast<char>(219);
        SetConsoleTextAttribute(_consoleHandle, 15);
    }
}
