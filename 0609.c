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

// 메인화면 예약창 네모박스 (고객, 병원)
void reservationBorder() {
	gotoxy(40, 3);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(40, 4);	printf("┃                            ┃");
	gotoxy(40, 5);	printf("┃                            ┃");
	gotoxy(40, 6);	printf("┃                            ┃");
	gotoxy(40, 7);	printf("┃                            ┃");
	gotoxy(40, 8);	printf("┃                            ┃");
	gotoxy(40, 9);	printf("┃                            ┃");
	gotoxy(40, 10);	printf("┃                            ┃");
	gotoxy(40, 11);	printf("┃                            ┃");
	gotoxy(40, 12);	printf("┃                            ┃");
	gotoxy(40, 13);	printf("┃                            ┃");
	gotoxy(40, 14);	printf("┃                            ┃");
	gotoxy(40, 15);	printf("┃                            ┃");
	gotoxy(40, 16);	printf("┃                            ┃");
	gotoxy(40, 17);	printf("┃                            ┃");
	gotoxy(40, 11);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(41, 4); printf("[예약]");
}

// 정보 수정 탈퇴 (고객, 병원)
void corrInformation() {
	if (c == 'x') {
		gotoxy(3, 1); printf("[정보 수정 및 탈퇴]");
		gotoxy(3, 3); printf("1. 이름");
		gotoxy(3, 5); printf("2. PW");
		gotoxy(3, 7); printf("3. 전화번호");
		gotoxy(3, 9); printf("4. 탈퇴");
	}
	else if (c == 'z') {
		gotoxy(3, 1); printf("[정보 수정 및 탈퇴]");
		gotoxy(3, 3); printf("1. 이름");
		gotoxy(3, 5); printf("2. 지역");
		gotoxy(3, 7); printf("3. P.W");
		gotoxy(3, 9); printf("4. 탈퇴");
	}
}

// 진료 기록 확인 (고객)
void medicalRecordCheck() {
	myRecode1();
	gotoxy(20, 20);
	printf("> ");
	scanf("%s", animNum);
	getchar();
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
	gotoxy(3, 4);
	printf("1. 진료 기록 확인");
	gotoxy(3, 6);
	printf("2. 예약 내역 확인");
	gotoxy(3, 8);
	printf("3. 회원 정보 수정 및 탈퇴");
	gotoxy(3, 10);
	printf("4. 종료");
}

// 병원 메인화면 (병원)
void mgMainScreen() {
	gotoxy(3, 1);
	printf("병원명");
	gotoxy(40, 1);
	printf("%d-%02d-%02d\n", today.year, today.month, today.day);
	gotoxy(3, 2);
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
	printf("동물등록번호: ");
	gotoxy(3, 6);
	printf("진료내용: ");
}

// 예약내역 출력 (고객)
void findReservation() {
	gotoxy(3, 1); printf("예약 내역");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("날짜\t\t\t동물등록번호");
}
// 예약 또는 접종 선택(병원)
void reservOrInocul() {
	gotoxy(3, 1); printf("예약 및 접종");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(5, 4); printf("1. 예약");
	gotoxy(5, 6); printf("2. 접종");
	gotoxy(5, 8); printf(">");
}

// 예약 (병원)
void reserv() {
	gotoxy(3, 1); printf("예약");
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4); printf("날짜    : ");
	gotoxy(3, 6); printf("고객 ID :");
	gotoxy(3, 8); printf("동물등록번호 : ");
}

// 접종 (병원)
void inocul() {
	gotoxy(3, 1); printf("접종");
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
	printf("동물 정보 등록");
	gotoxy(3, 2);
	for (int i = 0; i < 50; i++) {
		printf("-");
	}
	gotoxy(3, 4);
	printf("등록번호:");
	gotoxy(3, 6);
	printf("생일    :");
	gotoxy(3, 8);
	printf("고객 ID :");
}

