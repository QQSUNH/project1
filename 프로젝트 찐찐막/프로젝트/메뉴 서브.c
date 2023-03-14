#include "menu.h"
#include "Dino_head.h"
#include "baseball.h"
#include <errno.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 10
#define NUM_SCORES 100



// wav파일 재생을 위한 문자열 변환 함수
wchar_t* charToWChar(const char* str)
{
    const size_t size = strlen(str) + 1;
    wchar_t* wstr = (wchar_t*)calloc(size, sizeof(wchar_t));
    mbstowcs_s(NULL, wstr, size, str, _TRUNCATE);

    return wstr;

}

// wav파일 재생함수
void playMusic(const char* fileName)
{
    wchar_t* wfileName = charToWChar(fileName);
    PlaySound(wfileName, NULL, SND_FILENAME | SND_ASYNC);
    free(wfileName);
}


// txt파일 출력을 위한 코드
void printTxtFile(const char* fileName) {
    FILE* file;
    if (fopen_s(&file, fileName, "r") != 0) {
        printf("Failed to open file %s.\n", fileName);
        return;
    }

    char buffer[500];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
        fflush(stdout); // 출력 버퍼를 비워줍니다.
    }
    printf("\n");
    printf("\n");
    printf("\n");
    fclose(file);
}

//장애물피하기 랭킹 정렬
void read_and_sort_dino_data()
{
    // 파일에서 데이터 읽기
    FILE* fp_in;
    if (fopen_s(&fp_in, "dino.txt", "r") != 0) {
        printf("파일이 열리지 않습니다.");
        return;
    }

    int i, score[NUM_SCORES];
    char arr[NUM_SCORES][MAX_LEN];

    for (i = 0; i < NUM_SCORES; i++)
        fscanf_s(fp_in, "%s %d", arr[i], MAX_LEN, &score[i]);

    fclose(fp_in);

    // 내림차순으로 정렬
    int j, temp;
    char temp_str[MAX_LEN];
    for (i = 0; i < NUM_SCORES - 1; i++) {
        for (j = 0; j < NUM_SCORES - i - 1; j++) {
            if (score[j] < score[j + 1]) {
                temp = score[j];
                score[j] = score[j + 1];
                score[j + 1] = temp;

                strcpy_s(temp_str, MAX_LEN, arr[j]);
                strcpy_s(arr[j], MAX_LEN, arr[j + 1]);
                strcpy_s(arr[j + 1], MAX_LEN, temp_str);
            }
        }
    }

    // 정렬된 데이터 파일에 쓰기
    FILE* fp_out;
    if (fopen_s(&fp_out, "sorted_dino.txt", "w") != 0) {
        printf("파일이 열리지 않습니다.");
        return;
    }

    for (i = 0; i < NUM_SCORES; i++) {
        fprintf(fp_out, "%s %d\n", arr[i], score[i]);
    }

    fclose(fp_out);
}

//장애물피하기 점수 나열
void dinoscore()
{
    read_and_sort_dino_data();

    FILE* fp_in;
    if (fopen_s(&fp_in, "sorted_dino.txt", "r") != 0) {
        printf("파일이 열리지 않습니다.");
        return;
    }

    char name[MAX_LEN];
    int score;
    printf("<< 명예의 전당 >>\n");
    printf("Name\tScore\n");
    printf("--------------------\n");
    while (fscanf_s(fp_in, "%s %d", name, MAX_LEN, &score) == 2) {
        printf("%s\t%d\n", name, score);
    }

    fclose(fp_in);
}

//숫자야구 점수 정렬
void read_and_sort_baseball_data()
{
    // 파일에서 데이터 읽기
    FILE* fp_in;
    if (fopen_s(&fp_in, "baseball.txt", "r") != 0) {
        printf("파일이 열리지 않습니다.");
        return;
    }

    int i, score[NUM_SCORES];
    char arr[NUM_SCORES][MAX_LEN];
    int count = 0;

    for (i = 0; i < NUM_SCORES; i++, count++)
    {
        fscanf_s(fp_in, "%s %d", arr[i], MAX_LEN, &score[i]);
        if (score[i] < 0)
            break;

    }

    fclose(fp_in);

    // 오름차순으로 정렬
    int j, temp;
    char temp_str[MAX_LEN];
    for (i = 0; i < count; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (score[j] >  score[j + 1]) {
                temp = score[j];
                score[j] = score[j + 1];
                score[j + 1] = temp;

                strcpy_s(temp_str, MAX_LEN, arr[j]);
                strcpy_s(arr[j], MAX_LEN, arr[j + 1]);
                strcpy_s(arr[j + 1], MAX_LEN, temp_str);
            }
        }
    }

    // 정렬된 데이터 파일에 쓰기
    FILE* fp_out;
    if (fopen_s(&fp_out, "sorted_baseball.txt", "w") != 0) {
        printf("파일이 열리지 않습니다.");
        return;
    }

    for (i = 0; i < NUM_SCORES; i++) {
        fprintf(fp_out, "%s %d\n", arr[i], score[i]);
    }

    fclose(fp_out);
}

// 숫자야구 랭킹 나열
void baseballscore()
{
    read_and_sort_baseball_data();

    FILE* fp_in;
    if (fopen_s(&fp_in, "sorted_baseball.txt", "r") != 0) {
        printf("파일이 열리지 않습니다.");
        return;
    }

    char name[MAX_LEN];
    int sec;
    printf("<< 명예의 전당 >>\n");
    printf("Name\ttime\n");
    printf("--------------------\n");
    while (fscanf_s(fp_in, "%s %d", name, MAX_LEN, &sec) == 2) {
        printf("%s\t%d\n", name, sec);
    }

    fclose(fp_in);
}



// 메뉴 실행 코드
void menu()
{
    int choice = 0;
    printf("\t\t                              환영합니다!!!");
    printf("\n");
    printf("\n");



    while (1) {

        printf("\n");
        printf("\t▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩\n");
        printf("\t 1. 숫자야구");
        printf("       2. 장애물 피하기");
        printf("       3. 도움말");
        printf("       4. 랭킹");
        printf("       5. 종료\n\n");
        printf("\t선택하세요 : ");

        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            system("cls");  // 화면 초기화
            playMusic("C:\\Users\\KB\\Desktop\\music3.wav");
            // 숫자야구 게임 코드 실행
            play_baseball();
            break;
        case 2:
            system("cls");  // 화면 초기화
            playMusic("C:\\Users\\KB\\Desktop\\music2.wav");
            Dino_play();
            break;
        case 3:
            system("cls");  // 화면 초기화
            printf("먼저 숫자 야구부터 설명하겠습니다.\n ");
            printf("게임을 시작하면 랜덤한 3자리의 값이 생성이 됩니다.\n ");
            printf("주어진 기회는 10회이며 중복된 숫자를 제외한 아무 숫자 3자리를 입력하시면 됩니다.\n ");
            printf("이때 입력한 숫자가 자릿수가 다르면서 값이 같으면 볼이며, 값이 같으면서 자릿수가 같으면 스트라이크로 됩니다. \n ");// 도움말
            printf("\n");
            printf("예를 들어 815값이 생성이 되었을 때 263으로 입력해 봅시다.\n ");
            printf("생성된 숫자와 입력한 숫자에서 같은 자리에 같은 숫자는 없으므로 0볼이며, 같은 숫자가 하나도 없으므로 0스트라이크 입니다.\n ");// 도움말
            printf("다시 215로 입력을 해보면, 같은 자리에 같은 숫자는 2개가 있고 같은 숫자가 없으므로 2스트라이크 0볼이 되는겁니다.\n "); // 도움말
            printf("이제 마지막으로 815를 입력하면 같은 자리에 같은 자리의 숫자는 3개가 있으므로 3스트라이크가 되며 플레이어가 이깁니다.\n "); // 도움말
            printf("주어진 기회는 10회이므로 신중하게 숫자를 골라보세요.\n ");
            printf("\n");
            printf("\n");
            printf("장애물 게임은 z 버튼을 누르면\n");
            printf("플레이어의 캐릭터는 점프를 하게 되고 장애물을 피할 수 있습니다.\n");
            printf("장애물을 피해서 최고점수를 기록해보세요.\n");
            break;
        case 4:
            system("cls");  // 화면 초기화
            printTxtFile("text.txt");
            printf("\t▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩\n");
            printf("\t원하는 메뉴를 골라주세요 (1 = 숫자야구 2 = 장애물피하기 e = 메인메뉴) :");
            char input;
            do {
                input = getchar();
            } while (input != '1' && input != '2' && input != 'e');

            if (input == '1')
            {
                system("cls");
                printTxtFile("text.txt");
                // dino.txt 파일에 저장된 점수를 내림차순으로 정렬하는 코드
                baseballscore();

            }

            else if (input == '2')
            {
                system("cls");
                printTxtFile("text.txt");
                // dino.txt 파일에 저장된 점수를 내림차순으로 정렬하는 코드
                dinoscore();
            }            
            
            else if (input == 'e')
            {
                system("cls");  // 화면 초기화
                playMusic("C:\\Users\\KB\\Desktop\\music.wav");
                printTxtFile("text.txt");
                menu();
            }
            else
                printf("잘못된 입력입니다.");
            break;
        case 5:
            system("cls");

            printTxtFile("text.txt");
            printf("\n                                         게임이 종료되었습니다.\n");
            exit(0); // 프로그램 종료
        default:
            while (getchar() != '\n');
            system("cls");  // 화면 초기화
            printTxtFile("text.txt");
            menu();
            break; // 프로그램 에러
        }
    }
}