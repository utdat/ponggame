#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

class Bar
{
private:
	float x;
	float y;
	float ox;
	float oy;
	float vx;
	int size;
public:
	Bar(int, int, int); // Hàm khởi tạo

	// Get, Set
	void SetX(float); // Set tọa độ X của thanh trượt
	float GetX(); // Get tọa độ X của thanh trượt
	void SetY(float); // Set tọa y của thanh trượt
	float GetY(); // Get tọa độ y của thanh trượt
	void SetOx(float); // Set tọa độ x cũ của thanh trượt
	float GetOx(); // Get tọa độ x cũ của thanh trượt
	void SetOy(float); // Set tọa độ y cũ của thanh trượt
	float GetOy(); // Get tọa độ y cũ của thanh trượt
	void SetVx(float); // Set vận tốc theo ox của thanh trượt
	float GetVx(); // Get vận tốc theo ox của thanh trượt
	void SetSize(int); // Set size của thanh trượt
	int GetSize(); // Get size của thanh trượt

	void Draw(HANDLE); // Hàm vẽ thanh hứng
};

