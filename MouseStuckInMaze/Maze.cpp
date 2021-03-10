#include "Maze.h"


void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

Maze::Maze()
{
	cherriesEaten = 0;
	mX = 0;
	mY = 1;
	cX[0] = 0;
	cY[0] = 1;
	color = GetStdHandle(STD_OUTPUT_HANDLE);

}



void Maze::mouseWins() //displayed when the mouse eats 5 cherries or he finds the exit
{
	system("cls");
	for (int i = 0; i < 10; i++)
		cout << endl;
	SetConsoleTextAttribute(color, 2);
	cout << "                                 #     #                                                       " << endl;
	cout << "                                 ##   ##  ####  #    #  ####  ######    #    # # #    #  ####  " << endl;
	cout << "                                 # # # # #    # #    # #      #         #    # # ##   # #      " << endl;
	cout << "                                 #  #  # #    # #    #  ####  #####     #    # # # #  #  ####  " << endl;
	cout << "                                 #     # #    # #    #      # #         # ## # # #  # #      # " << endl;
	cout << "                                 #     # #    # #    # #    # #         ##  ## # #   ## #    # " << endl;
	cout << "                                 #     #  ####   ####   ####  ######    #    # # #    #  ####  " << endl;


}
void Maze::gameOver() //displayed when a cat eats a mouse
{
	system("cls");
	for (int i = 0; i < 10; i++)
		cout << endl;
	SetConsoleTextAttribute(color, 4);
	cout << "                                 #####                          #######                      " << endl;
	cout << "                                 #     #   ##   #    # ######   #     # #    # ###### #####  " << endl;
	cout << "                                 #        #  #  ##  ## #        #     # #    # #      #    # " << endl;
	cout << "                                 #  #### #    # # ## # #####    #     # #    # #####  #    # " << endl;
	cout << "                                 #     # ###### #    # #        #     # #    # #      #####  " << endl;
	cout << "                                 #     # #    # #    # #        #     #  #  #  #      #   #  " << endl;
	cout << "                                 #####   #    # #    # ######   #######   ##   ###### #    # " << endl;

}

void Maze::loadMaze() //load the maze from text file into mazeBoard
{
	char c;

	ifstream filein("maze.txt");
	for (int row = 0; row < 30; row++)
	{
		for (int col = 0; col < 70; col++)
		{
			filein >> c;
			if (c == '1')
				mazeBoard[row][col] = 1;
			else if (c == '0')
				mazeBoard[row][col] = 0;
			else if (c == '2')
				mazeBoard[row][col] = 2;
			else if (c == '3')
				mazeBoard[row][col] = 3;
		}
	}
	filein.close();

}

void Maze::showCat(int catNum) //displays cat on board
{
	gotoxy(cX[catNum], cY[catNum]);
	cout << "#";
}

void Maze::hideCat(int catNum) //temporarily erases cat from board
{
	gotoxy(cX[catNum], cY[catNum]);
	cout << " ";
}

void Maze::positionCat(int catNum)
{
	while (mazeBoard[cY[catNum]][cX[catNum]] != 0) //Assign a random cY[catNum] and cX[catNum] until it is an open spot on the maze
	{
		cY[catNum] = rand() % 30;
		cX[catNum] = rand() % 70;
	}

}

void Maze::showMouse() //displays mouse on board
{
	gotoxy(mX, mY);
	cout << "x";
}

void Maze::hideMouse() //temporarily erases mouse from board
{
	gotoxy(mX, mY);
	cout << " ";
}


void Maze::displayMaze(int x, int y) //prints out maze from array
{
	for (int row = 0; row < 30; row++)
	{
		for (int col = 0; col < 70; col++)
		{
			gotoxy(col + x, row + y);
			if (mazeBoard[row][col] == 1)
			{
				SetConsoleTextAttribute(color, 11);
				cout << char(219); //maze walls
				SetConsoleTextAttribute(color, 7);
			}
			else if (mazeBoard[row][col] == 0)
				cout << " "; //maze spaces
			else if (mazeBoard[row][col] == 2)
			{
				SetConsoleTextAttribute(color, 14);
				cout << char(219); //maze exit
				SetConsoleTextAttribute(color, 7);

			}
			else if (mazeBoard[row][col] == 3)
			{
				SetConsoleTextAttribute(color, 6);
				cout << "*";
				SetConsoleTextAttribute(color, 7);
			}


		}

		cout << endl;
	}

	cout << endl << "	   COMMANDS:" << endl;
	cout << "	   Press 'c' to Add A Cat Into The Maze (Recommended: 5 (MAX 10))" << endl;
	cout << "	   Press 'ESC' to Exit the Game" << endl << endl;
	cout << "	   RULES:" << endl;
	cout << "	   If the Mouse Eats 10 Pieces Of Cheese He Wins Automatically" << endl;
	cout << "	   The Mouse MUST Eat At Least 5 Pieces Of Cheese Before He Finds the Exit to Win" << endl;
	cout << "	   Cats Can STEAL Cheese From the Mouse" << endl;
	cout << "	   The Mouse Can Be Pretty Quick, So the Cat Has a Chance Of MISSING the Mouse" << endl;

}

bool Maze::isTopMouse(int x, int y) //used to make sure the mouse does not backtrack unless it has reached a dead end
{
	if (mousePos.peekMouse().x == x && mousePos.peekMouse().y == y) //don't let the mouse go to a location if it just came from it (top -1)
		return true;
	else
		return false;
}

bool Maze::isTopCat(int x, int y, int catNum) //used to make sure the cat does not backtrack unless it has reached a dead end
{
	if (catPos[catNum].peekCat().x == x && catPos[catNum].peekCat().y == y) //don't let the cat go to a location if it just came from it (top -1)
		return true;
	else
		return false;
}

bool Maze::didCatEatMouse(int numCat)
{
	if ((catPos[numCat].peekCat().x == mousePos.peekMouse().x) && (catPos[numCat].peekCat().y == mousePos.peekMouse().y)) //if the top-1 for the mouse and cat stacks are equal for any cat, end the game
	{
		return true;
	}
	else
		return false;

	/*
	* each time the moveMouse() function is called, pass the mouse's x and y value into the didCatEatMouse() function
	* go through all cats and see if they equal that mouse's position
	* sometimes, the mouse will get lucky and the mouse will dodge the cat's attack
	*/
}

bool Maze::moveMouse()
{
	tempM.x = mX;
	tempM.y = mY;
	hideMouse();

	if (cherriesEaten == 10) //if the mouse eats 10 cherries, end game and display "Mouse Won"
	{
		return false;
	}

	if (mazeBoard[mY][mX + 1] == 2 && cherriesEaten >= 5) //if the mouse reaches the exit and has eaten at least 5 cherries, end game and display "Mouse Won"
	{
		mX++;
		return false;
	}

	else if (mazeBoard[mY + 1][mX] == 3 && !(isTopMouse(mX, mY + 1))) //if down is cherry and not top of stack 
	{
		cherriesEaten++;
		mousePos.pushMouse(mX, mY);
		mY++;
	}


	else if (mazeBoard[mY][mX + 1] == 3 && !(isTopMouse(mX + 1, mY)))//if right is cherry and not top of stack 
	{
		cherriesEaten++;
		mousePos.pushMouse(mX, mY);
		mX++;
	}

	else if (mazeBoard[mY][mX - 1] == 3 && !(isTopMouse(mX - 1, mY))) //if left is cherry and not top of stack 
	{
		cherriesEaten++;
		mousePos.pushMouse(mX, mY);
		mX--;
	}

	else if (mazeBoard[mY - 1][mX] == 3 && !(isTopMouse(mX, mY - 1))) //if up is cherry and not top of stack 
	{
		cherriesEaten++;
		mousePos.pushMouse(mX, mY);
		mY--;
	}

	else if (mazeBoard[mY + 1][mX] == 0 && !(isTopMouse(mX, mY + 1))) //if down and not top of stack
	{
		mousePos.pushMouse(mX, mY);
		mY++;
	}


	else if (mazeBoard[mY][mX + 1] == 0 && !(isTopMouse(mX + 1, mY))) //if right and not top of stack
	{
		mousePos.pushMouse(mX, mY);
		mX++;
	}

	else if (mazeBoard[mY][mX - 1] == 0 && !(isTopMouse(mX - 1, mY))) // if left and not top of stack
	{
		mousePos.pushMouse(mX, mY);
		mX--;
	}

	else if (mazeBoard[mY - 1][mX] == 0 && !(isTopMouse(mX, mY - 1))) // if up and not top of stack
	{
		mousePos.pushMouse(mX, mY);
		mY--;
	}

	else //dead end, start backtracking
	{
		mousePos.popMouse();
		mazeBoard[mY][mX] = 1;
		mX = tempM.x;
		mY = tempM.y;
	}

	showMouse();
	Sleep(30);
	return true;


}

bool Maze::moveCat(int catNum)
{
	tempC.x = cX[catNum];
	tempC.y = cY[catNum];
	hideCat(catNum);


	if (((mazeBoard[cY[catNum] + 1][cX[catNum]] == 0) || (mazeBoard[cY[catNum] + 1][cX[catNum]] == 3)) && !(isTopCat(cX[catNum], cY[catNum] + 1, catNum))) // if down and not top of stack
	{
		mazeBoard[cY[catNum] + 1][cX[catNum]] = 0; //turn whatever position next to it into a 0, so the cat removes the cherry if there is one
		catPos[catNum].pushCat(cX[catNum], cY[catNum]);
		cY[catNum]++;

	}

	else if (((mazeBoard[cY[catNum]][cX[catNum] + 1] == 0) || (mazeBoard[cY[catNum]][cX[catNum] + 1] == 3)) && !(isTopCat(cX[catNum] + 1, cY[catNum], catNum))) // if right and not top of stack
	{
		mazeBoard[cY[catNum]][cX[catNum] + 1] = 0; //turn whatever position next to it into a 0, so the cat removes the cherry if there is one
		catPos[catNum].pushCat(cX[catNum], cY[catNum]);
		cX[catNum]++;

	}

	else if (((mazeBoard[cY[catNum] - 1][cX[catNum]] == 0) || (mazeBoard[cY[catNum] - 1][cX[catNum]] == 3)) && !(isTopCat(cX[catNum], cY[catNum] - 1, catNum))) //if up and not top of stack
	{
		mazeBoard[cY[catNum] - 1][cX[catNum]] = 0; //turn whatever position next to it into a 0, so the cat removes the cherry if there is one
		catPos[catNum].pushCat(cX[catNum], cY[catNum]);
		cY[catNum]--;

	}

	else if (((mazeBoard[cY[catNum]][cX[catNum] - 1] == 0) || (mazeBoard[cY[catNum]][cX[catNum] - 1] == 3)) && !(isTopCat(cX[catNum] - 1, cY[catNum], catNum))) //if left and not top of stack
	{
		mazeBoard[cY[catNum]][cX[catNum] - 1] = 0; //turn whatever position next to it into a 0, so the cat removes the cherry if there is one
		catPos[catNum].pushCat(cX[catNum], cY[catNum]);
		cX[catNum]--;

	}

	else //dead end, start backtracking
	{

		catPos[catNum].popCat();
		if (mazeBoard[cY[catNum]][cX[catNum] + 1] != 2)
		{
			mazeBoard[cY[catNum]][cX[catNum]] = 1;
		}
		cX[catNum] = tempC.x;
		cY[catNum] = tempC.y;

	}

	showCat(catNum);
	Sleep(30);
	return true;
}




