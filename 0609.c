#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
#include "0609.h"
#include "client.h"


void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;

// ����ȭ�� ����â �׸�ڽ� (����, ����)
void reservationBorder() {
	gotoxy(40, 3);	printf("������������������������������������������������������������");
	gotoxy(40, 4);	printf("��                            ��");
	gotoxy(40, 5);	printf("��                            ��");
	gotoxy(40, 6);	printf("��                            ��");
	gotoxy(40, 7);	printf("��                            ��");
	gotoxy(40, 8);	printf("��                            ��");
	gotoxy(40, 9);	printf("��                            ��");
	gotoxy(40, 10);	printf("��                            ��");
	gotoxy(40, 11);	printf("��                            ��");
	gotoxy(40, 12);	printf("��                            ��");
	gotoxy(40, 13);	printf("��                            ��");
	gotoxy(40, 14);	printf("��                            ��");
	gotoxy(40, 15);	printf("��                            ��");
	gotoxy(40, 16);	printf("��                            ��");
	gotoxy(40, 17);	printf("��                            ��");
	gotoxy(40, 11);	printf("������������������������������������������������������������");
	gotoxy(41, 4); printf("[����]");
}

// ���� ���� Ż�� (����, ����)
void corrInformation() {
	if (c == 'x') {
		gotoxy(3, 1); printf("[���� ���� �� Ż��]");
		gotoxy(3, 3); printf("1. �̸�");
		gotoxy(3, 5); printf("2. PW");
		gotoxy(3, 7); printf("3. ��ȭ��ȣ");
		gotoxy(3, 9); printf("4. Ż��");
	}
	else if (c == 'z') {
		gotoxy(3, 1); printf("[���� ���� �� Ż��]");
		gotoxy(3, 3); printf("1. �̸�");
		gotoxy(3, 5); printf("2. ����");
		gotoxy(3, 7); printf("3. P.W");
		gotoxy(3, 9); printf("4. Ż��");
	}
}

// ���� ��� Ȯ�� (����)
void medicalRecordCheck() {
	myRecode1();
	gotoxy(20, 20);
	printf("> ");
	scanf("%s", animNum);
	getchar();
	myRecode2();
}

// ���� ����ȭ�� (����)
void cuMainScreen() {
	gotoxy(3, 1);
	printf("�����̸�");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	gotoxy(3, 2);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("1. ���� ��� Ȯ��");
	gotoxy(3, 6);
	printf("2. ���� ���� Ȯ��");
	gotoxy(3, 8);
	printf("3. ȸ�� ���� ���� �� Ż��");
	gotoxy(3, 10);
	printf("4. ����");
}

// ���� ����ȭ�� (����)
void mgMainScreen() {
	gotoxy(3, 1);
	printf("������");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	gotoxy(3, 2);
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
	printf("������Ϲ�ȣ: ");
	gotoxy(3, 6);
	printf("���᳻��: ");
}

// ���೻�� ��� (����)
void findReservation() {
	gotoxy(3, 1); printf("���� ����");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("��¥\t\t\t������Ϲ�ȣ");
}
// ���� �Ǵ� ���� ����(����)
void reservOrInocul() {
	gotoxy(3, 1); printf("���� �� ����");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(5, 4); printf("1. ����");
	gotoxy(5, 6); printf("2. ����");
	gotoxy(5, 8); printf(">");
}

// ���� (����)
void reserv() {
	gotoxy(3, 1); printf("����");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("��¥    : ");
	gotoxy(3, 6); printf("���� ID :");
	gotoxy(3, 8); printf("������Ϲ�ȣ : ");
}

// ���� (����)
void inocul() {
	gotoxy(3, 1); printf("����");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("���� ID :");
	gotoxy(3, 6); printf("��¥    : ");
	gotoxy(3, 8); printf("������Ϲ�ȣ : ");
}

// ������� (����)
void addAnimal() {
	gotoxy(3, 1);
	printf("���� ���� ���");
	gotoxy(3, 2);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("��Ϲ�ȣ:");
	gotoxy(3, 6);
	printf("����    :");
	gotoxy(3, 8);
	printf("���� ID :");
}
