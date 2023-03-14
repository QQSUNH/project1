#include "baseball.h"
#include "menu.h"
#include "Dino_head.h"

void count1(int* start_time)
{
    *start_time = time(NULL); // 시작 시점
    getchar(); //엔터 먹는 역할
}


void random_numbers(int random[], int hint[]) // 랜덤숫자 생성
{
    srand(time(NULL));

    int i = 0;
    while (i < 3)
    {
        random[i] = rand() % 10;
        for (int j = 0; j < i; j++)
        {
            if (random[j] == random[i])
            {
                i--;
                break;
            }
        }
        i++;
    }

    for (int index = 0; index < 2; index++)
    {
        hint[index] = rand() % 10;
        if (hint[index] == random[0] || hint[index] == random[1] || hint[index] == random[2])
        {
            index--;
        }
        if (index == 1 && hint[0] == hint[1])

            index--;

    }
}
void get_user(int user[], char usernumber[]) // 숫자입력받음
{
    printf("숫자 3개를 입력하세요. (중복 안됨)\n");

    while (1)
    {
        gets(usernumber);
        int digitCount = 0;
        for (; digitCount < 4; digitCount++)
        {
            if (usernumber[digitCount] == NULL)
            {
                break;
            }
        }
        if (digitCount != 3)
        {
            printf("3자리 입력\n");
            continue;
        }
        if (usernumber[0] < '0' || usernumber[0] >'9' || usernumber[1] < '0' || usernumber[1] >'9' || usernumber[2] < '0' || usernumber[2] >'9')
        {
            printf("잘못된 값.\n");
            continue;
        }
        for (int i = 0; i < 3; i++)
        {
            user[i] = usernumber[i] - '0';
        }
        if (user[0] == user[1] || user[0] == user[2] || user[1] == user[2])
        {
            printf("중복, 다시 입력해주세요.\n");
            continue;

        }

        break;
    }
}
void start_game(int random[], int hint[], int user[], int* chance, int* try_count, int* game_over, int start_time)
{
    int strike = 0;
    int ball = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (user[i] == random[j])
            {
                if (i == j)
                {
                    strike++;
                }

                else
                {
                    ball++;
                }
            }

        }
    }
    if (strike == 3)
    {
        int end_time = time(NULL);
        int elapsed_time = end_time - start_time;
        system("mode con cols=110 lines=50");
        system("cls");
        printTxtFile("win.txt");
        printf("%d번째 시도에 성공했습니다.\n", *try_count);
        printf("소요된 시간은 %d초 입니다.\n", elapsed_time);
        //count2();

        printf("플레이어 이름을 입력해주세요(한글제외) : ");

        char name[50];
        scanf_s("%s", name, (unsigned)_countof(name));



        FILE* file = NULL;
        errno_t err = fopen_s(&file, "baseball.txt", "a");
        if (err != 0)
        {
            printf("파일 열기에 실패했습니다.");
            exit(1);
        }

        fprintf(file, "%s %d\n", name, elapsed_time);
        fclose(file);

        printf("\n\n\n\n\n\n\n");
        printf("원하는 메뉴를 입력해주세요 (r = 재시작, e = 메뉴, w = 종료) : ");

        char input;
        do
        {
            input = getchar();
        } while (input != 'r' && input != 'e' && input != 'w');

        if (input == 'r')
        {
            play_baseball();
        }
        else if (input == 'e')
        {
            system("cls");
            system("mode con cols=100 lines=40"); // 콘솔창 크기 조정
            playMusic("C:\\Users\\KB\\Desktop\\music.wav");
            printTxtFile("text.txt");
            menu();
        }

        else if (input == 'w')
        {
            system("mode con cols=100 lines=40"); // 콘솔창 크기 조정
            printTxtFile("text.txt");
            printf("\n                                         게임이 종료되었습니다.\n");
            exit(0);
        }
        *game_over = 1;
        return ;
    }
    if (*try_count == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (user[i] == hint[0])
            {
                printf("[ %d ]는 없어요\n", user[i]);
                return;
            }
        }
    }
    if (*try_count == 4)
    {
        for (int i = 0; i < 3; i++)
        {
            if (user[i] == hint[0] || user[i] == hint[1])
            {
                printf("[ %d ]는 없어요\n", user[i]);
                return;
            }
        }
    }
    if (strike == 0 && ball == 0)
    {
        printf("0스트라이크 0볼입니다.\n");
    }
    else
    {
        printf("%d 스트라이크, %d 볼입니다.\n\n", strike, ball);
    }
    (*chance)--;
    (*try_count)++;
}
void gameover(int* random, int *hint, const int sec, int start_time)
{

    int chance = MAX_CHANCE;
    int try_count = 1;
    int game_over = 0;
    int user[3];
    char usernumber[1024];
    int end_time = time(NULL);
    int elapsed_time = end_time - start_time;
    while (!game_over && chance > 0)
    {
        printf("남은 횟수: %d\n\n", chance);
        get_user(user, usernumber);
        start_game(random, hint, user, &chance, &try_count, &game_over, start_time);

    }


    if (chance == 0)
    {
        system("mode con cols=110 lines=50");
        system("cls");
        printTxtFile("lose.txt");
        printf("\n게임 종료! %d번의 시도 내에 정답을 맞추지 못했습니다. \t정답은 %d%d%d입니다.\n", MAX_CHANCE, random[0], random[1], random[2]);


        printf("\n\n\n\n\n\n\n");
        printf("원하는 메뉴를 입력해주세요 (r = 재시작, e = 메뉴, w = 종료) : ");

        char input;
        do
        {
            input = getchar();
        } while (input != 'r' && input != 'e' && input != 'w');

        if (input == 'r')
        {
            play_baseball();
        }
        else if (input == 'e')
        {
            system("cls");
            system("mode con cols=100 lines=40"); // 콘솔창 크기 조정
            playMusic("C:\\Users\\KB\\Desktop\\music.wav");
            printTxtFile("text.txt");
            menu();
        }

        else if (input == 'w')
        {
            system("mode con cols=100 lines=40"); // 콘솔창 크기 조정
            printTxtFile("text.txt");
            printf("\n                                         게임이 종료되었습니다.\n");
            exit(0);
        }
    }


}



void play_baseball()
{
    
    CursorView(0);
    start();
    int start_time;
    count1(&start_time);
    system("cls");
    playMusic("C:\\Users\\KB\\Desktop\\music3.wav");
    int random[3];
    int hint[2];

    //char c = getchar();
    random_numbers(random, hint);
    int sec = 0;
    gameover(random, hint,sec,start_time);

}
