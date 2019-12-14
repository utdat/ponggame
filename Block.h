#ifndef Block_h
#define Block_h

#include <iostream>
#include<Windows.h>
using namespace std;

class Block {
private:
    float x;
    float y;
    int size;
    bool isCrash;
    
public:
    Block(int, int, int);
    
    void SetX(float);
    float GetX();
    
    void SetY(float);
    float GetY();
    
    void SetSize(int);
    int GetSize();
    
    void setIsCrash(bool);
    bool getIsCrash();
    
    void Draw(HANDLE, int);
    
};

#endif
