//  snake.h
//  UniqueSnake
//
#include <iostream>
#include <windows.h>
#include <time.h>

//console size: 25x80

//snake base struct
struct tagSnakeBody{
	COORD snakePart;
	char character;
	struct tagSnakeBody* pNext;
};

class CTimer {
	private:
		unsigned startingTime;
	public:
		void start();
		unsigned elapsedTime();
};

void CTimer::start() {
	startingTime = clock();
}

unsigned CTimer::elapsedTime() {
	return ((unsigned) clock() - startingTime) / CLOCKS_PER_SEC;
}

//snake class
class CSnake {

	private:
		//snake it self
		struct tagSnakeBody *pHead;

	public:
		//constructor
		CSnake(int, int);
		
		//global vars
		int lifes;
		int score;
		COORD food;
		bool foodExist;
		DWORD gameSpeed;

		//functions
		void add2Tail();	
		void setCursorAndDraw(HANDLE);
		void add2Coords(int x, int y);
		void clearAllSnake(HANDLE console);
		void setTalePositions();
		void createFood(HANDLE console);
		void clearFood(HANDLE console);
		void detectFoodcollision();
		void drawArena(HANDLE console);
		bool detectAreacollision();
		void resetSnake();
		bool detectBodycollision();
};

// constructor
CSnake::CSnake(int x, int y) {
	struct tagSnakeBody *pNew;
	pHead = NULL;

	//new Snake Head
	pNew = (tagSnakeBody*)malloc(sizeof(struct tagSnakeBody));
	pNew->pNext = NULL;
	pNew->character = '>';
	pNew->snakePart.X = x;
	pNew->snakePart.Y = y;

	pHead = pNew;
	score = 0;
	lifes = 3;
	gameSpeed = 50;
}

//adds a new bodypart to tail
void CSnake::add2Tail() {
	struct tagSnakeBody *pNew;
	struct tagSnakeBody *pAux;

	//new Snake Body Part
	pNew = (tagSnakeBody*)malloc(sizeof(struct tagSnakeBody));
	pNew->pNext = NULL;
	pNew->character = '*';

	if(pHead == NULL)
		pHead = pNew;
	else
	{
		pAux = pHead;
		while(pAux->pNext != NULL)
			pAux = pAux->pNext;
		pNew->snakePart.X = pAux->snakePart.X - 1;
		pNew->snakePart.Y = pAux->snakePart.Y;
		pAux->pNext = pNew;
	}

}

//Places the cursor on console at the same coords as Snake Head is
void CSnake::setCursorAndDraw(HANDLE console) {
	struct tagSnakeBody *pAux;

	if(pHead == NULL)
		return;
	else
	{
		pAux = pHead;
		while(pAux != NULL)
		{
			SetConsoleCursorPosition(console, pAux->snakePart);
			std::cout << pAux->character;
			pAux = pAux->pNext;
		}
	}
}

//make it move
void CSnake::add2Coords(int x, int y) {
	pHead->snakePart.X += x;
	pHead->snakePart.Y += y;
}

//clears the last place where the snake has been at
void CSnake::clearAllSnake(HANDLE console)
{
	struct tagSnakeBody *pAux;

	if (pHead == NULL)
		return;
	else {
		pAux = pHead;
		while (pAux != NULL) {
			SetConsoleCursorPosition(console, pAux->snakePart);
			std::cout << " ";
			pAux = pAux->pNext;
		}
	}
}

//makes tale to move with the head
void CSnake::setTalePositions()
{
	struct tagSnakeBody *pAux; 
	struct tagSnakeBody *beforeAux;
	
	if(pHead == NULL)
		return;
	else
	{
		pAux = pHead;
		while(pAux->pNext != NULL)
			pAux = pAux->pNext;

		while(pAux != pHead)
		{
			beforeAux = pHead;
			while(beforeAux->pNext != pAux)
				beforeAux = beforeAux->pNext;
			pAux->snakePart = beforeAux->snakePart;
			pAux = beforeAux;
		}
	}
}

//creates a piece of food at the console

void CSnake::createFood(HANDLE console)
{
	food.X = rand()%77+1;
	food.Y = rand()%19+1;

	SetConsoleCursorPosition(console, food);
	std::cout << "&";
}

//clears the food if not eaten
void CSnake::clearFood(HANDLE console)
{
	SetConsoleCursorPosition(console, food);
	std::cout << " ";
}

//food collision
void CSnake::detectFoodcollision()
{
	if (pHead->snakePart.X == food.X && pHead->snakePart.Y == food.Y) {
		foodExist = false;
		score++;
		add2Tail();
	}
}

//draw snake arena

void CSnake::drawArena(HANDLE console) {
	COORD auxCoord;

	for(int i = 0; i < 80; i++)
	{
		for(int j = 0; j < 22; j++)
		{
			auxCoord.X = i;
			auxCoord.Y = j;

			if(j == 0 || j == 21 || i == 0 || i == 79)
			{
				SetConsoleCursorPosition(console, auxCoord); 
				std::cout << "-";
			}
		}
	}
}

//detect area collision

bool CSnake::detectAreacollision() {
	if(pHead->snakePart.X == 0 || pHead->snakePart.X == 79 
		|| pHead->snakePart.Y == 0 || pHead->snakePart.Y == 21)
	{
		lifes--;
		return true;
	}

	return false;
}

//reset snake

void CSnake::resetSnake() {

	struct tagSnakeBody *pNew;
	pHead = NULL;

	//new Snake Head
	pNew = (tagSnakeBody*)malloc(sizeof(struct tagSnakeBody));
	pNew->pNext = NULL;
	pNew->character = '>';
	pNew->snakePart.X = 10;
	pNew->snakePart.Y = 10;

	pHead = pNew;

	for(int i = 0; i < 5; i++) //starts with Head + 5 on tail
		add2Tail();
}

//detect collision with own body

bool CSnake::detectBodycollision() {
	struct tagSnakeBody *pAux;

	if(pHead == NULL)
		return false;
	else
	{
		pAux = pHead->pNext;
		while(pAux != NULL)
		{
			if(pHead->snakePart.X == pAux->snakePart.X && pHead->snakePart.Y == pAux->snakePart.Y)
			{
				lifes--;
				return true;
			}
			pAux = pAux->pNext;
		}
	}

	return false;
}

