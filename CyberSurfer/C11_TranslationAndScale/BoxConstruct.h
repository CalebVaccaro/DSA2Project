#pragma once
#include "Definitions.h"
#include "BoxRow.h"
#include <iostream>
#include <array>
using namespace std;
// 11 x
// 8 y

class BoxConstruct {
public:
	int yRowIndex = 1;
	int xRowIndex = 1;
	int yMax = 8;
	int xMax = 11;
	int amountOfBoxes = 0;
	std::vector<BoxRow*> constructRows;

	// Box Draw Information
	std::array<int, 11> row1 = { 0,0,0,1,1,0,1,1,0,0,0 };
	std::array<int, 11> row2 = { 1,0,1,0,0,0,0,0,1,0,1 };
	std::array<int, 11> row3 = { 1,0,1,1,1,1,1,1,1,0,1 };
	std::array<int, 11> row4 = { 1,1,1,1,1,1,1,1,1,1,1 };
	std::array<int, 11> row5 = { 0,1,1,0,1,1,1,0,1,1,0 };
	std::array<int, 11> row6 = { 0,0,1,1,1,1,1,1,1,0,0 };
	std::array<int, 11> row7 = { 0,0,0,1,0,0,0,1,0,0,0 };
	std::array<int, 11> row8 = { 0,0,1,0,0,0,0,0,1,0,0 };

	// Create a Row of Mesh Objects
	void CreateRowConstructs();
private:
};