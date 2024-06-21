#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <time.h>
#include "client.h"
#include "0609.h"

int n = 0;


void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;

void startInterface() {
	gotoxy(3, 1);	printf("1. �α���");
	gotoxy(3, 3);	printf("2. ȸ������");
	gotoxy(3, 5);	printf(">  ");	scanf("%d", &n);
	getchar();
}

void joinInterface() {
	gotoxy(3, 1);	printf("[ȸ������]");
	gotoxy(3, 3);	printf("1. ��");
	gotoxy(3, 5);	printf("2. ����");
	gotoxy(3, 7);	printf(">  ");	scanf("%d", &n);
	getchar();
}

void joinClientInterface() {
	gotoxy(3, 1);		printf("[��] ȸ������");
	gotoxy(3, 3);		printf("ID :");
	gotoxy(3, 5);		printf("P.W :");
	gotoxy(3, 7);		printf("�̸� :");
	gotoxy(3, 9);		printf("��ȭ��ȣ :");
	gotoxy(15, 3);	gets(client.id);
	gotoxy(15, 5);	gets(client.pw);
	gotoxy(15, 7);	gets(client.name);
	gotoxy(15, 9);	gets(client.num);
}

void joinManagerInterface() {
	gotoxy(3, 1);		printf("[����] ȸ������");
	gotoxy(3, 3);		printf("ID :");
	gotoxy(3, 5);		printf("P.W :");
	gotoxy(3, 7);		printf("������ :");
	gotoxy(3, 9);		printf("���� :");
	gotoxy(3, 10);	printf("(��, ��)");
	gotoxy(15, 3);  gets(manager.id);
	gotoxy(15, 5);  gets(manager.pw);
	gotoxy(15, 7);  gets(manager.name);
	gotoxy(15, 9);  gets(manager.lo.city);
	gotoxy(25, 9);	 printf(" ��\t");
	gets(manager.lo.dong); gotoxy((int)strlen(manager.lo.dong) * 2 + 25, 9); 
	printf("��\n");
}

void loginInterface() {
	gotoxy(3, 1);	printf("[�α���]");
	gotoxy(3, 3);	printf("ID :");
	gotoxy(3, 5);	printf("P.W :\n");
	gotoxy(10, 3);   gets(id);         // ID �Է�
	gotoxy(10, 5);   gets(pw);         // PW �Է�
}

// ����ȭ�� ����â �׸�ڽ� (��, ����)
void reservationBorder() {
	gotoxy(40, 3);	printf("������������������������������������������������������������");
	for (int i = 4; i <= 19; i++) {
		gotoxy(40, i);	printf("��                            ��");
	}
	gotoxy(40, 20);	printf("������������������������������������������������������������");
	gotoxy(41, 4); printf("[����]");
}

// ���� ���� Ż�� (��, ����)
void corrInformation() {
	if (c1 == 'i') {
		gotoxy(3, 1); printf("[���� ���� �� Ż��]");
		gotoxy(3, 3); printf("1. �̸�");
		gotoxy(3, 5); printf("2. PW");
		gotoxy(3, 7); printf("3. ��ȭ��ȣ");
		gotoxy(3, 9); printf("4. Ż��");
	}
	else if (c1 == 't') {
		gotoxy(3, 1); printf("[���� ���� �� Ż��]");
		gotoxy(3, 3); printf("1. �̸�");
		gotoxy(3, 5); printf("2. ����");
		gotoxy(3, 7); printf("3. P.W");
		gotoxy(3, 9); printf("4. Ż��");
	}
}

// ���� ��� Ȯ�� (��)
void medicalRecordCheck() {
	q = 5;
	q2 = 1;
	myRecode1();
	gotoxy(20, 20);
	printf("> ");
	scanf("%s", &animNum);
	getchar();
	q = 5;
	q2 = 1;
	system("cls");
	myRecode2();
}

// �� ����ȭ�� (��)
void cuMainScreen() {
	gotoxy(3, 1);
	printf("���̸�");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	gotoxy(3, 2);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);	printf("1. ���� ��� Ȯ��");
	gotoxy(3, 6);	printf("2. ���� ���� Ȯ��");
	gotoxy(3, 8);	printf("3. ȸ�� ���� ���� �� Ż��");
	gotoxy(3, 10);	printf("4. ����");
}

// ���� ����ȭ�� (����)
void mgMainScreen() {
	gotoxy(3, 1);
	printf("������\n");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("1. ���� ���");
	gotoxy(3, 6);
	printf("2. ������Ϲ�ȣ ���");
	gotoxy(3, 8);
	printf("3. ���Ό�� �� ����");
	gotoxy(3, 10);
	printf("4. ȯ�� ��� Ȯ��");
	gotoxy(3, 12);
	printf("5. ȸ�� ���� ���� �� Ż��");
	gotoxy(3, 14);
	printf("6. ����");
}

// ���� ��� �Է� (����)
void medicalRecord() {
	gotoxy(3, 1);
	printf("������");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	gotoxy(3, 2);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("������Ϲ�ȣ : ");
	gotoxy(3, 6);
	printf("���᳻�� : ");
}

// ���೻�� ��� (��)
void findReservation() {
	gotoxy(3, 1); printf("���� ����\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("��¥\t\t\t������Ϲ�ȣ\n\n");
}
// ���� �Ǵ� ���� ����(����)
void reservOrInocul() {
	gotoxy(3, 1); printf("���� �� ����\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(5, 4); printf("1. ����");
	gotoxy(5, 6); printf("2. ����");
	gotoxy(5, 8); printf("> ");
}

// ���� (����)
void reserv() {
	gotoxy(3, 1); printf("����\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("��¥    : ");
	gotoxy(3, 6); printf("�� ID :");
	gotoxy(3, 8); printf("������Ϲ�ȣ : ");
}

// ���� (����)
void inocul() {
	gotoxy(3, 1); printf("����\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("�� ID :");
	gotoxy(3, 6); printf("��¥    : ");
	gotoxy(3, 8); printf("������Ϲ�ȣ : ");
}

// ������� (����)
void addAnimal() {
	gotoxy(3, 1);
	printf("���� ���� ���\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("��Ϲ�ȣ :");
	gotoxy(3, 6);
	printf("����     :");
	gotoxy(3, 8);
	printf("�� ID  :");
}

