#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

// 콘솔창에서 wav형식의 오디오 파일을 재생할려면 playsound함수가 필요함.
// 이때 PlaySound 함수는 wchar_t 형식으로 된 파일경로만 인식
// charToWChar 함수는 char형식의 파일을 wchar_t형식으로 변환시키기 위해 쓰는 것
// wchar_t는 유니코드 문자를 저장하기 위한 데이터 타입임. 'char'타입의 문자열과는 다른 형태로 문자열을 표현

wchar_t* charToWChar(const char* str)  
// const char*타입의 문자열을 wchar_t* 타입의 문자열로 변환하는 함수 ,함수의 매개변수로는 const char*타입의 문자열 포인터 str이 전달됨
{
    const size_t size = strlen(str) + 1; 
    // strlen 함수를 사용하여 문자열 str의 길이를 측정, 이 길이에 1을 더해 문자열이 저장될 버퍼크기 계산
    wchar_t* wstr = (wchar_t*)calloc(size, sizeof(wchar_t));
    // calloc 함수를 사용하여 버퍼를 할당, 이때 할당된 메모리를 0으로 초기화
    mbstowcs_s(NULL, wstr, size, str, _TRUNCATE);
    // char 문자열을 wchar_t 문자열로 변환, 첫번째 매개변수 NULL은 변환된 문자열의 길이를 반환,
    // 두번째 매개변수는 변환된 문자열을 저장할 버퍼에 대한 포인터(str을 wstr로 지정)
    // 세번째 매개변수 size은 버퍼의 크기를 나타냄
    // 네번째 매개변수 str은 변환할 'char'형식의 문자열
    // 다섯번째 매개변수 _TRUNCAT는 변환할 문자수의 최대값 = 문자열이 안잘리게 함
    return wstr;
    // wchar_t형식으로 변환된 문자열을 반환
}

// ↑의 함수와 ↓의 함수는 wav형식의 오디오파일 재생 함수

void playMusic(const char* fileName) 
// const char* fileName 타입의 문자열 포인터 fileName 입력을 받음
{
    wchar_t* wfileName = charToWChar(fileName); 
    // 입력받은 fileName 문자열을 wchar_t*타입으로 변환 charToWChar함수에서 mbstowcs를 이용하여 변환
    PlaySound(wfileName, NULL, SND_FILENAME | SND_ASYNC); 
    /*변환된 wfileName을 이용하여 Playsound()함수를 호출해 재생하며, 
    SND_FILENAME을 이용하여 파일이름 전달하고 SND_ASYNC를 사용하여 비동기적으로 재생*/
    free(wfileName);
    // 재생이 되면 free()를 이용하여 문자열에 할당된 메모리를 해제
}

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
        printf("\t선택하세요 :");

        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            system("cls");  // 화면 초기화
            // 숫자야구 게임 코드 실행

            break;
        case 2:
            system("cls");  // 화면 초기화
            // 장애물을 점프해서 피하는 게임 코드 실행

            break;
        case 3:
            system("cls");  // 화면 초기화
            printf("먼저 숫자 야구부터 설명하겠습니다.\n\n ");
            printf("게임을 시작하면 랜덤한 3자리의 값이 생성이 됩니다.\n ");
            printf("주어진 기회는 10회이며 중복된 숫자를 제외한 아무 숫자 3자리를 입력하시면 됩니다.\n\n ");
            printf("이때 입력한 숫자가 자릿수가 다르면서 값이 같으면 볼이며\n 값이 같으면서 자릿수가 같으면 스트라이크로 됩니다. \n ");// 도움말
            printf("\n");
            printf("예를 들어 815값이 생성이 되었을 때 263으로 입력해 봅시다.\n\n ");
            printf("생성된 숫자와 입력한 숫자에서 같은 자리에 같은 숫자는 없으므로 0볼이며\n 같은 숫자가 하나도 없으므로 0스트라이크 입니다.\n\n ");// 도움말
            printf("다시 215로 입력을 해보면, 같은 자리에 같은 숫자는 2개가 있고\n 같은 숫자가 없으므로 2스트라이크 0볼이 되는겁니다.\n\n "); // 도움말
            printf("이제 마지막으로 815를 입력하면 같은 자리에 같은 자리의 숫자는 3개가 있으므로\n 3스트라이크가 되며 플레이어가 이깁니다.\n\n "); // 도움말
            printf("주어진 기회는 10회이므로 신중하게 숫자를 골라보세요.\n ");
            printf("\n");
            printf("\n");
            printf("장애물 게임은 z 버튼을 누르면\n");
            printf("플레이어의 캐릭터는 점프를 하게 되고 장애물을 피할 수 있습니다.\n");
            printf("장애물을 피해서 최고점수를 기록해보세요.\n");
            break;
        case 4:
            system("cls");  // 화면 초기화
            // 랭킹
            break;
        case 5:
            return 0; // 프로그램 종료
        default:
            printf("잘못된 선택입니다.\n");
            break; // 프로그램 에러
        }
    }
}


int main() {
    system("COLOR 0F");
    system("mode con cols=100 lines=60");

    playMusic("C:\\Users\\KB\\Desktop\\music.wav");

    printTxtFile("text.txt");
   
    menu();
    system("cls");

    system("mode con cols=100 lines=60"); // 콘솔창 크기 조정
    printTxtFile("text.txt");
    printf("\n                                         게임이 종료되었습니다.\n");

    return 0;
}
