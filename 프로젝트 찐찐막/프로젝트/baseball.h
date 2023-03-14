#pragma once
#define MAX_CHANCE 10
#define DIGIT 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//1
void random_numbers(int random[], int hint[]);

//2
void get_user(int user[], char usernumber[]);


//3
void start_game(int random[], int hint[], int user[], int* chance, int* try_count, int* game_over);


//4
void gameover();

//5
void play_baseball();