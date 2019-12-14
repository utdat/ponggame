// 1612759.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"Board.h"
#include"Ball.h"
#include"Bar.h"
#include<time.h>
#include <vector>
#include"Item.h"

int _width = 51;
int _height = 30;
float _maxSpeed = 1.8f;

int main()
{
	HANDLE _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	srand(unsigned int(time(NULL)));

	// Hiển thị màn hình console vừa với trò chơi
	SMALL_RECT DisplayArea = { 0, 0, _width, _height + 3 };

	SetConsoleWindowInfo(_consoleHandle, TRUE, &DisplayArea);
	//

	// Ẩn con trỏ
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = false;

	SetConsoleCursorInfo(_consoleHandle, &ConCurInf);
	//

	Board _board;

	_board.Draw(_width, _height, _consoleHandle);// Vẽ sàn đấu

	Bar _you(_width / 2, _height - 2, 4); // Khởi tạo thanh trượt của người chơi
	Ball _b(_width / 2 - 1, _height / 2); // Khởi tạo quả bóng

	vector<string> his;
    
    vector<Block> _block;
    for (int i = 0; i < 12; i++){
		if (i < 6)
		{
			Block block(8 * i + 5, 1, 4);
			_block.push_back(block);
		}
		else
		{
			Block block(8 * (i % 6) + 5, 2, 4);
			_block.push_back(block);
		}
    }
    
    vector<Barrier> _barrier;
    for (int i = 0; i < 6; i++){
        Barrier barrier(8 * i + 5, 7, 4);
        _barrier.push_back(barrier);
    }

	int y_Score = 0; // điểm ban đầu
	bool _start = false; // Biến kiểm tra điều kiện để bắt đầu trò chơi

	// Set vận tốc Vx, Vy của quả bóng để lúc bắt đầu luôn đi về phía người chơi
	_b.SetVx(float(rand() % 3) - 1.5f);
	_b.SetVy(1);

	//_comp.SetVx(0);

	_board.Run(_you, _b, _block, _barrier, _start, y_Score, _width, _height, _consoleHandle, _maxSpeed, his);//Hàm hoạt động của trò chơi
}
