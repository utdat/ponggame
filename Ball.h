#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

class Ball
{
private:
	float x;
	float y;
	float ox; // vi tri x cu
	float oy; // vi tri y cu
	float vx; // van toc x
	float vy; // van toc y

public:
	Ball(int, int); // Hàm khởi tạo

	// Get, Set
	void SetX(float); // Set tọa độ x của quả bóng
	float GetX(); // Get tọa độ x của quả bóng
	void SetY(float); // set tọa độ y của quả bóng
	float GetY(); // Get tọa độ y của quả bóng
	void SetOx(float); // Set tọa độ x cũ của quả bóng
	float GetOx(); // Get tọa độ x cũ của quả bóng
	void SetOy(float); // Set tọa độ y cũ của quả bóng
	float GetOy(); // Get tọa độ y cũ của quả bóng
	void SetVx(float); // Set vận tốc theo Ox của quả bóng
	float GetVx(); // Get vận tốc theo Ox của quả bóng
	void SetVy(float); // Set vận tốc theo Oy của quả bóng
	float GetVy(); // Get vận tốc theo Oy của quả bóng

	void Draw(HANDLE); // Hàm vẽ quả bóng
};

