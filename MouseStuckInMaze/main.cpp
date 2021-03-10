#include "Maze.h"

bool main() {
	int totalCats = 0;
	char c;
	PlaySound(TEXT("music.wav"), NULL, SND_ASYNC); //Background Music
	Maze m;
	m.loadMaze();
	m.displayMaze(0, 0);
	while (1)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == 'c' && totalCats < 10) //if 'c' is hit, add a cat at the beginning, and every cat added afterwards is placed randomly in the maze
			{
				m.positionCat(totalCats);
				totalCats++;
			}
			else if (c == 27)
			{
				m.gameOver();
				PlaySound(TEXT("game_over.wav"), NULL, SND_SYNC); //game over sound effect
				return false;
			}

		}

		for (int i = 0; i < totalCats; i++) //moves cats
		{
			m.moveCat(i);
			if (m.didCatEatMouse(i)) //did a cat eat a mouse? if it did, display "game over"
			{
				m.gameOver();
				PlaySound(TEXT("game_over.wav"), NULL, SND_SYNC); //game over sound effect
				return false;
			}
		}

		if (!(m.moveMouse())) //if the mouse eats 10 cherries or finds the exit
		{
			m.mouseWins();
			PlaySound(TEXT("finish.wav"), NULL, SND_SYNC); //you won! sound
			return false;
		}

	}
}
