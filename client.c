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
ANIMAL* animal = NULL;
MR* mr = NULL;
MR mr1;
RESER* reser = NULL;
RESER reser1;

char id[ID] ="", pw[PW]="";		// �α����Ϸ��� id, pw
char join[BUF_SIZE]="";             // ������ �����ϰų� ���Ź��� �� ����� ���ڿ�
char animNum[NUM]="";            //  �ݷ������� ��ȣ�� ���� ����

char c = 'a';   // ��� �ڵ�
char c1 = 'a'; // Ŭ���̾�Ʈ ��� �ڵ� 

char rc = 0;	// ���Ź��� ��� �ڵ�
char resercheck;	// ���� ��¥ �ߺ� ����

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
    ANIMAL anim;
    gotoxy(15, 4);
    gets(anim.num);
    gotoxy(15, 6);
    scanf("%d", &anim.bd.year);
    gotoxy(sizeof(anim.bd.year) + 16, 6);
    printf(" - ");
    scanf("%d", &anim.bd.month);
    gotoxy((int)sizeof(anim.bd.month)*3 + 16, 6);
    printf(" - ");
    scanf("%d", &anim.bd.day);
    getchar();
    gotoxy(15, 8);
    gets(anim.c_id);
    animal = &anim;
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
                send(sock, &c, 1, 0);    // ����ڵ� ����
                sprintf(join, "%s@%s", id, pw); //ID�� PW�� join�� ��ġ��
                send(sock, join, strlen(join), 0);  // join ������ ����
                strcpy(join, "");
                break;
            case 'j':  //�� ȸ������
                send(sock, &c, 1, 0);                            // ����ڵ� ����
                sprintf(join, "%s@%s@%s@%s",        // ȭ�����Կ� �Է¹޾Ҵ� �� join�� ��ġ��
                    client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 'o':  //���� ȸ������
                send(sock, &c, 1, 0);                            // ����ڵ� ����
                sprintf(join, "%s@%s@%s@%s@%s",        // ȭ�����Կ� �Է¹޾Ҵ� �� join�� ��ġ��
                    manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 'f':   // ������ Ȯ�� 1
                send(sock, &c, 1, 0);                                // ����ڵ� ����
                send(sock, client.id, strlen(client.id), 0);    // �� ID ������ ����
                break;
            case 's': // ������Ȯ��2
                send(sock, &c, 1, 0);                                    // ����ڵ� ����
                send(sock, animNum, strlen(animNum), 0);// �ݷ����� ��Ϲ�ȣ ������ ����
                break;
            case 'd':   // ���೯¥Ȯ��(��)
            case 'w':   // ���� ������ Ȯ��(����)
            case 'b':   // ���� ����Ȯ��(��)
                send(sock, &c, 1, 0);        // �� ����ڵ� ����
                sprintf(join, "%d@%d@%d@%d",        // date�� ��¥ ���� ��ġ��
                    today.year, today.month, today.day, today.hour);
                send(sock, join, strlen(join), 0);      // date ������ ����
                strcpy(join, "");
                break;
            case 'r':   // ������
                send(sock, &c, 1, 0);        // ����ڵ� ����
                sprintf(join, "%s@%d@%d@%d@%s@%s", 
                    mr->num, mr->date.year, mr->date.month, mr->date.day, mr->mgName, mr->record);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'h':   // ���� ��¥ �ߺ�
                send(sock, &c, 1, 0);
                sprintf(join, "%d@%d@%d@%d",
                    today.year, today.month, today.day, today.hour);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'e':   // ����
            case 'u':   // ����
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%s@%s@%d@%d@%d@%d@%s",
                    reser->c_id, reser->mg_id, reser->num, reser->date.year, reser->date.month, reser->date.day,
                    reser->date.hour, reser->cord);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'n':   // �������� ���
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%d@%d@%d@%s",
                    animal->num, animal->bd.year, animal->bd.month, animal->bd.day, animal->c_id);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'i':       // �� ���� ����
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%s@%s@%s",        // �� ���� ������ �Է¹޾Ҵ� �� join�� ��ġ��
                    client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 't':       // ������ ���� ����
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%s@%s@%s@%s",        // ������ ���� ������ �Է¹޾Ҵ� �� join�� ��ġ��
                    manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join ������ ����
                strcpy(join, "");
                break;
            case 'y':       // ������ Ż��
                send(sock, &c, 1, 0);
                send(sock, manager.id, strlen(manager.id), 0);    // ������ ID ������ ����
                break;
            case 'v':       // �� Ż��
                send(sock, &c, 1, 0);
                send(sock, client.id, strlen(client.id), 0);    // �� ID ������ ����
                break;
            case 'q':
                printf("�����մϴ�.\n");
                closesocket(sock);
                exit(0);
        }
    }
    return 0;
}

unsigned WINAPI RecMsg(void* arg) {// ����send�Լ�
    SOCKET sock = *((SOCKET*)arg);
    int strLen;

    while (1) {//�ݺ�
        recv(sock, &rc, 1, 0);
        if (rc == 0)
            return -1;
        if (rc == 'q') {
            printf("Client : Disconnection\n");
            closesocket(sock);
            exit(0);
        }
        else{
            switch (rc) {
                case 'l':   // �α���
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0: // �ش� ������ ���� ���
                            gotoxy(3, 7);
                            textcolor(RED);
                            printf("���̵� �Ǵ� ��й�ȣ�� �߸� �Է��߽��ϴ�.");
                            textcolor(WHITE);
                            system("pause");
                            c = 'l';
                            break;
                        case 1: // �ش� ������ ���� ���
                            strLen = recv(sock, join, BUF_SIZE - 1, 0);
                            join[strLen] = '\0';
                            strcpy(client.name, strtok(join, "@"));
                            strcpy(client.num, strtok(NULL, "@"));
                            strcpy(client.id, strtok(NULL, "@"));
                            strcpy(client.pw, strtok(NULL, "@"));
                            textcolor(GREEN);
                            printf("�α��� �Ǿ����ϴ�");
                            textcolor(WHITE);
                            c = 'c';
                            break;
                        case 2: // �ش� ������ ������ ( ���� ) )�� ���
                            strLen = recv(sock, join, BUF_SIZE - 1, 0);
                            join[strLen] = '\0';
                            strcpy(manager.name, strtok(join, "@"));
                            strcpy(manager.lo.city, strtok(NULL, "@"));
                            strcpy(manager.lo.dong, strtok(NULL, "@"));
                            strcpy(manager.id, strtok(NULL, "@"));
                            strcpy(manager.pw, strtok(NULL, "@"));
                            textcolor(GREEN);
                            printf("�α��� �Ǿ����ϴ�");
                            textcolor(WHITE);
                            c = 'm';
                            break;
                    }
                    strcpy(join, "");
                    break;
                case 'j':       // �� ȸ������ ���ú��ڵ�
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0:
                            textcolor(RED);
                            printf("ID�� �ߺ��˴ϴ�");
                            textcolor(WHITE);
                            c = 'j';
                        case 1:
                            system("cls");
                            textcolor(GREEN);
                            printf("���ԵǾ����ϴ�.\n");
                            textcolor(WHITE);
                            c = 'a';
                            break;
                    }
                    break;
                case 'o':       // ������ ( ���� ) ȸ������ ���ú��ڵ�
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0:
                            textcolor(RED);
                            printf("ID�� �ߺ��˴ϴ�");
                            textcolor(WHITE);
                            c = 'j';
                        case 1:
                            system("cls");
                            textcolor(GREEN);
                            printf("���ԵǾ����ϴ�.\n");
                            textcolor(WHITE);
                            c = 'a';
                            break;
                    }
                    break;
                case 'f':       // ���� ���Ȯ�� 1 ���ú� �ڵ�
                    while ((strLen = recv(sock, join, BUF_SIZE - 1, 0) != -1)) {
                        join[strLen] = '\0';
                        ANIMAL* seAnim = (ANIMAL*)malloc(sizeof(ANIMAL));
                        strcpy(seAnim->num, strtok(join, "@"));
                        strcpy(seAnim->bd.year, strtok(NULL, "@"));
                        strcpy(seAnim->bd.month, strtok(NULL, "@"));
                        strcpy(seAnim->bd.day, strtok(NULL, "@"));
                        strcpy(seAnim->c_id, strtok(NULL, "@"));
                        seAnim->next = animal;
                        animal = seAnim;
                    }
                    int i = 1;
                    int i2 = 5;
                    ANIMAL* current = animal;
                    while (current != NULL) {
                        gotoxy(4, i2);
                        printf("%d : %s\n\n", i, current->num);
                        i++;
                        i2 += 2;
                        current = current->next;
                    }
                    free(current);
                    strcpy(join, "");
                    break;
                case 's':   // ���� ���Ȯ�� 2 ���ú� �ڵ�
                    while ((strLen = recv(sock, join, BUF_SIZE - 1, 0) != -1)) {
                        join[strLen] = '\0';
                        MR *reMr = (MR*)malloc(sizeof(MR));
                        strcpy(reMr->num, strtok(join, "@"));
                        strcpy(reMr->date.year, strtok(NULL, "@"));
                        strcpy(reMr->date.month, strtok(NULL, "@"));
                        strcpy(reMr->date.day, strtok(NULL, "@"));
                        strcpy(reMr->mgName, strtok(NULL, "@"));
                        strcpy(reMr->record, strtok(NULL, "@"));
                        reMr->next = mr;
                        mr = reMr;
                    }
                    if (mr == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        break;
                    }
                    int j = 1;
                    int j2 = 5;
                    MR* current1 = mr;
                    while (current1 != NULL) {
                        gotoxy(3, j2);
                        printf("%d : %d-%d-%d\n", j,  
                            current1->date.year, current1->date.month, current1->date.day);
                        printf("%s\n", current1->record);
                        j++;
                        j2 += 4;
                        current1 = current1->next;
                    }
                    free(current1);
                    strcpy(join, "");
                    break;
                case 'd':       // ���೯¥Ȯ��(��)
                    while ((strLen = recv(sock, join, BUF_SIZE - 1, 0) != -1)) {
                        join[strLen] = '\0';
                        RESER* reRe = (RESER*)malloc(sizeof(RESER));
                        strcpy(reRe->c_id, strtok(join, "@"));
                        strcpy(reRe->mg_id, strtok(NULL, "@"));
                        strcpy(reRe->num, strtok(NULL, "@"));
                        strcpy(reRe->date.year, strtok(NULL, "@"));
                        strcpy(reRe->date.month, strtok(NULL, "@"));
                        strcpy(reRe->date.day, strtok(NULL, "@"));
                        strcpy(reRe->date.hour, strtok(NULL, "@"));
                        strcpy(reRe->cord, strtok(NULL, "@"));
                        reRe->next = reser;
                        reser = reRe;
                    }
                    RESER* current2 = reser;
                    int o = 5;
                    while (current2 != NULL) {
                        gotoxy(42, o);
                        printf("%d-%d-%d-%d\n\n",
                            current2->date.year, current2->date.month, current2->date.day, current2->date.hour);
                        current2 = current2->next;
                        o++;
                    }
                    free(current2);
                    strcpy(join, "");
                    break;
                case 'w':       // ( ���� ) ���� ������ Ȯ��
                    while ((strLen = recv(sock, join, BUF_SIZE - 1, 0) != -1)) {
                        join[strLen] = '\0';
                        RESER *reRe = (RESER*)malloc(sizeof(RESER));
                        strcpy(reRe->c_id, strtok(join, "@"));
                        strcpy(reRe->mg_id, strtok(NULL, "@"));
                        strcpy(reRe->num, strtok(NULL, "@"));
                        strcpy(reRe->date.year, strtok(NULL, "@"));
                        strcpy(reRe->date.month, strtok(NULL, "@"));
                        strcpy(reRe->date.day, strtok(NULL, "@"));
                        strcpy(reRe->date.hour, strtok(NULL, "@"));
                        strcpy(reRe->cord, strtok(NULL, "@"));
                        reRe->next = reser;
                        reser = reRe;
                    }
                    int k = 5;
                    RESER* current3=reser;
                    while (current3 != NULL) {
                        gotoxy(42, k);
                        printf("%s", current3->c_id);
                        current3 = current3->next;
                        k++;
                    }
                    free(current3);
                    strcpy(join, "");
                    break;
                case 'b':       // ���೻��Ȯ��
                    while ((strLen = recv(sock, join, BUF_SIZE - 1, 0) != -1)) {
                        join[strLen] = '\0';
                        RESER* reRe = (RESER*)malloc(sizeof(RESER));
                        strcpy(reRe->c_id, strtok(join, "@"));
                        strcpy(reRe->mg_id, strtok(NULL, "@"));
                        strcpy(reRe->num, strtok(NULL, "@"));
                        strcpy(reRe->date.year, strtok(NULL, "@"));
                        strcpy(reRe->date.month, strtok(NULL, "@"));
                        strcpy(reRe->date.day, strtok(NULL, "@"));
                        strcpy(reRe->date.hour, strtok(NULL, "@"));
                        strcpy(reRe->cord, strtok(NULL, "@"));
                        reRe->next = reser;
                        reser = reRe;
                    }
                    RESER* current4 = reser;
                    int p = 6;
                    while (current4 != NULL) {
                        gotoxy(3, p);
                        printf("%d-%d-%d-%d\t%s",
                            current4->date.year, current4->date.month, current4->date.day, current4->date.hour,
                            current4->num);
                        p+=2;
                        current4 = current4->next;
                    }
                    free(current4);
                    strcpy(join, "");
                    break;
                case 'r':
                    textcolor(GREEN);
                    printf("��ϵǾ����ϴ�.");
                    textcolor(WHITE);
                    break;
                case 'h':
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0:
                            gotoxy(20, 4);
                            textcolor(RED);
                            printf("���೯¥�� �ߺ��˴ϴ�.");
                            textcolor(WHITE);
                            system("pause");
                            c = 'E';
                            break;
                        case 1:
                            gotoxy(20, 4);
                            textcolor(GREEN);
                            printf("���� �����մϴ�");
                            textcolor(WHITE);
                            break;
                    }
                    break;
                case 'e':
                    textcolor(GREEN);
                    printf("����Ǿ����ϴ�.");
                    textcolor(WHITE);
                    break;
                case 'u':
                    textcolor(GREEN);
                    printf("���� ����Ǿ����ϴ�");
                    textcolor(WHITE);
                    break;
                case 'n':
                    textcolor(GREEN);
                    printf("��ϵǾ����ϴ�");
                    textcolor(WHITE);
                    break;
                case 'i':
                case 't':
                    gotoxy(10, 20);
                    textcolor(YELLOW);
                    printf("����Ǿ����ϴ�");
                    break;
                case 'y':
                case 'v':
                    gotoxy(10, 20);
                    textcolor(YELLOW);
                    printf("Ż��Ǿ����ϴ�");
                    c = 'q';
                    break;
                case 'q':
                    gotoxy(10, 20);
                    printf("����Ǿ����ϴ�");
                    closesocket(sock);
                    exit(0);
                    break;

            }
        }
    }
    return 0;
}

