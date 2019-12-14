#ifndef Barrier_h
#define Barrier_h

#include <iostream>
#include<Windows.h>
using namespace std;

class Barrier {
private:
    float x;
    float y;
    int size;
    bool isExist;
    
public:
    Barrier(int, int,int);
    
    void SetX(float);
    float GetX();
    
    void SetY(float);
    float GetY();
    
    void SetSize(int);
    int GetSize();
    
    void setIsExist(bool);
    bool getIsExist();
    
    void Draw(HANDLE);
    
};
#endif 
