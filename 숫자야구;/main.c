#include "game.h"

int main()
{
    int random[3];
    int hint[2];
    random_numbers(random, hint);

    int chance = MAX_CHANCE;
    int try_count = 1;
    int game_over = 0;
    int user[3];
    char usernumber[1024];

    while (!game_over && chance > 0)
    {
        printf("남은 횟수: %d\n\n", chance);
        get_user(user, usernumber);
        play_game(random, hint, user, &chance, &try_count, &game_over);

    }

    if (chance == 0)
    {
        printf("\n게임 종료! %d번의 시도 내에 정답을 맞추지 못했습니다. \t정답은 %d%d%d입니다.\n", MAX_CHANCE, random[0], random[1], random[2]);
    }

    return 0;
}