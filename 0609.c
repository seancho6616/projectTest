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
	gotoxy(3, 1);	printf("1. 로그인");
	gotoxy(3, 3);	printf("2. 회원가입");
	gotoxy(3, 5);	printf(">  ");	scanf("%d", &n);
	getchar();
}

void joinInterface() {
	gotoxy(3, 1);	printf("[회원가입]");
	gotoxy(3, 3);	printf("1. 고객");
	gotoxy(3, 5);	printf("2. 병원");
	gotoxy(3, 7);	printf(">  ");	scanf("%d", &n);
	getchar();
}

void joinClientInterface() {
	gotoxy(3, 1);		printf("[고객] 회원가입");
	gotoxy(3, 3);		printf("ID :");
	gotoxy(3, 5);		printf("P.W :");
	gotoxy(3, 7);		printf("이름 :");
	gotoxy(3, 9);		printf("전화번호 :");
	gotoxy(15, 3);	gets(client.id);
	gotoxy(15, 5);	gets(client.pw);
	gotoxy(15, 7);	gets(client.name);
	gotoxy(15, 9);	gets(client.num);
}

void joinManagerInterface() {
	gotoxy(3, 1);		printf("[병원] 회원가입");
	gotoxy(3, 3);		printf("ID :");
	gotoxy(3, 5);		printf("P.W :");
	gotoxy(3, 7);		printf("병원명 :");
	gotoxy(3, 9);		printf("지역 :");
	gotoxy(3, 10);	printf("(시, 동)");
	gotoxy(15, 3);  gets(manager.id);
	gotoxy(15, 5);  gets(manager.pw);
	gotoxy(15, 7);  gets(manager.name);
	gotoxy(15, 9);  gets(manager.lo.city);
	gotoxy(25, 9);	 printf(" 시\t");
	gets(manager.lo.dong); gotoxy((int)strlen(manager.lo.dong) * 2 + 25, 9); 
	printf("동\n");
}

void loginInterface() {
	gotoxy(3, 1);	printf("[로그인]");
	gotoxy(3, 3);	printf("ID :");
	gotoxy(3, 5);	printf("P.W :\n");
	gotoxy(10, 3);   gets(id);         // ID 입력
	gotoxy(10, 5);   gets(pw);         // PW 입력
}

// 메인화면 예약창 네모박스 (고객, 병원)
void reservationBorder() {
	gotoxy(40, 3);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	for (int i = 4; i <= 19; i++) {
		gotoxy(40, i);	printf("┃                            ┃");
	}
	gotoxy(40, 20);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(41, 4); printf("[예약]");
}

// 정보 수정 탈퇴 (고객, 병원)
void corrInformation() {
	if (c1 == 'i') {
		gotoxy(3, 1); printf("[정보 수정 및 탈퇴]");
		gotoxy(3, 3); printf("1. 이름");
		gotoxy(3, 5); printf("2. PW");
		gotoxy(3, 7); printf("3. 전화번호");
		gotoxy(3, 9); printf("4. 탈퇴");
	}
	else if (c1 == 't') {
		gotoxy(3, 1); printf("[정보 수정 및 탈퇴]");
		gotoxy(3, 3); printf("1. 이름");
		gotoxy(3, 5); printf("2. 지역");
		gotoxy(3, 7); printf("3. P.W");
		gotoxy(3, 9); printf("4. 탈퇴");
	}
}

// 진료 기록 확인 (고객)
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

// 고객 메인화면 (고객)
void cuMainScreen() {
	gotoxy(3, 1);
	printf("고객이름");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	gotoxy(3, 2);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);	printf("1. 진료 기록 확인");
	gotoxy(3, 6);	printf("2. 예약 내역 확인");
	gotoxy(3, 8);	printf("3. 회원 정보 수정 및 탈퇴");
	gotoxy(3, 10);	printf("4. 종료");
}

// 병원 메인화면 (병원)
void mgMainScreen() {
	gotoxy(3, 1);
	printf("병원명\n");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("1. 진료 기록");
	gotoxy(3, 6);
	printf("2. 동물등록번호 등록");
	gotoxy(3, 8);
	printf("3. 진료예약 및 접종");
	gotoxy(3, 10);
	printf("4. 환자 기록 확인");
	gotoxy(3, 12);
	printf("5. 회원 정보 수정 및 탈퇴");
	gotoxy(3, 14);
	printf("6. 종료");
}

// 진료 기록 입력 (병원)
void medicalRecord() {
	gotoxy(3, 1);
	printf("진료기록");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	gotoxy(3, 2);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("동물등록번호 : ");
	gotoxy(3, 6);
	printf("진료내용 : ");
}

// 예약내역 출력 (고객)
void findReservation() {
	gotoxy(3, 1); printf("예약 내역\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("날짜\t\t\t동물등록번호\n\n");
}
// 예약 또는 접종 선택(병원)
void reservOrInocul() {
	gotoxy(3, 1); printf("예약 및 접종\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(5, 4); printf("1. 예약");
	gotoxy(5, 6); printf("2. 접종");
	gotoxy(5, 8); printf("> ");
}

// 예약 (병원)
void reserv() {
	gotoxy(3, 1); printf("예약\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("날짜    : ");
	gotoxy(3, 6); printf("고객 ID :");
	gotoxy(3, 8); printf("동물등록번호 : ");
}

// 접종 (병원)
void inocul() {
	gotoxy(3, 1); printf("접종\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("고객 ID :");
	gotoxy(3, 6); printf("날짜    : ");
	gotoxy(3, 8); printf("동물등록번호 : ");
}

// 동물등록 (병원)
void addAnimal() {
	gotoxy(3, 1);
	printf("동물 정보 등록\n");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("등록번호 :");
	gotoxy(3, 6);
	printf("생일     :");
	gotoxy(3, 8);
	printf("고객 ID  :");
}

