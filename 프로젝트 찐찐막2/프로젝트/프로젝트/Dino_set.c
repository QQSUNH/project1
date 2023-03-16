#include"Dino_head.h"
#include"menu.h"
#pragma region 콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView()
{
    system("mode con:cols=100 lines=25"); //실행 창의 크기
    system("title Google Dinosaurs. project_4Team"); //실행 창의 제목
}
#pragma endregion

#pragma region 커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
//WINDOW환경에서 Console 창에서 출력되는 텍스틑나 커서의 위치를 조작하는 'GotoXY'를 정의
{
    COORD Pos;
    //'COORD'는 Window API에서 정의 된 구조체로 x와 y좌표, Console창에서 커서의 위치를 지정
    Pos.X = 2 * x;//x의 값을 2배 대입
    Pos.Y = y;//그대로 대입
    //Console창에서 가로폭과 세로 높이가 비례하여 표시
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    //'SetConsoleCursorPosition'함수 호출
    //출력장치 핸들(GetStdHandle(STD_OUTPUT_HANDLE)과 위에서 구한 좌표값(Pos)을 인자로 전달
    //Console 창에서 커서의 위치를 해당 좌표값으로 이동
}
#pragma endregion

#pragma region 키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()//키보드 입력을 받아오는 함수
{
    if (_kbhit() != 0)//함수 내부에서 사용되는 '_kbit()'함수는 키보드 buffer에 입력된 키 이베트가 있는지 확인하는 함수
        //키 입력이 있다면 0이 아닌 값을 반환
    {
        return _getch();//함수 '_getch'는 키보드 버퍼에서 다음 입력을 읽어들이는 함수
        //읽어들인 키 값(ASCII코드)을 반환
    }
    return 0;
    //'_kibit()'함수가 0을 반환하여 키보드 버퍼에 입력된 키 이벤트가 없다면 함수는 '0'을 반환
}
/*따라서 'GetKeyDown()'함수는 현재 입력된 키 값을 반환하며, 만약 아무런 키 입력이 없다면 0을 반환
이함수를 이용하여 키 입력을 감지하고, 키보드 이벤트에 대응하는 동작을 수행할 수 있음.*/
#pragma endregion

#pragma region 공룡을 그리는 함수
void DrawDino(int dinoY)//공룡 모양을 출력하는 함수인 'DrawDino'를 정의
//함수의 입력값으로 공룡의 y축 위치(dinoY)가 주어지며, 이 위치에 공룡이 출력
{
    GotoXY(0, dinoY);//'GotoXY'함수로 공룡이 출력될 위치(0,dinoY)로 커서를 이동
    static bool legFlag = true;
    //변수 'static bool legFlag' 변수 선언, 공룡의 다리를 번갈아가며, 출력하기 위한 변수로 사용
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");
    if (legFlag)
    {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag = false;
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = true;
    }
    //공룡의 다리를 번갈아가며 출력하기 위해, 'legFlag' 변수를 사용하여 공룡 다리의 상태를 변경하면서 출력
    //만약 'legFlag'가 'true'이면, 왼쪽 다리를 출력하고 'false'이면 오른쪽 다리를 출력.
}
#pragma endregion

#pragma region 나무를 그리는 함수
void DrawTree(int treeX)
//나무(Tree)모양을 출력하는 함수인 'DrawTree'를 정의
//함수의 입력값으로 나무의 x축 위치(treeX)가 주어지며, 이 위치에 나무가 출력
{
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf(" $$ ");
    //함수 내부에서는 GotoXY 함수를 호출하여 나무가 출력될 위치(treeX, TREE_BOTTOM_Y)로 커서 이동
    //'TREE_BOTTOM_Y'는 나무의 밑바닥 높이를 나타내는 상수
}
#pragma endregion

#pragma region 충돌 했을때 게임오버
void DrawGameOver(const int score)
//'Game Over'메세지와 점수(score)를 출력하는 'DrawGamOver'을 정의
//함수의 입력값으로 플레이어가 회득한 점수(score)가 주어지며, 'GameOver'메세지 출력
{
    system("cls");
    //함수 내부에서 'system("cls")'함수를 사용하여 콘솔 창을 초기화
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);
    //'GotoXY 함수를 호출하여 메세지가 출력될 위치(x, y)로 커서 이동

    printf("\n\n\n\n\n\n\n\n\n");
    printf("플레이어 이름을 입력해주세요(영어로만) : ");

    char name[50];
    scanf_s("%s", name, (unsigned)_countof(name));



    FILE* file = NULL;
    errno_t err = fopen_s(&file, "dino.txt", "a");
    if (err != 0)
    {
        printf("파일 열기에 실패했습니다.");
        exit(1);
    }

    fprintf(file, "%s %d\n", name, score);
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
        Dino_play();
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


    //'system("pause")' 함수를 사용하여 사용자로부터 키 입력을 대기
    //게임 종료 후 Console창이 종료되지 않고, 사용자의 입력을 대기하다가 아무 키나 누르면 프로그램이 종료
}
#pragma endregion

#pragma region 충돌했으면 true, 아니면 false
bool isCollision(const int treeX, const int dinoY)
//충동 판정을 수행하는 함수인 'isCollision'을 정의
//입력 값으로 나무의 위치(treeX)와 공룡의 높이(dinoY)를 이용하여, 충돌 판정 수행
{
    //트리의 X가 공룡의 몸체쪽에 있을때,
    //공룡의 높이가 충분하지 않다면 충돌로 처리
    GotoXY(0, 0);
    //함수 내부에서 'GotoXY'함수를 사용하여 디버깅을 위한 메세지를 출력
    printf("treeX : %d, dinoY : %d", treeX, dinoY); //이런식으로 적절한 X, Y를 찾습니다.
    //출력 메세지는 현재 출동 판정에 사용되는 입력 값들인 treeX와 dinoY를 포함
    if (treeX <= 8 && treeX >= 4 && dinoY > 8)
        //'if'문을 사용하여 나무와 공룡의 위치가 충돌했는지 여부 판정
        //이 코드에서는 나무의 X위치가 4이상 8이하이고,
        //공룡의 위치 Y는 8이상일 때 충돌로 판정
        //디자인과 관련된 값으로, 게임을 구현하는데 따라 다른 값으로 설정될 수 있음.
    {
        return true;
    }
    return false;
    //충돌 발생 'true', 그렇지 않으면 'false'반환
}
#pragma endregion
