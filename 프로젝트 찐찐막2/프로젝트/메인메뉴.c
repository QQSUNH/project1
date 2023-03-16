#include"Dino_head.h"
#include "menu.h"
#include "baseball.h"




int main() {
    system("COLOR 0F");
    system("mode con cols=115 lines=50");

    playMusic("C:\\Users\\KB\\Desktop\\music.wav");

    printTxtFile("text.txt");
    CursorView(0);
    menu();
    system("cls");

    system("mode con cols=100 lines=25"); // 콘솔창 크기 조정
    printTxtFile("text.txt");
    printf("\n                                         게임이 종료되었습니다.\n");

    return 0;
}