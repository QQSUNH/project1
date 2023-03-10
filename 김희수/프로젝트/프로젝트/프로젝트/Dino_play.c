#include"Dino_head.h"
#include"menu.h"
//위의 함수들을 활용하여 게임을 플레이 하는 함수

void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void start()
{
    system("mode con:cols=100 lines=25");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t                               3초후 게임을 시작합니다.\n");
    Sleep(1000);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t                               2초후 게임을 시작합니다.\n");
    Sleep(1000);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t                               1초후 게임을 시작합니다.\n");
    Sleep(1000);
}
void Dino_play()
{
    CursorView(0);
    start();
    playMusic("C:\\Users\\KB\\Desktop\\music2.wav");
    SetConsoleView();

    while (true)        //게임 루프
    {
        //게임 시작시 초기화과정을 실행
        bool isJumping = false;
        bool isBottom = true; // 바닥에 있을 때 
        const int gravity = 3; // 중력을 나타내는 'gravity'가 초기와 시켜줌

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;
        //초기화로 인해 공룡과 장애물의 위치도 초기값으로 설정됨

        int score = 0;
        clock_t start, curr;    //점수 변수 초기화
        start = clock();        //시작시간 초기화



        while (true)    //한 판에 대한 루프
        {
            //충돌 검사(isCollision)를 수행 
            //만약 충돌시 게임 루프를 탈출
            if (isCollision(treeX, dinoY))
                break;


            //z키가 눌렸고, 바닥이 아닐때 점프
            if (GetKeyDown() == 'z' && isBottom)
            {
                isJumping = true;
                isBottom = false;
            }

            //점프중이라면 Y를 감소, 점프가 끝났으면 Y를 증가.
            if (isJumping)
            {
                dinoY -= gravity;
            }
            else
            {
                dinoY += gravity;
            }

            //공룡의 위치를 계산, 공룡은 중력에 따라 내려가기 때문에
            //Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
            if (dinoY >= DINO_BOTTOM_Y)
            {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            //장애물을 이동시킴
            //treeX 변수를 이용하여 좌측으로 이동
            //나무의 위치가 왼쪽 끝으로가면 다시 오른쪽 끝으로 소환.
            treeX -= 2;//높을 수록 속도가 빨리짐
            if (treeX <= 0)
            {
                treeX = TREE_BOTTOM_X;
            }

            //점프의 맨위를 찍으면 점프가 끝난 상황.
            if (dinoY <= 3)
            {
                isJumping = false;
            }

            DrawDino(dinoY);        //draw dino
            DrawTree(treeX);        //draw Tree
            //'DrawDino'와 'DrawTree'함수 사용하여 게임화면을 그림(공룡과 장애물)

            curr = clock();            //현재시간 받아오기
            if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1초가 넘었을떄
            {
                score++;    //스코어 UP
                start = clock();    //시작시간 초기화
            }
            Sleep(60);
            //게임의 경과 시간에 따라 점수를 계산
            //경과 시간은 clock() 함수를 사용하여 측정
            //한 번의 루프마다 경과한 시간이 1초가 지나면 점수를 증가
            system("cls");
            //'system("cls")'함수 사용하여 게임화면을 지우고, 새로운 프레임을 그림

            //(v2.0) 점수출력을 1초마다 해주는것이 아니라 항상 출력해주면서, 1초가 지났을때 ++ 해줍니다.
            GotoXY(22, 0);    //커서를 가운데 위쪽으로 옮긴다. 콘솔창이 cols=100이니까 2*x이므로 22정도 넣어줌
            printf("Score : %d ", score);    //점수 출력해줌.
        }

        //게임 오버 메뉴
        DrawGameOver(score);
        //게임 루프를 탈출한 후, 'DrawGameOver' 함수를 호출하여 'GameOver'를 출력
    }
    
}