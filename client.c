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

char id[ID] ="", pw[PW]="";		// 로그인하려는 id, pw
char join[BUF_SIZE]="";             // 서버로 전달하거나 수신받을 때 사용할 문자열
char animNum[NUM]="";            //  반려동물의 번호를 받을 변수

char c = 'a';   // 목록 코드
char c1 = 'a'; // 클라이언트 목록 코드 

char rc = 0;	// 수신받은 목록 코드
char resercheck;	// 예약 날짜 중복 여부
int q = 5;
int q2 = 1;

int loinNum = 0; // 로그인 확인여부
//int num = 0;


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

// 요구사항 ID : M3-1
void reservationCheck() {   // 예약 날짜 중복 확인
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

// 요구사항 ID : M3
void reservation() {    // 예약
    fflush(stdin);
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

// 요구사항 ID : S1
unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
    SOCKET sock = *((SOCKET*)arg);
    while (1) {
        switch (c) {
            case 'l':   //로그인
                sprintf(join, "%c@%s@%s", id, pw); //ID와 PW를 join에 합치기
                send(sock, join, strlen(join), 0);  // join 서버로 전달
                strcpy(join, "");
                break;
            case 'j':  //고객 회원가입
                sprintf(join, "%c@%s@%s@%s@%s",        // 화원가입에 입력받았던 것 join에 합치기
                    c, client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 'o':  //병원 회원가입
                sprintf(join, "%c@%s@%s@%s@%s@%s",        // 화원가입에 입력받았던 것 join에 합치기
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 'f':   // 진료기록 확인 1
                sprintf(join, "%c@%s", c, client.id);
                send(sock, join, strlen(join), 0);    // 고객 ID 서버로 전달
                break;
            case 's': // 진료기록확인2
                sprintf(join, "%c@%s", c, animNum);
                send(sock, join, strlen(join), 0);    // 고객 ID 서버로 전달break;
            case 'd':   // 예약날짜확인(고객)
            case 'w':   // 오늘 예약자 확인(병원)
            case 'b':   // 예약 내역확인(고객)
                sprintf(join, "%c@%d@%d@%d@%d",        // date에 날짜 정보 합치기
                    c, today.year, today.month, today.day, today.hour);
                send(sock, join, strlen(join), 0);      // date 서버로 전달
                strcpy(join, "");
                break;
            case 'r':   // 진료기록
                sprintf(join, "%c@%s@%d@%d@%d@%s@%s", 
                    c, mr1.num, mr1.date.year, mr1.date.month, mr1.date.day, mr1.mgName, mr1.record);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'e':   // 예약
            case 'u':   // 접종
                sprintf(join, "%c@%s@%s@%s@%d@%d@%d@%d@%s",
                    c, reser1.c_id, reser1.mg_id, reser1.num, reser1.date.year, reser1.date.month, reser1.date.day,
                    reser1.date.hour, reser1.cord);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'n':   // 동물정보 등록
                sprintf(join, "%c@%s@%d@%d@%d@%s",
                    c, animal.num, animal.bd.year, animal.bd.month, animal.bd.day, animal.c_id);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'i':       // 고객 정보 수정
                sprintf(join, "%c@%s@%s@%s@%s",        // 고객 수정 정보에 입력받았던 것 join에 합치기
                    c, client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 't':       // 관리자 정보 수정
                sprintf(join, "%c@%s@%s@%s@%s@%s",        // 관리자 수정 정보에 입력받았던 것 join에 합치기
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 'y':       // 관리자 탈퇴
                sprintf(join, "%c@%s", c, manager.id);
                send(sock, join, strlen(join), 0);    // 관리자 ID 서버로 전달
                break;
            case 'v':       // 고객 탈퇴
                sprintf(join, "%c@%s", c, client.id);
                send(sock, join, strlen(join), 0);    // 고객 ID 서버로 전달
                break;
            case 'q':
                printf("종료합니다.\n");
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
            case 'l':		// 로그인 
                w = atoi(word);
                word = strtok(NULL, "@");
                switch (w) {
                case 0:
                    gotoxy(3, 7);
                    textcolor(RED);
                    printf("아이디 또는 비밀번호를 잘못 입력했습니다.");
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
                    printf("로그인 되었습니다");
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
                    printf("로그인 되었습니다");
                    textcolor(WHITE);
                    c1 = 'm';
                    break;
                }
                strcpy(join, "");
                break;
            case 'j':		// 고객 회원가입
                w = atoi(word);
                word = strtok(NULL, "@");
                switch (w) {
                case 0:
                    textcolor(RED);
                    printf("ID가 중복됩니다");
                    textcolor(WHITE);
                    c1 = 'j';
                    break;
                case 1:
                    system("cls");
                    textcolor(GREEN);
                    printf("가입되었습니다.\n");
                    textcolor(WHITE);
                    c1 = 'a';
                    break;
                }
                strcpy(join, "");
                break;
            case 'o':		// 관리자 ( 병원 ) 회원가입
                w = atoi(word);
                word = strtok(NULL, "@");
                switch (w) {
                case 0:
                    textcolor(RED);
                    printf("ID가 중복됩니다");
                    textcolor(WHITE);
                    c1 = 'j';
                    break;
                case 1:
                    system("cls");
                    textcolor(GREEN);
                    printf("가입되었습니다.\n");
                    textcolor(WHITE);
                    c1 = 'a';
                    break;
                }
                strcpy(join, "");
                break;
            case 'f':		// 진료 기록 확인 1 ( 동물등록번호 출력 )
                strcpy(animal.num, strtok(NULL, "@"));
                animal.bd.year = atoi(strtok(NULL, "@"));
                animal.bd.month = atoi(strtok(NULL, "@"));
                animal.bd.day = atoi(strtok(NULL, "@"));
                strcpy(animal.c_id, strtok(NULL, "@"));
                gotoxy(3, q);	printf("%d : %s\n", q2, animal.num);
                q2++;	q += 2;
                strcpy(join, "");
                break;
            case 's':		// 진료 기록 확인 2 ( 진료 기록 출력 )
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
            case 'd':		// 예약날짜 확인 ( 고객 )
            case 'w':		// ( 병원 ) 오늘 예약자 확인
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
            case 'b':		// 예약 내역 확인
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
            case 'r':		// 진료 기록
                textcolor(GREEN);
                printf("기록되었습니다.");
                textcolor(WHITE);
                break;
            case 'e':		// 예약
                w = atoi(word);
                if (w == 0) {
                    printf("예약이 중복됩니다.\n");
                    c1 = 'e';
                }
                textcolor(GREEN);
                printf("예약되었습니다.");
                textcolor(WHITE);
                break;
            case 'u':		// 접종
                textcolor(GREEN);
                printf("접종 예약되었습니다");
                textcolor(WHITE);
                break;
            case 'n':		// 동물정보 등록
                textcolor(GREEN);
                printf("등록되었습니다");
                textcolor(WHITE);
                break;
            case 'i':	// 고객 정보 수정
            case 't':	// 관리자 정보 수정
                gotoxy(10, 20);
                textcolor(YELLOW);
                printf("변경되었습니다");
                break;
            case 'y':		// 관리자 탈퇴
            case 'v':		// 고객 탈퇴
                gotoxy(10, 20);
                textcolor(YELLOW);
                printf("탈퇴되었습니다");
                c1 = 'q';
                break;
            case 'q':		// 종료
                gotoxy(10, 20);
                printf("종료되었습니다");
                closesocket(sock);
                exit(0);
                break;
            }
        }
    }
}