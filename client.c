#define _WINSOCK_DEPRECATED_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� ���ϰ��� ��� ���ÿ�
#define _CRT_SECURE_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� �Է°��� ��� ���ÿ�
#pragma comment(lib, "ws2_32")  //���־�Ʃ��� ȯ�濡�� ���߽� ���� ���̺귯�� ������#pragma warning(disable:4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <time.h>
#include "client.h"
#include "0609.h"

#define ID 20			// ID �迭ũ��
#define PW 20			// PW �迭ũ��
#define MAX 12			// �̸� �迭ũ��
#define NUM 16			// ��ȣ(��ȭ��ȣ, ��Ϲ�ȣ) �迭ũ��
#define RECORD 500		// ���� ��� �迭ũ��
#define LO 6			// ������ �ڵ� �迭ũ��
#define BUF_SIZE 700


TODAY today;
CLIENT client;
MANAGER manager;
ANIMAL animal;
MR mr1;
RESER reser1;

char id[ID] ="", pw[PW]="";		// �α����Ϸ��� id, pw
char join[BUF_SIZE]="";             // ������ �����ϰų� ���Ź��� �� ����� ���ڿ�
char animNum[NUM]="";            //  �ݷ������� ��ȣ�� ���� ����

char c = 'a';   // ��� �ڵ�
char c1 = 'a'; // Ŭ���̾�Ʈ ��� �ڵ� 

char rc = 0;	// ���Ź��� ��� �ڵ�
char resercheck;	// ���� ��¥ �ߺ� ����
int q = 5;
int q2 = 1;

int loinNum = 0; // �α��� Ȯ�ο���
//int num = 0;


void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//�䱸���� ID : P1
void todayDate() {     // ������ ��¥ �Լ�
    time_t* curr;
    curr = time(NULL);
    struct tm* d;
    d = localtime(&curr);
    today.year = d->tm_year + 1900; // 1900�� �������ν� 
    today.month = d->tm_mon+1;      // 0~11������ +1
    today.day = d->tm_mday;             // ���� �ϼ� 
    today.hour = d->tm_hour;            // ���� �ð� 0~23
}

// �䱸���� ID : P2
void myRecode1() {  // �ش� �� �ݷ����� ��� �ҷ����� �Լ�
    c = 'f';
    gotoxy(3, 1);                           // ��ġ�̵�
    printf("���� ��� Ȯ��\n");         
    for (int i = 0; i < 50; i++) {
        printf("-");
    }
    gotoxy(2, 3);
    printf(" ���\n\n");
}

// �䱸���� ID : P3
void myRecode2() {  // �ش� �ݷ����� ���� ��� �θ��� �Լ�
    c = 's';
    gotoxy(3, 1);                           // ��ġ �̵�
    printf("���� ��� Ȯ��\n");
    for (int i = 0; i < 50; i++) {
        printf("-");
    }
    gotoxy(3, 3);
    printf("%s\n", animNum);    // �Է� ���� ������Ϲ�ȣ ���
}


// �䱸���� ID : C1
void reservationDate() {    // ���� ��¥ Ȯ��(�ٰ����� ���� ��¥)
    c = 'd';
}

// �䱸���� ID : P4
void editInformation() {    // �������� �� Ż��
    
    int inputnum;
    switch (c1) {        // ���� ������(����) ����
        case 't':                   // ������(����)
            gotoxy(8,20);      // ��ġ �̵�
            printf("> ");            // �����ϰ��� �ϴ� ���� �Է� ��ġ Ȯ��
            scanf("%d", &inputnum); // �Է�( �����ϰ��� �ϴ� ����)
            getchar();
            switch (inputnum) {
                case 1: // ������ ����
                    // ��ġ ����
                    fflush(stdin); 
                    gotoxy(5, 4);
                    printf("> ");
                    gets(manager.name); // �����ϰ��� �ϴ� ������ �Է�
                    gotoxy(10, 13);
                    c = 't';                        // ������ ���� ������ �����ϱ� ���Ͽ�
                    break;
                case 2: // ���� ����
                    // ��ġ ����
                    fflush(stdin); 
                    gotoxy(5, 6);
                    printf("> ");
                    printf("�� : ");
                    gets(manager.lo.city);  // �����ϰ��� �ϴ� �� �Է�
                    gotoxy(15, 6);
                    printf("\t�� : ");
                    gets(manager.lo.dong);  // �����ϰ��� �ϴ� �� �Է�
                    c = 't';                        // ������ ���� ������ �����ϱ� ���Ͽ�
                    gotoxy(10, 13);
                    break;
                case 3: // �������
                    // ��ġ ����
                    fflush(stdin); 
                    gotoxy(5, 8);
                    printf("> ");
                    gets(manager.pw);           // �����ϰ��� �ϴ� PW �Է�
                    c = 't';                            // ������ ���� ������ �����ϱ� ���Ͽ�
                    gotoxy(10, 13);
                    break;
                case 4: // Ż��
                    c = 'y';
                    break;
            }
            break;
        case 'i':                       // ��
            gotoxy(3, 20);         // ��ġ �̵�
            printf("> ");                   // �����ϰ��� �ϴ� ���� �Է� ��ġ Ȯ��
            scanf("%d", &inputnum); // �Է�( �����ϰ��� �ϴ� ���� )
            getchar();
            switch (inputnum) {
                case 1: // ���� ����
                    gotoxy(5, 4);
                    printf("> ");
                    gets(client.name);              // �����ϰ��� �ϴ� �̸� �Է�
                    gotoxy(10, 13);
                    c = 'i';
                    break;
                case 2: // ��ȭ��ȣ ����
                    gotoxy(5, 6);
                    printf("> ");
                    gets(client.num);                   // �����ϰ��� �ϴ� ��ȣ �Է�
                    gotoxy(10, 13);
                    c = 'i';
                    break;
                case 3: // �������
                    gotoxy(5, 8);
                    printf("> ");
                    gets(client.pw);                    // �����ϰ��� �ϴ� PW �Է�
                    gotoxy(10, 13);
                    c = 'i';
                    break;
                case 4: // Ż��
                    c = 'v';
                    break;
            }
           break;
    }
}


// �䱸���� ID : M1
void todayReservation() {   // ���� ������ Ȯ�� ( ������ ( ���� ) )
    c = 'w';
}

// �䱸���� ID : M2
void hosptalRecode() {     // ������
    mr1.date.year = today.year;                     // ��¥�� �ڵ� ����
    mr1.date.month = today.month;
    mr1.date.day = today.day;
    mr1.date.hour = today.hour;
    strcpy(mr1.mgName, manager.name);
    gotoxy(20, 4);
    gets(mr1.num);
    gotoxy(4, 7);
    printf("> ");
    gets(mr1.record);
    printf("\n\n");
    c = 'r';
}

// �䱸���� ID : M4
void animalNum() {  // �ݷ����� ���
    gotoxy(15, 4);
    gets(animal.num);
    gotoxy(15, 6);
    scanf("%d", &animal.bd.year);
    gotoxy(sizeof(animal.bd.year) + 16, 6);
    printf(" - ");
    scanf("%d", &animal.bd.month);
    gotoxy((int)sizeof(animal.bd.month)*3 + 16, 6);
    printf(" - ");
    scanf("%d", &animal.bd.day);
    getchar();
    gotoxy(15, 8);
    gets(animal.c_id);
    c = 'n';
}

// �䱸���� ID : M3-1
void reservationCheck() {   // ���� ��¥ �ߺ� Ȯ��
    gotoxy(15, 4);
    scanf("%d", &reser1.date.year);
    gotoxy((int)sizeof(reser1.date.year) + 16, 4);
    printf(" - ");
    scanf("%d", &reser1.date.month);
    gotoxy((int)sizeof(reser1.date.day) * 3 + 16, 4);
    printf(" - ");
    scanf("%d", &reser1.date.day);
    gotoxy((int)sizeof(reser1.date.day) * 5 + 16, 4);
    printf(" ");
    scanf("%d", &reser1.date.hour);
    getchar();
    c = 'h';
}

// �䱸���� ID : M3
void reservation() {    // ����
    fflush(stdin);
    gotoxy(20, 6);
    gets(reser1.c_id);
    gotoxy(20, 8);
    gets(reser1.num);
    strcpy(reser1.mg_id, manager.id);
    strcpy(reser1.cord, "r");        // �����̶�� ���� Ȯ���ϱ� ���� �ڵ�
    c = 'e';
}

// �䱸���� ID : M4
void inoculation() {    // ����
    gotoxy(20, 4);
    gets(reser1.c_id);
    gotoxy(20, 8);
    gets(reser1.num);
    strcpy(reser1.mg_id, manager.id);
    strcpy(reser1.cord, "i");        // �����̶�� ���� Ȯ���ϱ� ���� �ڵ�
    reser1.date.year = today.year + 1;
    reser1.date.month = today.month;
    reser1.date.day = today.day;
    reser1.date.hour = 0;
    gotoxy(20, 6);  printf("%d - %d - %d",
        reser1.date.year-1, reser1.date.month, reser1.date.day);
    c = 'u';
}

// �䱸���� ID : S1
unsigned WINAPI SendMsg(void* arg) {//���ۿ� �������Լ�
    SOCKET sock = *((SOCKET*)arg);
    while (1) {
        switch (c) {
            case 'l':   //�α���
                sprintf(join, "%c@%s@%s", id, pw); //ID�� PW�� join�� ��ġ��
                send(sock, join, strlen(join), 0);  // join ������ ����
                strcpy(join, "");
                break;
            case 'j':  //�� ȸ������
                sprintf(join, "%c@%s@%s@%s@%s",        // ȭ�����Կ� �Է¹޾Ҵ� �� join�� ��ġ��
                    c, client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 'o':  //���� ȸ������
                sprintf(join, "%c@%s@%s@%s@%s@%s",        // ȭ�����Կ� �Է¹޾Ҵ� �� join�� ��ġ��
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 'f':   // ������ Ȯ�� 1
                sprintf(join, "%c@%s", c, client.id);
                send(sock, join, strlen(join), 0);    // �� ID ������ ����
                break;
            case 's': // ������Ȯ��2
                sprintf(join, "%c@%s", c, animNum);
                send(sock, join, strlen(join), 0);    // �� ID ������ ����break;
            case 'd':   // ���೯¥Ȯ��(��)
            case 'w':   // ���� ������ Ȯ��(����)
            case 'b':   // ���� ����Ȯ��(��)
                sprintf(join, "%c@%d@%d@%d@%d",        // date�� ��¥ ���� ��ġ��
                    c, today.year, today.month, today.day, today.hour);
                send(sock, join, strlen(join), 0);      // date ������ ����
                strcpy(join, "");
                break;
            case 'r':   // ������
                sprintf(join, "%c@%s@%d@%d@%d@%s@%s", 
                    c, mr1.num, mr1.date.year, mr1.date.month, mr1.date.day, mr1.mgName, mr1.record);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'e':   // ����
            case 'u':   // ����
                sprintf(join, "%c@%s@%s@%s@%d@%d@%d@%d@%s",
                    c, reser1.c_id, reser1.mg_id, reser1.num, reser1.date.year, reser1.date.month, reser1.date.day,
                    reser1.date.hour, reser1.cord);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'n':   // �������� ���
                sprintf(join, "%c@%s@%d@%d@%d@%s",
                    c, animal.num, animal.bd.year, animal.bd.month, animal.bd.day, animal.c_id);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'i':       // �� ���� ����
                sprintf(join, "%c@%s@%s@%s@%s",        // �� ���� ������ �Է¹޾Ҵ� �� join�� ��ġ��
                    c, client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 't':       // ������ ���� ����
                sprintf(join, "%c@%s@%s@%s@%s@%s",        // ������ ���� ������ �Է¹޾Ҵ� �� join�� ��ġ��
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 'y':       // ������ Ż��
                sprintf(join, "%c@%s", c, manager.id);
                send(sock, join, strlen(join), 0);    // ������ ID ������ ����
                break;
            case 'v':       // �� Ż��
                sprintf(join, "%c@%s", c, client.id);
                send(sock, join, strlen(join), 0);    // �� ID ������ ����
                break;
            case 'q':
                printf("�����մϴ�.\n");
                closesocket(sock);
                exit(0);
        }
        c = '\0';
    }
    return 0;
}

unsigned WINAPI RecMsg(void* arg) {
    SOCKET sock = *((SOCKET*)arg);
    int strLen;
    char* word = NULL;
    int w;
    ANIMAL* current;
    while (1) {
        strLen = recv(sock, join, BUF_SIZE - 1, 0);
        if (strLen == -1)
            return -1;
        join[strLen] = '\0';
        if (!strcmp(join, "q")) {
            printf("Client : Disconnection\n");
            closesocket(sock);
            exit(0);
        }
        else {
            word = strtok(join, "@");
            rc = word[0];
            word = strtok(NULL, "@");
            switch (rc) {
            case 'l':		// �α��� 
                w = atoi(word);
                word = strtok(NULL, "@");
                switch (w) {
                case 0:
                    gotoxy(3, 7);
                    textcolor(RED);
                    printf("���̵� �Ǵ� ��й�ȣ�� �߸� �Է��߽��ϴ�.");
                    textcolor(WHITE);
                    system("pause");
                    c1 = 'a';
                    break;
                case 1:
                    strcpy(client.name, strtok(NULL, "@"));
                    strcpy(client.num, strtok(NULL, "@"));
                    strcpy(client.id, strtok(NULL, "@"));
                    strcpy(client.pw, strtok(NULL, "@"));
                    textcolor(GREEN);
                    printf("�α��� �Ǿ����ϴ�");
                    textcolor(WHITE);
                    c1 = 'c';
                    break;
                case 2:
                    strcpy(manager.name, strtok(NULL, "@"));
                    strcpy(manager.lo.city, strtok(NULL, "@"));
                    strcpy(manager.lo.dong, strtok(NULL, "@"));
                    strcpy(manager.id, strtok(NULL, "@"));
                    strcpy(manager.pw, strtok(NULL, "@"));
                    textcolor(GREEN);
                    printf("�α��� �Ǿ����ϴ�");
                    textcolor(WHITE);
                    c1 = 'm';
                    break;
                }
                strcpy(join, "");
                break;
            case 'j':		// �� ȸ������
                w = atoi(word);
                word = strtok(NULL, "@");
                switch (w) {
                case 0:
                    textcolor(RED);
                    printf("ID�� �ߺ��˴ϴ�");
                    textcolor(WHITE);
                    c1 = 'j';
                    break;
                case 1:
                    system("cls");
                    textcolor(GREEN);
                    printf("���ԵǾ����ϴ�.\n");
                    textcolor(WHITE);
                    c1 = 'a';
                    break;
                }
                strcpy(join, "");
                break;
            case 'o':		// ������ ( ���� ) ȸ������
                w = atoi(word);
                word = strtok(NULL, "@");
                switch (w) {
                case 0:
                    textcolor(RED);
                    printf("ID�� �ߺ��˴ϴ�");
                    textcolor(WHITE);
                    c1 = 'j';
                    break;
                case 1:
                    system("cls");
                    textcolor(GREEN);
                    printf("���ԵǾ����ϴ�.\n");
                    textcolor(WHITE);
                    c1 = 'a';
                    break;
                }
                strcpy(join, "");
                break;
            case 'f':		// ���� ��� Ȯ�� 1 ( ������Ϲ�ȣ ��� )
                strcpy(animal.num, strtok(NULL, "@"));
                animal.bd.year = atoi(strtok(NULL, "@"));
                animal.bd.month = atoi(strtok(NULL, "@"));
                animal.bd.day = atoi(strtok(NULL, "@"));
                strcpy(animal.c_id, strtok(NULL, "@"));
                gotoxy(3, q);	printf("%d : %s\n", q2, animal.num);
                q2++;	q += 2;
                strcpy(join, "");
                break;
            case 's':		// ���� ��� Ȯ�� 2 ( ���� ��� ��� )
                strcpy(mr1.num, strtok(NULL, "@"));
                mr1.date.year = atoi(strtok(NULL, "@"));
                mr1.date.month = atoi(strtok(NULL, "@"));
                mr1.date.day = atoi(strtok(NULL, "@"));
                strcpy(mr1.mgName, strtok(NULL, "@"));
                strcpy(mr1.record, strtok(NULL, "@"));
                gotoxy(3, q);	printf("%d : %d-%d-%d\n", q2,
                    mr1.date.year, mr1.date.month, mr1.date.day);
                printf("%s\n", mr1.record);
                q2++;
                q += 4;
                strcpy(join, "");
                break;
            case 'd':		// ���೯¥ Ȯ�� ( �� )
            case 'w':		// ( ���� ) ���� ������ Ȯ��
                strcpy(reser1.c_id, strtok(NULL, "@"));
                strcpy(reser1.mg_id, strtok(NULL, "@"));
                strcpy(reser1.num, strtok(NULL, "@"));
                reser1.date.year = atoi(strtok(NULL, "@"));
                reser1.date.month = atoi(strtok(NULL, "@"));
                reser1.date.day = atoi(strtok(NULL, "@"));
                reser1.date.hour = atoi(strtok(NULL, "@"));
                strcpy(reser1.cord, strtok(NULL, "@"));
                gotoxy(42, q);	printf("%d-%d-%d-%d\n",
                    reser1.date.year, reser1.date.month, reser1.date.day, reser1.date.hour);
                q += 2;
                strcpy(join, "");
                break;
            case 'b':		// ���� ���� Ȯ��
                strcpy(reser1.c_id, strtok(NULL, "@"));
                strcpy(reser1.mg_id, strtok(NULL, "@"));
                strcpy(reser1.num, strtok(NULL, "@"));
                reser1.date.year = atoi(strtok(NULL, "@"));
                reser1.date.month = atoi(strtok(NULL, "@"));
                reser1.date.day = atoi(strtok(NULL, "@"));
                reser1.date.hour = atoi(strtok(NULL, "@"));
                strcpy(reser1.cord, strtok(NULL, "@"));
                gotoxy(3, q);	printf("%d-%d-%d-%d\t%s\n",
                    reser1.date.year, reser1.date.month, reser1.date.day, reser1.date.hour, reser1.num);
                q += 2;
                strcpy(join, "");
                break;
            case 'r':		// ���� ���
                textcolor(GREEN);
                printf("��ϵǾ����ϴ�.");
                textcolor(WHITE);
                break;
            case 'e':		// ����
                w = atoi(word);
                if (w == 0) {
                    printf("������ �ߺ��˴ϴ�.\n");
                    c1 = 'e';
                }
                textcolor(GREEN);
                printf("����Ǿ����ϴ�.");
                textcolor(WHITE);
                break;
            case 'u':		// ����
                textcolor(GREEN);
                printf("���� ����Ǿ����ϴ�");
                textcolor(WHITE);
                break;
            case 'n':		// �������� ���
                textcolor(GREEN);
                printf("��ϵǾ����ϴ�");
                textcolor(WHITE);
                break;
            case 'i':	// �� ���� ����
            case 't':	// ������ ���� ����
                gotoxy(10, 20);
                textcolor(YELLOW);
                printf("����Ǿ����ϴ�");
                break;
            case 'y':		// ������ Ż��
            case 'v':		// �� Ż��
                gotoxy(10, 20);
                textcolor(YELLOW);
                printf("Ż��Ǿ����ϴ�");
                c1 = 'q';
                break;
            case 'q':		// ����
                gotoxy(10, 20);
                printf("����Ǿ����ϴ�");
                closesocket(sock);
                exit(0);
                break;
            }
        }
    }
}