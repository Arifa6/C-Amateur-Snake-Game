/*
 * srcfile.cpp
 *
 *  Created on: Aug. 22, 2019
 *      Author: massih
 */
#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
using namespace std;

bool gameOver;

const int width = 20;
const int height = 20;

int xPosition, yPosition, xFruit, yFruit, score;
int xTail[100], yTail[100];
int lengthTail;
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT}dir;

void Setup(){

	gameOver = false;
	dir = STOP;
	xPosition = width / 2;
	yPosition = height / 2;
	xFruit = rand() % (width + 2);
	yFruit = rand() % (height + 2);
}
void Visuals(){
	// this is the seizure way of making the game
	system("cls");
	for(int i = 0; i < width + 3; i++)
		cout << "#";
	cout << endl;
	for(int i = 0; i < height + 1; i++){
		for(int j = 0; j <= width + 1; j++){
			if(j == 0)
				cout << "#";
			if(i == yPosition && j == xPosition)
				cout << "O";
			else if(i == yFruit && j == xFruit)
				cout << "F";
			else if(j == width + 1 )
				cout << "#";
			else{
				bool print = false;
				for(int k = 0; k < lengthTail; k++){
					if(xTail[k] == j  && yTail[k] == i){
						cout << "o";
						print = true;
					}
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	for(int i = 0; i < width + 3; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input(){
	if(kbhit()){
		switch(getch()){
		case 'w' :
			dir = UP;
			break;
		case 's' :
			dir = DOWN;
			break;
		case 'a' :
			dir = LEFT;
			break;
		case 'd' :
			dir = RIGHT;
			break;
		case 'x' :
			gameOver = true;
			break;
		}
	}
}

void Logic(){
	int prevX = xTail[0];
	int prevY = yTail[0];
	int prev2X, prev2Y;
	xTail[0] = xPosition;
	yTail[0] = yPosition;
	for(int i = 1;i < lengthTail; i++){
		prev2X = xTail[i];
		prev2Y = yTail[i];
		xTail[i] = prevX;
		yTail[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch(dir){
	case UP:
		yPosition--;
		break;
	case DOWN:
		yPosition++;
		break;
	case LEFT:
		xPosition--;
		break;
	case RIGHT:
		xPosition++;
		break;
	default:
		break;
	}
	if(xPosition > width || xPosition < 0|| yPosition > height|| yPosition < 0)
		gameOver = true;
	for(int i = 0; i < lengthTail; i++){
		if(xTail[i] == xPosition && yTail[i] == yPosition)
			gameOver = true;
	}
	if(xPosition == xFruit && yPosition == yFruit){
		score += 10;
		xFruit = rand() % width;
		yFruit = rand() % height;
		lengthTail++;
	}
}
int main(){
	srand(time(0));
	Setup();
	while(!gameOver){
		Input();
		Visuals();
		Logic();
		(Sleep(100));
	}
}
