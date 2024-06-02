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

void todayDate() {     // ���� ��¥ �Լ�
    time_t* curr;
    curr = time(NULL);
    struct tm* d;
    d = localtime(&curr);
    today.year = d->tm_year + 1900;
    today.month = d->tm_mon+1;
    today.day = d->tm_mday;
    today.hour = d->tm_hour;
}

void myRecode1() {  // �ش� �� �ݷ����� ��� �ҷ����� �Լ�
    system("cls");
    c = "p1";
    gotoxy(3, 1);
    printf("���� ��� Ȯ��");
    gotoxy(40, 1);
    printf("%d-%d-%d", today.year, today.month, today.day);
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    gotoxy(2, 3);
    printf("* ���\n\n");
}

void myRecode2() {
    system("cls");
    c = "p2";
    gotoxy(3, 1);
    printf("���� ��� Ȯ��");
    gotoxy(40, 1);
    printf("%d-%d-%d", today.year, today.month, today.day);
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    gotoxy(2, 3);
    printf("* %s", animNum);
}

void reservationDate() {    // ���� ��¥ Ȯ��(�ٰ����� ���� ��¥)
    c = "c1";
}

void reservationDerails() { // ���� ���� Ȯ��
    system("cls");
    c = "c2";
    gotoxy(3, 4);
    printf("���� ���� Ȯ��");
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
unsigned WINAPI SendMsg(void* arg) {//���ۿ� �������Լ�
    while (1) {
        switch (c) {
            case 'l':
                send(sock, c, 2, 0);
                char loin; // �α��ν� ������ �ѱ�� ���� ����(id, pw�� ����)
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
                send(sock, c, 2, 0); // c ="p1" -> ����
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

//unsigned WINAPI RecvMsg(void* arg) {// ����send�Լ�
//    int strLen;
//    while (1) {//�ݺ�
//        strLen = recv(sock, msg, BUF_SIZE - 1, 0);//�����κ��� �޽����� �����Ѵ�.
//        if (strLen == -1) return -1;
//        msg[strLen] = '\0';//���ڿ��� ���� �˸��� ���� ����
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
