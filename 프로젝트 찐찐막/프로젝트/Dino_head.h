#pragma once

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//1
void SetConsoleView();

//2
void GotoXY(int x, int y);

//3
int GetKeyDown();

//4
void DrawDino(int dinoY);

//5
void DrawTree(int treeX);

//6
void DrawGameOver(const int score);

//7
bool isCollision(const int treeX, const int dinoY);

//8
void Dino_play();

//9
void CursorView(char show);

//10
void start();