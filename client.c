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

int loinNum=0; // 로그인 확인여부
int joinNum = 0;
int ee;

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

void beforInterface() {
	int  conti = 1;
	while (conti) {
		switch (c1) {
		case 'a':		//로그인 or 회원가입
			system("cls");
			startInterface();
			switch (n) {
			case 1:			// 로그인
				system("cls");
				fflush(stdin);
				loginInterface();
				gotoxy(3, 10);
				c = 'l';
				if (loinNum == 0) {
					textcolor(RED);
					gotoxy(3, 7);	 printf("아이디 또는 비밀번호를 잘못 입력했습니다.");
					textcolor(WHITE);
					system("pause");
				}
				else if (loinNum == 1) {
					textcolor(GREEN);
					gotoxy(3, 7);	printf("로그인 되었습니다");
					textcolor(WHITE);
					c1 = 'c';
					conti = 0;
				}
				else if (loinNum == 2) {
					textcolor(GREEN);
					gotoxy(3, 7);	printf("로그인 되었습니다");
					textcolor(WHITE);
					c1 = 'm';
					conti = 0;
				}
				break;
			case 2:			//회원가입
				system("cls");
				joinInterface();
				if (n == 1) {
					c1 = 'j';		// 고객 회원가입 창으로 이동
				}
				else if (n == 2) {
					c1 = 'o';		// 병원 회원가입 창으로 이동
				}
				break;
			}
			break;
		case 'j':			//고객 회원가입
			system("cls");
			fflush(stdin);
			joinClientInterface();
			gotoxy(3, 12);
			if (joinNum == 0) {
				textcolor(RED);
				printf("ID가 중복됩니다.\n");
				textcolor(WHITE);
			}
			else
			c = 'j';
			c1 = 'a';
			break;
		case 'o':				//병원 가입
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
		fflush(stdin);				// 전에 있던 버퍼 초기화
		cuMainScreen();			// 고객 메인목록 창
		reservationBorder();	// 예약날짜 칸
		q = 5;
		q2 = 1;
		reservationDate();		// 예약 날짜 확인 ( 다가오는 예약 날짜 )
		gotoxy(3, 12);	printf(">  ");	scanf("%d", &num);
		getchar();
		switch (num) {
		case 1:
			system("cls");
			fflush(stdin);
			medicalRecordCheck();		// 고객 진료 기록 확인 창
			gotoxy(3, 20);
			system("pause");
			//c1 = 'f';				// 진료 기록 확인 창으로 이동
			break;
		case 2:
			system("cls");
			fflush(stdin);
			q = 5;
			q2 = 1;
			findReservation();				// 예약 내역 확인 창
			c = 'b';
			gotoxy(3, 20);
			system("pause");
			// c1 = 'b';				// 예약 내역 확인 창으로 이동
			break;
		case 3:
			system("cls");
			fflush(stdin);
			corrInformation();		// 고객 정보 수정 및 탈퇴 창
			editInformation();		// 정보 수정 및 탈퇴 기능
			system("pause");
			//c1 = 'i';				// 정보 수정 및 탈퇴 창으로 이동
			break;
		case 4:
			c = 'q';				// 종료
			break;
		default:					// 해당 없는 값을 입력 받았을때
			printf("\n\t다시입력\n");
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
		mgMainScreen();		// 관리자( 병원 ) 메인목록 창
		reservationBorder();	// 예약날짜 칸
		q = 5;
		q2 = 1;
		todayReservation();		// 오늘 예약자 확인
		gotoxy(3, 16);	printf(">  ");	scanf("%d", &num);
		getchar();
		switch (num) {
		case 1:							// 진료 기록 창으로 전환
			system("cls");
			fflush(stdin);
			medicalRecord();			// 병원 진료기록 창
			hosptalRecode();			// 병원 진료기록 기능
			gotoxy(3, 20);
			system("pause");
			break;
		case 2:							// 반려동물 등록 창으로 전환
			system("cls");
			fflush(stdin);
			addAnimal();					// 반려동물 등록 창
			animalNum();
			gotoxy(3, 20);
			system("pause");
			break;
		case 3:							// 예약 및 접종 창으로 전환
			system("cls");
			fflush(stdin);
			reservOrInocul();			// 예약 및 접종 창
			n = 0;
			scanf("%d", &n);
			getchar();
			if (n == 1) {
				system("cls");
				fflush(stdin);
				reserv();					// 예약 창
				reservation();				// 예약 정보 입력
				gotoxy(3, 20);
				if (ee == 0) {
					printf("예약이 중복됩니다.\n");
				}
				else {
					textcolor(GREEN);
					printf("예약되었습니다.");
					textcolor(WHITE);
				}
				system("pause");
			}
			else if (n == 2) {
				system("cls");
				fflush(stdin);
				inocul();						// 접종 창
				inoculation();				// 접종 정보 입력
				gotoxy(3, 20);
				system("pause");
			}
			break;
		case 4:							// 환자 진료기록 확인
			system("cls");
			fflush(stdin);
			gotoxy(3, 2);	printf("동물등록번호 : ");	gets(animNum);
			system("cls");
			myRecode2();
			gotoxy(3, 20);
			system("pause");
			c1 = 'm';							// 병원 메인으로 전환
			break;
		case 5:									// 정보 수정 및 탈퇴
			system("cls");
			fflush(stdin);
			corrInformation();		// 정보수정 및 탈퇴 창
			editInformation();		// 정보 수정 및 탈퇴 기능
			system("pause");
			break;
		case 6:									// 종료
			c = 'q';
			break;
		default:
			printf("\n\t다시입력\n");		// 해당 없는 값을 입력 받았을때
			system("pause");
			break;
		}
	}
}