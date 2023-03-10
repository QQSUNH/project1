#pragma once
#define MAX_CHANCE 10
#define DIGIT 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_numbers(int random[], int hint[]);
int get_user(int user[], char usernumber[]);
void play_game(int random[], int hint[], int user[], int* chance, int* try_count, int* game_over);
