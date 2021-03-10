#pragma once
#include "Stack.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;
using namespace std;
class Maze
{
public:

	struct currentPosition {

		int x, y;

	}tempM, tempC;

	Stack mousePos;
	Stack catPos[10];
//functions
	Maze();
	void loadMaze(),
		displayMaze(int x, int y),
		showMouse(),
		hideMouse(),
		showCat(int catNum),
		hideCat(int catNum),
		positionCat(int catNum),
		gameOver(),
		mouseWins();
		
	bool isTopCat(int x, int y, int catNum),
		isTopMouse(int x, int y),
		moveMouse(),
		moveCat(int catNum),
		didCatEatMouse(int numCat);

//variables
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	int mazeBoard[30][70];
	int mX, mY;
	int cX[10], cY[10];
	int cherriesEaten;
};



