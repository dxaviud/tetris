#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <functional>
#include <thread>

bool quit = false;
int score = 0;

const int screenWidth = 12;
const int screenHeight = 18;
const std::string leftPadding = "     ";

char screen[screenHeight][screenWidth] = {
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
	{'#','#','#','#','#','#','#','#','#','#','#','#'}

};

enum ClockwiseRotation {none, one, two, three};

class Tetromino
{
public:
	char symbol;
	int x = screenWidth/2, y = 0;
	bool shape[4][4] = { 0 };
	bool noRotation[4][4] = { 0 };
	bool oneRotation[4][4] = { 0 };
	bool twoRotation[4][4] = { 0 };
	bool threeRotation[4][4] = { 0 };
	ClockwiseRotation rotation = none;
	virtual void rotate()
	{
		switch (rotation)
		{
		case none:
			if (!collision(x, y, oneRotation))
			{
				changeShape(oneRotation);
				rotation = one;
			}
			break;
		case one:
			if (!collision(x, y, twoRotation))
			{
				changeShape(twoRotation);
				rotation = two;
			}
			break;
		case two:
			if (!collision(x, y, threeRotation))
			{
				changeShape(threeRotation);
				rotation = three;
			}
			break;
		case three:
			if (!collision(x, y,noRotation))
			{
				changeShape(noRotation);
				rotation = none;
			}
			break;
		}
	}
	bool collision(int x, int y, bool newShape[4][4])
	{
		for (int yy = 0; yy < 4; yy++)
		{
			for (int xx = 0; xx < 4; xx++)
			{
				if (newShape[yy][xx] && screen[y+yy][x+xx] != ' ')
					return true;
			}
		}
		return false;
	}
	void stop()
	{
		for (int yy = 0; yy < 4; yy++)
		{
			for (int xx = 0; xx < 4; xx++)
			{
				if (shape[yy][xx])
					screen[y + yy][x + xx] = symbol;
			}
		}
	}
	void changeShape(bool newShape[4][4])
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				shape[y][x] = newShape[y][x];
			}
		}
	}

};

//none
//0010
//0010
//0010
//0010

//one
//0000
//0000
//1111
//0000

//two
//0100
//0100
//0100
//0100

//three
//0000
//1111
//0000
//0000

class LineT : public Tetromino
{
public:
	LineT()
	{
		symbol = 'A';

		noRotation[0][2] = 1;
		noRotation[1][2] = 1;
		noRotation[2][2] = 1;
		noRotation[3][2] = 1;

		oneRotation[2][0] = 1;
		oneRotation[2][1] = 1;
		oneRotation[2][2] = 1;
		oneRotation[2][3] = 1;

		twoRotation[0][1] = 1;
		twoRotation[1][1] = 1;
		twoRotation[2][1] = 1;
		twoRotation[3][1] = 1;

		threeRotation[1][0] = 1;
		threeRotation[1][1] = 1;
		threeRotation[1][2] = 1;
		threeRotation[1][3] = 1;

		changeShape(noRotation);
	}

};


//0000
//0110
//0110
//0000

class SquareT : public Tetromino
{
public:
	SquareT()
	{
		symbol = 'B';

		noRotation[1][1] = 1;
		noRotation[1][2] = 1;
		noRotation[2][1] = 1;
		noRotation[2][2] = 1;

		oneRotation[1][1] = 1;
		oneRotation[1][2] = 1;
		oneRotation[2][1] = 1;
		oneRotation[2][2] = 1;

		twoRotation[1][1] = 1;
		twoRotation[1][2] = 1;
		twoRotation[2][1] = 1;
		twoRotation[2][2] = 1;

		threeRotation[1][1] = 1;
		threeRotation[1][2] = 1;
		threeRotation[2][1] = 1;
		threeRotation[2][2] = 1;
		
		changeShape(noRotation);

	}
	void rotate() override {} //do nothing
};

//none
//0010
//0110
//0010
//0000

//one
//0000
//0010
//0111
//0000

//two
//0000
//0100
//0110
//0100

//three
//0000
//1110
//0100
//0000

class TeeT : public Tetromino
{
public:
	TeeT()
	{
		symbol = 'C';

		noRotation[0][2] = 1;
		noRotation[1][1] = 1;
		noRotation[1][2] = 1;
		noRotation[2][2] = 1;

		oneRotation[1][2] = 1;
		oneRotation[2][1] = 1;
		oneRotation[2][2] = 1;
		oneRotation[2][3] = 1;

		twoRotation[1][1] = 1;
		twoRotation[2][1] = 1;
		twoRotation[3][1] = 1;
		twoRotation[2][2] = 1;

		threeRotation[1][0] = 1;
		threeRotation[1][1] = 1;
		threeRotation[1][2] = 1;
		threeRotation[2][1] = 1;

		changeShape(noRotation);


	}
};

//none
//0100
//0100
//0110
//0000

//one
//0000
//0111
//0100
//0000

//two
//0000
//0110
//0010
//0010

//three
//0000
//0010
//1110
//0000

class ElT : public Tetromino
{
public:
	ElT()
	{
		symbol = 'D';

		noRotation[0][1] = 1;
		noRotation[1][1] = 1;
		noRotation[2][1] = 1;
		noRotation[2][2] = 1;

		oneRotation[1][1] = 1;
		oneRotation[1][2] = 1;
		oneRotation[1][3] = 1;
		oneRotation[2][1] = 1;

		twoRotation[1][1] = 1;
		twoRotation[1][2] = 1;
		twoRotation[2][2] = 1;
		twoRotation[3][2] = 1;

		threeRotation[2][0] = 1;
		threeRotation[2][1] = 1;
		threeRotation[2][2] = 1;
		threeRotation[1][2] = 1;

		changeShape(noRotation);

	}
};

//none
//0010
//0010
//0110
//0000

//one
//0000
//0100
//0111
//0000

//two
//0000
//0110
//0100
//0100

//three
//0000
//1110
//0010
//0000

class El2T : public Tetromino
{
public:
	El2T()
	{
		symbol = 'E';

		noRotation[0][2] = 1;
		noRotation[1][2] = 1;
		noRotation[2][2] = 1;
		noRotation[2][1] = 1;

		oneRotation[1][1] = 1;
		oneRotation[2][1] = 1;
		oneRotation[2][2] = 1;
		oneRotation[2][3] = 1;

		twoRotation[1][1] = 1;
		twoRotation[2][1] = 1;
		twoRotation[3][1] = 1;
		twoRotation[1][2] = 1;

		threeRotation[1][0] = 1;
		threeRotation[1][1] = 1;
		threeRotation[1][2] = 1;
		threeRotation[2][2] = 1;

		changeShape(noRotation);
	}
};

//none
//0000
//0110
//0011
//0000

//one
//0000
//0010
//0110
//0100

//two
//0000
//1100
//0110
//0000

//three
//0010
//0110
//0100
//0000

class ZeeT : public Tetromino
{
public:
	ZeeT()
	{
		symbol = 'F';

		noRotation[1][1] = 1;
		noRotation[1][2] = 1;
		noRotation[2][2] = 1;
		noRotation[2][3] = 1;

		oneRotation[1][2] = 1;
		oneRotation[2][1] = 1;
		oneRotation[2][2] = 1;
		oneRotation[3][1] = 1;

		twoRotation[1][0] = 1;
		twoRotation[1][1] = 1;
		twoRotation[2][1] = 1;
		twoRotation[2][2] = 1;

		threeRotation[0][2] = 1;
		threeRotation[1][1] = 1;
		threeRotation[1][2] = 1;
		threeRotation[2][1] = 1;

		changeShape(noRotation);
	}
};

//none
//0000
//0110
//1100
//0000

//one
//0100
//0110
//0010
//0000

//two
//0000
//0011
//0110
//0000

//three
//0000
//0100
//0110
//0010

class Zee2T : public Tetromino
{
public:
	Zee2T()
	{
		symbol = 'G';
		
		noRotation[1][1] = 1;
		noRotation[1][2] = 1;
		noRotation[2][0] = 1;
		noRotation[2][1] = 1;

		oneRotation[0][1] = 1;
		oneRotation[1][1] = 1;
		oneRotation[1][2] = 1;
		oneRotation[2][2] = 1;

		twoRotation[1][2] = 1;
		twoRotation[1][3] = 1;
		twoRotation[2][1] = 1;
		twoRotation[2][2] = 1;

		threeRotation[1][1] = 1;
		threeRotation[2][1] = 1;
		threeRotation[2][2] = 1;
		threeRotation[3][2] = 1;

		changeShape(noRotation);
	}
};

Tetromino* getNextT(int);

Tetromino* tetromino = getNextT(rand()%7);

void display()
{
	system("cls");
	std::cout << std::endl << std::endl;
	std::cout << leftPadding << "score: " << score << "\n" << std::endl;
	for (int y = 0; y < screenHeight; y++)
	{
		std::cout << leftPadding;
		for (int x = 0; x < screenWidth; x++)
		{
			if (screen[y][x] == '=')
				std::cout << '=';
			else if (x >= tetromino->x && y >= tetromino->y && x < tetromino->x + 4 && y < tetromino->y + 4 && tetromino->shape[y - tetromino->y][x - tetromino->x])
				std::cout << tetromino->symbol;
			else std::cout << screen[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << leftPadding << "q to quit";
}

void input()
{
	if (_kbhit())
	{
		char ch = _getch();
		if (ch == 'w')
		{
			//do nothing, can't move tetromino up
		}
		else if (ch == 's')
		{
			if (!tetromino->collision(tetromino->x, tetromino->y + 1, tetromino->shape))
				tetromino->y++;
		}
		else if (ch == 'a')
		{
			if (!tetromino->collision(tetromino->x - 1, tetromino->y, tetromino->shape))
				tetromino->x--;
		}
		else if (ch == 'd')
		{
			if (!tetromino->collision(tetromino->x + 1, tetromino->y, tetromino->shape))
				tetromino->x++;
		}
		else if (ch == 'o')
		{
			tetromino->rotate();
		}
		else if (ch == 'q')
			quit = true;

	}
}

void timer_start(std::function<void(void)> func, unsigned int interval)
{
	std::thread([func, interval]() {
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			func();
		}
	}).detach();
}

void deleteLine(int y)
{
	for (int x = 1; x < screenWidth - 1; x++)
		screen[y][x] = '=';
	display();
	Sleep(500);
	for (y; y > 0; y--)
	{
		for (int x = 0; x < screenWidth - 1; x++)
			screen[y][x] = screen[y-1][x];
	}
	score += 10;
}

void deleteLines()
{
	for (int y = tetromino->y; y < tetromino->y + 4 && y < screenHeight - 1; y++)
	{
		bool fullLine = true;
		for (int x = 1; x < screenWidth - 1; x++)
		{
			if (screen[y][x] == ' ')
			{
				fullLine = false;
				break;
			}
				
		}
		if (fullLine)
			deleteLine(y);

	}
}


void lowerTetromino()
{
	if (!tetromino->collision(tetromino->x, tetromino->y + 1, tetromino->shape))
		tetromino->y++;
	else
	{
		tetromino->stop();
		deleteLines();
		delete tetromino;
		tetromino = getNextT(rand() % 7);
		if (tetromino->collision(tetromino->x, tetromino->y, tetromino->shape))
			quit = true;
	}
	
}

Tetromino* getNextT(int i)
{
	switch (i)
	{
	case 0:
		return new LineT();
	case 1:
		return new SquareT();
	case 2:
		return new TeeT();
	case 3:
		return new ElT();
	case 4:
		return new El2T();
	case 5:
		return new ZeeT();
	case 6:
		return new Zee2T();
	default:
		return new LineT();
	}
}

int main()
{
	std::cout << std::endl << std::endl;
	std::cout << leftPadding << "Welcome to Tetris!" << std::endl;
	std::cout << leftPadding << "Controls: " << "a to move left, s to move down, d to move right" << std::endl;
	std::cout << leftPadding << "o to rotate" << std::endl;
	std::cout << std::endl << leftPadding << "Hit enter to begin game.";
	std::cin.get();

	timer_start(lowerTetromino, 1000);

	while (!quit)
	{
		display();
		input();
		Sleep(15);
	}


	
	system("cls");
	std::cout << leftPadding << "Game Over!" << std::endl;
	std::cout << leftPadding << "Your score: " << score << std::endl;
	std::cin.get();

	delete tetromino;

}

