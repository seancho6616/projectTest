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
ANIMAL* animal = NULL;
MR* mr = NULL;
MR mr1;
RESER* reser = NULL;
RESER reser1;

char id[ID] ="", pw[PW]="";		// 로그인하려는 id, pw
char join[BUF_SIZE]="";             // 서버로 전달하거나 수신받을 때 사용할 문자열
char animNum[NUM]="";            //  반려동물의 번호를 받을 변수

char c = 'a';   // 목록 코드
char c1 = 'a'; // 클라이언트 목록 코드 

char rc = 0;	// 수신받은 목록 코드
char resercheck;	// 예약 날짜 중복 여부

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
                send(sock, &c, 1, 0);    // 목록코드 전달
                sprintf(join, "%s@%s", id, pw); //ID와 PW를 join에 합치기
                send(sock, join, strlen(join), 0);  // join 서버로 전달
                strcpy(join, "");
                break;
            case 'j':  //고객 회원가입
                send(sock, &c, 1, 0);                            // 목록코드 전달
                sprintf(join, "%s@%s@%s@%s",        // 화원가입에 입력받았던 것 join에 합치기
                    client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 'o':  //병원 회원가입
                send(sock, &c, 1, 0);                            // 목록코드 전달
                sprintf(join, "%s@%s@%s@%s@%s",        // 화원가입에 입력받았던 것 join에 합치기
                    manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 'f':   // 진료기록 확인 1
                send(sock, &c, 1, 0);                                // 목록코드 전달
                send(sock, client.id, strlen(client.id), 0);    // 고객 ID 서버로 전달
                break;
            case 's': // 진료기록확인2
                send(sock, &c, 1, 0);                                    // 목록코드 전달
                send(sock, animNum, strlen(animNum), 0);// 반려동물 등록번호 서버로 전달
                break;
            case 'd':   // 예약날짜확인(고객)
            case 'w':   // 오늘 예약자 확인(병원)
            case 'b':   // 예약 내역확인(고객)
                send(sock, &c, 1, 0);        // 각 목록코드 전달
                sprintf(join, "%d@%d@%d@%d",        // date에 날짜 정보 합치기
                    today.year, today.month, today.day, today.hour);
                send(sock, join, strlen(join), 0);      // date 서버로 전달
                strcpy(join, "");
                break;
            case 'r':   // 진료기록
                send(sock, &c, 1, 0);        // 목록코드 전달
                sprintf(join, "%s@%d@%d@%d@%s@%s", 
                    mr->num, mr->date.year, mr->date.month, mr->date.day, mr->mgName, mr->record);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'h':   // 예약 날짜 중복
                send(sock, &c, 1, 0);
                sprintf(join, "%d@%d@%d@%d",
                    today.year, today.month, today.day, today.hour);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'e':   // 예약
            case 'u':   // 접종
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%s@%s@%d@%d@%d@%d@%s",
                    reser->c_id, reser->mg_id, reser->num, reser->date.year, reser->date.month, reser->date.day,
                    reser->date.hour, reser->cord);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'n':   // 동물정보 등록
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%d@%d@%d@%s",
                    animal->num, animal->bd.year, animal->bd.month, animal->bd.day, animal->c_id);
                send(sock, join, strlen(join), 0);
                strcpy(join, "");
                break;
            case 'i':       // 고객 정보 수정
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%s@%s@%s",        // 고객 수정 정보에 입력받았던 것 join에 합치기
                    client.name, client.num, client.id, client.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 't':       // 관리자 정보 수정
                send(sock, &c, 1, 0);
                sprintf(join, "%s@%s@%s@%s@%s",        // 관리자 수정 정보에 입력받았던 것 join에 합치기
                    manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, join, strlen(join), 0);          // join 서버로 전달
                strcpy(join, "");
                break;
            case 'y':       // 관리자 탈퇴
                send(sock, &c, 1, 0);
                send(sock, manager.id, strlen(manager.id), 0);    // 관리자 ID 서버로 전달
                break;
            case 'v':       // 고객 탈퇴
                send(sock, &c, 1, 0);
                send(sock, client.id, strlen(client.id), 0);    // 고객 ID 서버로 전달
                break;
            case 'q':
                printf("종료합니다.\n");
                closesocket(sock);
                exit(0);
        }
    }
    return 0;
}

unsigned WINAPI RecMsg(void* arg) {// 소켓send함수
    SOCKET sock = *((SOCKET*)arg);
    int strLen;

    while (1) {//반복
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
                case 'l':   // 로그인
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0: // 해당 정보가 없을 경우
                            gotoxy(3, 7);
                            textcolor(RED);
                            printf("아이디 또는 비밀번호를 잘못 입력했습니다.");
                            textcolor(WHITE);
                            system("pause");
                            c = 'l';
                            break;
                        case 1: // 해당 정보가 고객일 경우
                            strLen = recv(sock, join, BUF_SIZE - 1, 0);
                            join[strLen] = '\0';
                            strcpy(client.name, strtok(join, "@"));
                            strcpy(client.num, strtok(NULL, "@"));
                            strcpy(client.id, strtok(NULL, "@"));
                            strcpy(client.pw, strtok(NULL, "@"));
                            textcolor(GREEN);
                            printf("로그인 되었습니다");
                            textcolor(WHITE);
                            c = 'c';
                            break;
                        case 2: // 해당 정보가 관리자 ( 병원 ) )일 경우
                            strLen = recv(sock, join, BUF_SIZE - 1, 0);
                            join[strLen] = '\0';
                            strcpy(manager.name, strtok(join, "@"));
                            strcpy(manager.lo.city, strtok(NULL, "@"));
                            strcpy(manager.lo.dong, strtok(NULL, "@"));
                            strcpy(manager.id, strtok(NULL, "@"));
                            strcpy(manager.pw, strtok(NULL, "@"));
                            textcolor(GREEN);
                            printf("로그인 되었습니다");
                            textcolor(WHITE);
                            c = 'm';
                            break;
                    }
                    strcpy(join, "");
                    break;
                case 'j':       // 고객 회원가입 리시브코드
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0:
                            textcolor(RED);
                            printf("ID가 중복됩니다");
                            textcolor(WHITE);
                            c = 'j';
                        case 1:
                            system("cls");
                            textcolor(GREEN);
                            printf("가입되었습니다.\n");
                            textcolor(WHITE);
                            c = 'a';
                            break;
                    }
                    break;
                case 'o':       // 관리자 ( 병원 ) 회원가입 리시브코드
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0:
                            textcolor(RED);
                            printf("ID가 중복됩니다");
                            textcolor(WHITE);
                            c = 'j';
                        case 1:
                            system("cls");
                            textcolor(GREEN);
                            printf("가입되었습니다.\n");
                            textcolor(WHITE);
                            c = 'a';
                            break;
                    }
                    break;
                case 'f':       // 진료 기록확인 1 리시브 코드
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
                case 's':   // 진료 기록확인 2 리시브 코드
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
                case 'd':       // 예약날짜확인(고객)
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
                case 'w':       // ( 병원 ) 오늘 예약자 확인
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
                case 'b':       // 예약내역확인
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
                    printf("기록되었습니다.");
                    textcolor(WHITE);
                    break;
                case 'h':
                    recv(sock, &loinNum, 1, 0);
                    switch (loinNum) {
                        case 0:
                            gotoxy(20, 4);
                            textcolor(RED);
                            printf("예약날짜가 중복됩니다.");
                            textcolor(WHITE);
                            system("pause");
                            c = 'E';
                            break;
                        case 1:
                            gotoxy(20, 4);
                            textcolor(GREEN);
                            printf("예약 가능합니다");
                            textcolor(WHITE);
                            break;
                    }
                    break;
                case 'e':
                    textcolor(GREEN);
                    printf("예약되었습니다.");
                    textcolor(WHITE);
                    break;
                case 'u':
                    textcolor(GREEN);
                    printf("접종 예약되었습니다");
                    textcolor(WHITE);
                    break;
                case 'n':
                    textcolor(GREEN);
                    printf("등록되었습니다");
                    textcolor(WHITE);
                    break;
                case 'i':
                case 't':
                    gotoxy(10, 20);
                    textcolor(YELLOW);
                    printf("변경되었습니다");
                    break;
                case 'y':
                case 'v':
                    gotoxy(10, 20);
                    textcolor(YELLOW);
                    printf("탈퇴되었습니다");
                    c = 'q';
                    break;
                case 'q':
                    gotoxy(10, 20);
                    printf("종료되었습니다");
                    closesocket(sock);
                    exit(0);
                    break;

            }
        }
    }
    return 0;
}

