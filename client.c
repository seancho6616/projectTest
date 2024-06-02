#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include "client.h"

//c = "l";

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void todayDate() {     // 오늘 날짜 함수
    time_t* curr;
    curr = time(NULL);
    struct tm* d;
    d = localtime(&curr);
    today.year = d->tm_year + 1900;
    today.month = d->tm_mon+1;
    today.day = d->tm_mday;
    today.hour = d->tm_hour;
}

void myRecode1() {  // 해당 고객 반려동물 목록 불러오는 함수
    system("cls");
    c = "p1";
    gotoxy(3, 1);
    printf("진료 기록 확인");
    gotoxy(40, 1);
    printf("%d-%d-%d", today.year, today.month, today.day);
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    gotoxy(2, 3);
    printf("* 명단\n\n");
}

void myRecode2() {
    system("cls");
    c = "p2";
    gotoxy(3, 1);
    printf("진료 기록 확인");
    gotoxy(40, 1);
    printf("%d-%d-%d", today.year, today.month, today.day);
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    gotoxy(2, 3);
    printf("* %s", animNum);
}

void reservationDate() {    // 예약 날짜 확인(다가오는 예약 날짜)
    c = "c1";
}

void reservationDerails() { // 예약 내역 확인
    system("cls");
    c = "c2";
    gotoxy(3, 4);
    printf("예약 내역 확인");
    gotoxy(40, 4);
    printf("%d-%d-%d", today.year, today.month, today.day);
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
}

void editInformation() {
    c = "p3";
}
//
//void reservationDate(TODAY d) {
//    char date[20];
//    sprintf(date, "%d@%d@%d@%d", d.year, d.month, d.day, d.hour);
//
//    while (1) {
//
//    }
//
//    printf("%d");
//}
//
//void hospitalRecode() {
//
//}
//
//void anumalNum(ANIMAL infor) {
//    char i[40];
//    sprintf(i, "%s@%s@%s@%s@%s",
//        infor.num, infor.bd.year, infor.bd.month, infor.bd.day, infor.c_id);
//}
//
unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
    while (1) {
        switch (c) {
            case 'l':
                send(sock, c, 2, 0);
                char loin; // 로그인시 서버로 넘기기 위한 변수(id, pw를 삽입)
                gets("%s", id);
                gets("%s", pw);
                sprintf(loin, "%s@%s", id, pw);
                send(sock, loin, strlen(loin), 0);
                break;
            case 'jc':
                send(sock, c, 2, 0);
                sprintf(join, "%s@%s@%s@%s", 
                    client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);
                c = "l";
                break;
            case 'jm':
                send(sock, c, 2, 0);
                sprintf(join, "%s@%s@%s@%s", 
                    manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);
                c = "l";
                break;
            case 'p1':
                send(sock, c, 2, 0); // c ="p1" -> 서버
                send(sock, client.id, strlen(client.id), 0);
                break;
            case 'p2':
                send(sock, c, 2, 0);
                send(sock, animNum, strlen(animNum), 0);
                break;
            case 'c1':
                send(sock, c, 2, 0);
                char date;
                sprintf(date, "%d@%d@%d@%d",
                    today.year, today.month, today.day, today.hour);
                send(sock, date, strlen(date), 0);
        }
    }
    return 0;
}

//unsigned WINAPI RecvMsg(void* arg) {// 소켓send함수
//    int strLen;
//    while (1) {//반복
//        strLen = recv(sock, msg, BUF_SIZE - 1, 0);//서버로부터 메시지를 수신한다.
//        if (strLen == -1) return -1;
//        msg[strLen] = '\0';//문자열의 끝을 알리기 위해 설정
//        if (!strcmp(msg, "q")) {
//            printf("left\n");
//            closesocket(sock);
//            exit(0);
//        }
//        else {
//            printf("Result : %s\n", msg);
//        }
//        strcpy(msg, "");
//    }
//    return 0;
//}
//
