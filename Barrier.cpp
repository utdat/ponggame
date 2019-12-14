#include "Barrier.h"

Barrier::Barrier(int _x, int _y, int _size){
    this->x = float(_x);
    this->y = float(_y);
    this->size = _size;
    this->isExist = false;
}

void  Barrier::SetX(float _x) {
    this->x = _x;
}
float Barrier::GetX() {
    return this->x;
}

void  Barrier::SetY(float _y) {
    this->y = _y;
}
float Barrier::GetY() {
    return this->y;
}

void Barrier::SetSize(int _size){
    this->size = _size;
}
int Barrier::GetSize(){
    return this->size;
}

void Barrier::setIsExist(bool check){
    this->isExist = check;
}
bool Barrier::getIsExist(){
    return this->isExist;
}

void Barrier::Draw(HANDLE _consoleHandle){
    COORD _pos; // Toa do _pos
    
    _pos.X = int(this->x) - this->size;
    _pos.Y = int(this->y);

    SetConsoleCursorPosition(_consoleHandle, _pos);
    
    if (this->isExist){
        SetConsoleTextAttribute(_consoleHandle, 12);
        for (int i = -this->size; i < this->size; i++)
            cout << static_cast<char>(88);
        SetConsoleTextAttribute(_consoleHandle, 15);
    }
}
