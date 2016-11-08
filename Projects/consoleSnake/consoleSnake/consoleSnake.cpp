//  mainLogic.cpp
//  UniqueSnake
//


#include <iostream>
#include <windows.h>
#include <fstream>
#include "snake.h"

using namespace std;

int menu();
void play(CSnake *snake);
void highscore(CSnake *snake);
void options(CSnake *snake);
void sortFileScore(CSnake *snake);

int main()
{
	CSnake snake(10,10);
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	do
	{
		switch(menu()) {
			case 1:
				snake.clearAllSnake(console);
				snake.resetSnake();
				snake.drawArena(console);
				play(&snake);
				sortFileScore(&snake);
				break;
			case 2:
				highscore(&snake);
				break;
			case 3:
				options(&snake);
				break;
			case 0:
				return 0;
				break;
		}
		system("cls");
	}
	while(true);

	return 0;
}

int menu()
{
	int op = 0;

	cout << "---- Menu ----" << endl;
	cout << "[1]- Play" << endl;
	cout << "[2]- Highscores" << endl;
	cout << "[3]- Options" << endl;
	cout << "[0]- Exit" << endl;
	cin >> op;

	while (op < 0 || op > 3) {
		cout << "Choose a valid option:" << endl; 
		cin >> op;
	}
	
	system("cls");
	return op;
}

void options(CSnake *snake)
{
	int op = 0;

	cout << "---- Speed ----" << endl;
	cout << "[1]- Fast" << endl;
	cout << "[2]- Normal" << endl;
	cout << "[3]- Slow" << endl;
	cout << "Your current is: " << snake->gameSpeed << endl;
	cin >> op;

	while (op < 1 || op > 3) {
		cout << "Choose a valid option:" << endl; 
		cin >> op;
	}

	switch(op)
	{
		case 1: snake->gameSpeed = 30;
				break;
		case 2: snake->gameSpeed = 50;
				break;
		case 3: snake->gameSpeed = 70;
				break;
	}

	system("cls");
}

void highscore(CSnake *snake)
{
	ifstream fScore;
	fScore.open("score.snk");
	int i = 0,
		aux;

	cout << "Top Ten Scores:" << endl;

	while (fScore >> aux) {  // top 10
		cout << aux << endl;
		i++;
	}
	fScore.close();

	system("pause");
	system("cls");
}

void play(CSnake *snake)
{
	bool started = false;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD lastCoord = {0,0};
	COORD scoreCoord = {3, 23};
	CTimer timer;
	unsigned foodInterval = 5;

	//for(int i = 0; i < 5; i++) //starts with Head + 5 on tail
	//	snake->add2Tail();

	snake->setCursorAndDraw(console);

	timer.start(); 

	while (GetAsyncKeyState(VK_ESCAPE) == 0) {
		if (timer.elapsedTime() >= foodInterval) {
			if (snake->foodExist)
				snake->clearFood(console);

			snake->createFood(console);
			snake->foodExist = true;
			timer.start();
		}
		else {
			snake->clearAllSnake(console);

			if (GetAsyncKeyState(VK_LEFT) != 0) {
				snake->setTalePositions();
				snake->add2Coords(-1, 0);
				lastCoord.X = -1; lastCoord.Y = 0; started = true;
			}
			else if (GetAsyncKeyState(VK_RIGHT) != 0) {
				snake->setTalePositions();
				snake->add2Coords(1, 0);
				lastCoord.X = 1; lastCoord.Y = 0; started = true;
			}
			else if (GetAsyncKeyState(VK_UP) != 0) {
				snake->setTalePositions();
				snake->add2Coords(0, -1);
				lastCoord.X = 0; lastCoord.Y = -1; started = true;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0) {
				snake->setTalePositions();
				snake->add2Coords(0, 1);
				lastCoord.X = 0; lastCoord.Y = 1; started = true;
			}
			else {
				if(started)
					snake->setTalePositions();
				snake->add2Coords(lastCoord.X, lastCoord.Y);
			}	

			if (snake->detectAreacollision() || snake->detectBodycollision()) {
				lastCoord.X = 0;
				lastCoord.Y = 0;
				snake->clearAllSnake(console);
				started = false;
				snake->resetSnake();
				snake->drawArena(console);
			}
			else {
				snake->setCursorAndDraw(console);
				snake->detectFoodcollision();
			}

			SetConsoleCursorPosition(console, scoreCoord);
			cout << "Score: " << snake->score << " || Lives: " << snake->lifes << "    ";

			if(snake->lifes <= 0)
				break;

			
			Sleep(snake->gameSpeed);
		}
	}

	cout << "Game Over :)  ";

	system("pause");
	system("cls");
}

void sortFileScore(CSnake *snake)
{
	int scores[11];
	int i = 0,
		aux;

	ifstream fScoreRead;
	fScoreRead.open("score.snk");

	while (fScoreRead >> aux) {
		scores[i] = aux;
		i++;
	}

	scores[i] = snake->score;

	int auxSort;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {

			if (scores[i] > scores[j]) {
				auxSort = scores[i];
				scores[i] = scores[j];
				scores[j] = auxSort;
			}
		}
	}

	ofstream fScoreWrite;
	fScoreWrite.open("score.snk");

	for (int i = 0; i < 10; i++) {
		fScoreWrite << scores[i] << "\n";
	}
}

