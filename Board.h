#pragma once
#include "Ball.h"
#include "Bar.h"
#include "Block.h"
#include "Barrier.h"
#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <vector>
#include "Item.h"
using namespace std;
class Board
{
public:
    void Draw(int, int, HANDLE); // Hàm vẽ sàn đấu
    void Reset(Bar&, Ball&, vector<Block>&, vector<Barrier>&, bool&, int&, int, int, HANDLE,int item_index); // Hàm reset game mỗi khi không hứng được quả bóng
	void Run(Bar&, Ball&, vector<Block>&, vector<Barrier>&, bool&, int&, int, int, HANDLE, int, vector<string>& his); // Hàm hoạt động của game
	vector<clock_t> SaveGame(Ball ball, Bar bar, vector<Block> block, int barr_index, Item item, int score, clock_t timeStart, clock_t timeItem, int _height, HANDLE _consoleHandle, int itemIndex, bool checkItem);
	void LoadGame(Ball& ball, Bar& bar, vector<Block>& block, vector<Barrier>& barr, Item& item, int& barr_index, int& score, clock_t& time, int& _height, HANDLE& _consoleHandle, int& itemIndex, bool& checkItem, clock_t& itemStart);
    void PauseGame(HANDLE t);
	void writeHis(vector<string>& his, bool check, int score, int time);
	vector<string> readHis();
	void showHis(vector<string> his, int _width, int _height, HANDLE _consoleHandle);
	bool checkWin(vector<Block> b);
    Board();
    ~Board();
};

