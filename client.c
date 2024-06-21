#define _WINSOCK_DEPRECATED_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 소켓관련 경고 무시용
#define _CRT_SECURE_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 입력관련 경고 무시용
#pragma comment(lib, "ws2_32")  //비주얼스튜디오 환경에서 개발시 소켓 라이브러리 지정용#pragma warning(disable:4996)
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

#define ID 20			// ID 배열크기
#define PW 20			// PW 배열크기
#define MAX 12			// 이름 배열크기
#define NUM 16			// 번호(전화번호, 등록번호) 배열크기
#define RECORD 500		// 진료 기록 배열크기
#define LO 6			// 지역과 코드 배열크기
#define BUF_SIZE 700


TODAY today;
CLIENT client;
MANAGER manager;
ANIMAL animal;
MR mr1;
RESER reser1;



char animNum[NUM]="";            //  반려동물의 번호를 받을 변수

//char c;   // 목록 코드
char c1 = 'a'; // 클라이언트 목록 코드 

char rc = 0;	// 수신받은 목록 코드
char resercheck;	// 예약 날짜 중복 여부
int q = 5;      //  반복 출력 시 사용할 Y값
int q2 = 1;     // 출력 정보 카운트

int loinNum; // 로그인 확인여부

// 위치 이동 함수
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//요구사항 ID : P1
void todayDate() {     // 오늘의 날짜 함수
    time_t* curr;
    curr = time(NULL);
    struct tm* d;
    d = localtime(&curr);
    today.year = d->tm_year + 1900; // 1900을 더함으로써 
    today.month = d->tm_mon+1;      // 0~11임으로 +1
    today.day = d->tm_mday;             // 달의 일수 
    today.hour = d->tm_hour;            // 현제 시각 0~23
}

// 요구사항 ID : P2
void myRecode1() {  // 해당 고객 반려동물 목록 불러오는 함수
    c = 'f';
    gotoxy(3, 1);                           // 위치이동
    printf("진료 기록 확인\n");         
    for (int i = 0; i < 50; i++) {
        printf("-");
    }
    gotoxy(2, 3);
    printf(" 명단\n\n");
}

// 요구사항 ID : P3
void myRecode2() {  // 해당 반려동물 진료 기록 부르는 함수
    c = 's';
    gotoxy(3, 1);                           // 위치 이동
    printf("진료 기록 확인\n");
    for (int i = 0; i < 50; i++) {
        printf("-");
    }
    gotoxy(3, 3);
    printf("%s\n", animNum);    // 입력 받은 동물등록번호 출력
}


// 요구사항 ID : C1
void reservationDate() {    // 예약 날짜 확인(다가오는 예약 날짜)
    c = 'd';
}

// 요구사항 ID : P4
void editInformation() {    // 정보수정 및 탈퇴
    
    int inputnum;
    switch (c1) {        // 고객과 관리자(병원) 구분
        case 't':                   // 관리자(병원)
            gotoxy(8,20);      // 위치 이동
            printf("> ");            // 선택하고자 하는 것을 입력 위치 확인
            scanf("%d", &inputnum); // 입력( 선택하고자 하는 것을)
            getchar();
            switch (inputnum) {
                case 1: // 병원명 변경
                    // 위치 선정
                    fflush(stdin); 
                    gotoxy(5, 4);
                    printf("> ");
                    gets(manager.name); // 변경하고자 하는 병원명 입력
                    gotoxy(10, 13);
                    c = 't';                        // 변경한 것을 서버로 전달하기 위하여
                    break;
                case 2: // 지역 변경
                    // 위치 선정
                    fflush(stdin); 
                    gotoxy(5, 6);
                    printf("> ");
                    printf("시 : ");
                    gets(manager.lo.city);  // 변경하고자 하는 시 입력
                    gotoxy(15, 6);
                    printf("\t동 : ");
                    gets(manager.lo.dong);  // 변경하고자 하는 동 입력
                    c = 't';                        // 변경한 것을 서버로 전달하기 위하여
                    gotoxy(10, 13);
                    break;
                case 3: // 비번변경
                    // 위치 선정
                    fflush(stdin); 
                    gotoxy(5, 8);
                    printf("> ");
                    gets(manager.pw);           // 변경하고자 하는 PW 입력
                    c = 't';                            // 변경한 것을 서버로 전달하기 위하여
                    gotoxy(10, 13);
                    break;
                case 4: // 탈퇴
                    c = 'y';
                    break;
            }
            break;
        case 'i':                       // 고객
            gotoxy(3, 20);         // 위치 이동
            printf("> ");                   // 선택하고자 하는 것을 입력 위치 확인
            scanf("%d", &inputnum); // 입력( 선택하고자 하는 것을 )
            getchar();
            switch (inputnum) {
                case 1: // 고객명 변경
                    gotoxy(5, 4);
                    printf("> ");
                    gets(client.name);              // 변경하고자 하는 이름 입력
                    gotoxy(10, 13);
                    c = 'i';
                    break;
                case 2: // 전화번호 변경
                    gotoxy(5, 6);
                    printf("> ");
                    gets(client.num);                   // 변경하고자 하는 번호 입력
                    gotoxy(10, 13);
                    c = 'i';
                    break;
                case 3: // 비번변경
                    gotoxy(5, 8);
                    printf("> ");
                    gets(client.pw);                    // 변경하고자 하는 PW 입력
                    gotoxy(10, 13);
                    c = 'i';
                    break;
                case 4: // 탈퇴
                    c = 'v';
                    break;
            }
           break;
    }
}


// 요구사항 ID : M1
void todayReservation() {   // 오늘 예약자 확인 ( 관리자 ( 병원 ) )
    c = 'w';
}

// 요구사항 ID : M2
void hosptalRecode() {     // 진료기록
    mr1.date.year = today.year;                     // 날짜는 자동 저장
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

// 요구사항 ID : M4
void animalNum() {  // 반려동물 등록
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

// 요구사항 ID : M3
void reservation() {    // 예약
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
    strcpy(reser1.cord, "r");        // 예약이라는 것을 확인하기 위한 코드
    c = 'e';
}

// 요구사항 ID : M4
void inoculation() {    // 접종
    gotoxy(20, 4);
    gets(reser1.c_id);
    gotoxy(20, 8);
    gets(reser1.num);
    strcpy(reser1.mg_id, manager.id);
    strcpy(reser1.cord, "i");        // 접종이라는 것을 확인하기 위한 코드
    reser1.date.year = today.year + 1;
    reser1.date.month = today.month;
    reser1.date.day = today.day;
    reser1.date.hour = 0;
    gotoxy(20, 6);  printf("%d - %d - %d",
        reser1.date.year-1, reser1.date.month, reser1.date.day);
    c = 'u';
}

