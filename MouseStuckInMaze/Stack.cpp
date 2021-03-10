#include "Maze.h"


Stack::Stack()
{
	mtop = ctop = -1;
}

void Stack::pushMouse(int x, int y) //pushes current x and y for mouse into stack
{
	mouse[mtop].x = x;
	mouse[mtop].y = y;
	mtop++;
}

Stack::position Stack::popMouse() //returns the top-1 of stack
{
	if(mtop> 0)
		mtop--;
	return mouse[mtop];
}

Stack::position Stack::peekMouse() //returns the top-1 of stack without modifying
{
	position peekM;
	peekM = mouse[mtop - 1];
	return peekM;
}

void Stack::pushCat(int x, int y) //pushes current x and y for cat into stack
{
	cat[ctop].x = x;
	cat[ctop].y = y;
	ctop++;
}

Stack::position Stack::popCat() //returns the top-1 of stack
{
	if (ctop > 0)
		ctop--;
	return cat[ctop];
}

Stack::position Stack::peekCat() //returns the top-1 of stack without modifying
{
	position peekC;
	peekC = cat[ctop - 1];
	return peekC;
}






