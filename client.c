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



char animNum[NUM]="";            //  �ݷ������� ��ȣ�� ���� ����

//char c;   // ��� �ڵ�
char c1 = 'a'; // Ŭ���̾�Ʈ ��� �ڵ� 

char rc = 0;	// ���Ź��� ��� �ڵ�
char resercheck;	// ���� ��¥ �ߺ� ����
int q = 5;      //  �ݺ� ��� �� ����� Y��
int q2 = 1;     // ��� ���� ī��Ʈ

int loinNum=0; // �α��� Ȯ�ο���
int joinNum = 0;
int ee;

// ��ġ �̵� �Լ�
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

// �䱸���� ID : M3
void reservation() {    // ����
    fflush(stdin);
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

void beforInterface() {
	int  conti = 1;
	while (conti) {
		switch (c1) {
		case 'a':		//�α��� or ȸ������
			system("cls");
			startInterface();
			switch (n) {
			case 1:			// �α���
				system("cls");
				fflush(stdin);
				loginInterface();
				gotoxy(3, 10);
				c = 'l';
				if (loinNum == 0) {
					textcolor(RED);
					gotoxy(3, 7);	 printf("���̵� �Ǵ� ��й�ȣ�� �߸� �Է��߽��ϴ�.");
					textcolor(WHITE);
					system("pause");
				}
				else if (loinNum == 1) {
					textcolor(GREEN);
					gotoxy(3, 7);	printf("�α��� �Ǿ����ϴ�");
					textcolor(WHITE);
					c1 = 'c';
					conti = 0;
				}
				else if (loinNum == 2) {
					textcolor(GREEN);
					gotoxy(3, 7);	printf("�α��� �Ǿ����ϴ�");
					textcolor(WHITE);
					c1 = 'm';
					conti = 0;
				}
				break;
			case 2:			//ȸ������
				system("cls");
				joinInterface();
				if (n == 1) {
					c1 = 'j';		// �� ȸ������ â���� �̵�
				}
				else if (n == 2) {
					c1 = 'o';		// ���� ȸ������ â���� �̵�
				}
				break;
			}
			break;
		case 'j':			//�� ȸ������
			system("cls");
			fflush(stdin);
			joinClientInterface();
			gotoxy(3, 12);
			if (joinNum == 0) {
				textcolor(RED);
				printf("ID�� �ߺ��˴ϴ�.\n");
				textcolor(WHITE);
			}
			else
			c = 'j';
			c1 = 'a';
			break;
		case 'o':				//���� ����
			system("cls");
			fflush(stdin);
			joinManagerInterface();
			c = 'o';
			c1 = 'a';
			break;
		}
	}
}

void clientInterface() {
	while (1) {
		system("cls");
		fflush(stdin);				// ���� �ִ� ���� �ʱ�ȭ
		cuMainScreen();			// �� ���θ�� â
		reservationBorder();	// ���೯¥ ĭ
		q = 5;
		q2 = 1;
		reservationDate();		// ���� ��¥ Ȯ�� ( �ٰ����� ���� ��¥ )
		gotoxy(3, 12);	printf(">  ");	scanf("%d", &num);
		getchar();
		switch (num) {
		case 1:
			system("cls");
			fflush(stdin);
			medicalRecordCheck();		// �� ���� ��� Ȯ�� â
			gotoxy(3, 20);
			system("pause");
			//c1 = 'f';				// ���� ��� Ȯ�� â���� �̵�
			break;
		case 2:
			system("cls");
			fflush(stdin);
			q = 5;
			q2 = 1;
			findReservation();				// ���� ���� Ȯ�� â
			c = 'b';
			gotoxy(3, 20);
			system("pause");
			// c1 = 'b';				// ���� ���� Ȯ�� â���� �̵�
			break;
		case 3:
			system("cls");
			fflush(stdin);
			corrInformation();		// �� ���� ���� �� Ż�� â
			editInformation();		// ���� ���� �� Ż�� ���
			system("pause");
			//c1 = 'i';				// ���� ���� �� Ż�� â���� �̵�
			break;
		case 4:
			c = 'q';				// ����
			break;
		default:					// �ش� ���� ���� �Է� �޾�����
			printf("\n\t�ٽ��Է�\n");
			system("pause");
			break;
		}
		num = 0;
		break;
	}
}

void managerInterface() {
	while (1) {
		system("cls");
		fflush(stdin);
		mgMainScreen();		// ������( ���� ) ���θ�� â
		reservationBorder();	// ���೯¥ ĭ
		q = 5;
		q2 = 1;
		todayReservation();		// ���� ������ Ȯ��
		gotoxy(3, 16);	printf(">  ");	scanf("%d", &num);
		getchar();
		switch (num) {
		case 1:							// ���� ��� â���� ��ȯ
			system("cls");
			fflush(stdin);
			medicalRecord();			// ���� ������ â
			hosptalRecode();			// ���� ������ ���
			gotoxy(3, 20);
			system("pause");
			break;
		case 2:							// �ݷ����� ��� â���� ��ȯ
			system("cls");
			fflush(stdin);
			addAnimal();					// �ݷ����� ��� â
			animalNum();
			gotoxy(3, 20);
			system("pause");
			break;
		case 3:							// ���� �� ���� â���� ��ȯ
			system("cls");
			fflush(stdin);
			reservOrInocul();			// ���� �� ���� â
			n = 0;
			scanf("%d", &n);
			getchar();
			if (n == 1) {
				system("cls");
				fflush(stdin);
				reserv();					// ���� â
				reservation();				// ���� ���� �Է�
				gotoxy(3, 20);
				if (ee == 0) {
					printf("������ �ߺ��˴ϴ�.\n");
				}
				else {
					textcolor(GREEN);
					printf("����Ǿ����ϴ�.");
					textcolor(WHITE);
				}
				system("pause");
			}
			else if (n == 2) {
				system("cls");
				fflush(stdin);
				inocul();						// ���� â
				inoculation();				// ���� ���� �Է�
				gotoxy(3, 20);
				system("pause");
			}
			break;
		case 4:							// ȯ�� ������ Ȯ��
			system("cls");
			fflush(stdin);
			gotoxy(3, 2);	printf("������Ϲ�ȣ : ");	gets(animNum);
			system("cls");
			myRecode2();
			gotoxy(3, 20);
			system("pause");
			c1 = 'm';							// ���� �������� ��ȯ
			break;
		case 5:									// ���� ���� �� Ż��
			system("cls");
			fflush(stdin);
			corrInformation();		// �������� �� Ż�� â
			editInformation();		// ���� ���� �� Ż�� ���
			system("pause");
			break;
		case 6:									// ����
			c = 'q';
			break;
		default:
			printf("\n\t�ٽ��Է�\n");		// �ش� ���� ���� �Է� �޾�����
			system("pause");
			break;
		}
	}
}