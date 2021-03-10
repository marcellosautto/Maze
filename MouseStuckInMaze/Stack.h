#pragma once
class Stack
{
public:

	struct position {

		int x, y;

	};

//constructor
Stack();
//functions
void pushMouse(int x, int y),
		pushCat(int x, int y);
position popMouse(),
peekMouse(),
popCat(),
peekCat();


//variables
	position mouse[1000];
	position cat[1000];
	int mtop, ctop;
};

