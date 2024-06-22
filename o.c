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
#include "0609.h"
#include "client.h"

#define ID 20			// ID 배열크기
#define PW 20			// PW 배열크기
#define MAX 12			// 이름 배열크기
#define NUM 16			// 번호(전화번호, 등록번호) 배열크기
#define RECORD 500		// 진료 기록 배열크기
#define LO 6			// 지역과 코드 배열크기
#define BUF_SIZE 700

char msg[BUF_SIZE] = "";
char result[BUF_SIZE] = "";

unsigned WINAPI SendMsg(void* arg);		// 서버 전달 함수

unsigned WINAPI RecMsg(void* arg);		// 서버 수신 함수

void main() {
	
	char serverIp[100];
	int  portNum;
	todayDate();
	strcpy(serverIp, "192.168.0.9");	// 임의로 설정
	portNum = 55555;		// 임의로 설정 " 55555 "

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);
	serverAddr.sin_port = htons(portNum);

	connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);		//메시지 전송용 쓰레드가 실행된다.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecMsg, (void*)&sock, 0, NULL);		//메시지 수신용 쓰레드가 실행된다.

    beforInterface();
    printf("%d", loinNum);
    switch (loinNum) {
        case 1:
            clientInterface();
            break;
        case 2:
            managerInterface();
            break;
    }


	//while (1) {
	//	switch (c1) {
	//		case 'a':		//로그인 or 회원가입
	//			system("cls");
 //               startInterface();
	//			switch (n) {
	//				case 1:			// 로그인
	//					system("cls");
 //                       fflush(stdin);
 //                       loginInterface();
	//					gotoxy(3, 10);
 //                       printf("%s\n%s\n", id, pw);
 //                       c = 'l';
 //                       printf("%c", c);
 //                       sprintf(animNum, "%c@%s@%s",'c', id, pw);
 //                       printf("%s\n", animNum);
	//					//c1 = 'm'; 테스트용
	//					break;
	//				case 2:			//회원가입
	//					system("cls");
 //                       joinInterface();
	//					if (n == 1) {
	//						c1 = 'j';		// 고객 회원가입 창으로 이동
	//					}
	//					else if (n == 2) {
	//						c1 = 'o';		// 병원 회원가입 창으로 이동
	//					}
	//					break;
	//			}
	//			break;
	//		case 'j':			//고객 회원가입
	//			system("cls");
	//			fflush(stdin);
 //               joinClientInterface();
	//			gotoxy(3, 12);
	//			c = 'j';
	//			system("pause");
	//			c1 = 'a';
	//			break;
	//		case 'o':				//병원 가입
	//			system("cls");
	//			fflush(stdin);
 //               joinManagerInterface();
	//			
	//			gotoxy(3, 12);
	//			c = 'o'; 
	//			system("pause");
	//			c1 = 'a';
	//			break;
	//		// 고객메인
	//		case 'c':
	//			system("cls");
	//			fflush(stdin);				// 전에 있던 버퍼 초기화
	//			cuMainScreen();			// 고객 메인목록 창
	//			reservationBorder();	// 예약날짜 칸
	//			q = 5;
	//			q2 = 1; 
	//			reservationDate();		// 예약 날짜 확인 ( 다가오는 예약 날짜 )
	//			gotoxy(3, 12);	printf(">  ");	scanf("%d", &num);
	//			getchar();
	//			switch (num) {
	//				case 1:
	//					c1 = 'f';				// 진료 기록 확인 창으로 이동
	//					break;
	//				case 2:
	//					c1 = 'b';				// 예약 내역 확인 창으로 이동
	//					break;
	//				case 3:
	//					c1 = 'i';				// 정보 수정 및 탈퇴 창으로 이동
	//					break;
	//				case 4:
	//					c = 'q';				// 종료
	//					c1 = 'q';
	//					break;
	//				default:					// 해당 없는 값을 입력 받았을때
	//					printf("\n\t다시입력\n");
	//					system("pause");
	//					break;
	//			}
	//			num = 0;
	//			break;

	//		case 'f':			//진료기록확인
	//			system("cls");
	//			fflush(stdin);
	//			medicalRecordCheck();		// 고객 진료 기록 확인 창
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'c';								// 메인으로 전환
	//			break;
	//		case 'b':
	//			system("cls");
	//			fflush(stdin);
	//			q = 5;
	//			q2 = 1; 
	//			findReservation();				// 예약 내역 확인 창
	//			c = 'b';
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'c';
	//			break;
	//		case 'i':			//고객정보수정및탈퇴
	//			system("cls");
	//			fflush(stdin);
	//			corrInformation();		// 고객 정보 수정 및 탈퇴 창
	//			editInformation();		// 정보 수정 및 탈퇴 기능
	//			system("pause");
	//			c1 = 'c';						// 메인으로 전환
	//			break;
	//		case 'm':		//병원메인
	//			system("cls");
	//			fflush(stdin);
	//			mgMainScreen();		// 관리자( 병원 ) 메인목록 창
	//			reservationBorder();	// 예약날짜 칸
	//			q = 5;
	//			q2 = 1;
	//			todayReservation();		// 오늘 예약자 확인
	//			gotoxy(3, 16);	printf(">  ");	scanf("%d", &num);
	//			getchar();
	//			switch (num) {
	//			case 1:							// 진료 기록 창으로 전환
	//				c1 = 'r';
	//				break;
	//			case 2:							// 반려동물 등록 창으로 전환
	//				c1 = 'n';
	//				break;
	//			case 3:							// 예약 및 접종 창으로 전환
	//				c1 = 'p';
	//				break;
	//			case 4:							// 환자 진료기록 확인
	//				system("cls");
	//				fflush(stdin);
	//				gotoxy(3, 2);	printf("동물등록번호 : ");	gets(animNum);
	//				system("cls");
	//				myRecode2();
	//				gotoxy(3, 20);
	//				system("pause");
	//				c1 = 'm';							// 병원 메인으로 전환
	//				break;
	//			case 5:									// 정보 수정 및 탈퇴
	//				c1 = 't';
	//				break;
	//			case 6:									// 종료
	//				c = 'q';
	//				c1 = 'q';
	//				break;
	//			default:
	//				printf("\n\t다시입력\n");		// 해당 없는 값을 입력 받았을때
	//				system("pause");
	//				break;
	//			}
	//			break;
	//		case 'r':			//병원진료기록
	//			system("cls");
	//			fflush(stdin);
	//			medicalRecord();			// 병원 진료기록 창
	//			hosptalRecode();			// 병원 진료기록 기능
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// 병원 메인으로 전환
	//			break;
	//		case 'n':		//반려동물 등록
	//			system("cls");
	//			fflush(stdin);
	//			addAnimal();					// 반려동물 등록 창
	//			animalNum();
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// 병원 메인으로 전환
	//			break;
	//		case 'p':			//진료예약및접좁
	//			system("cls");
	//			fflush(stdin);
	//			reservOrInocul();			// 예약 및 접종 창
	//			n = 0;
	//			scanf("%d", &n);
	//			getchar();
	//			if (n == 1) 
	//				c1 = 'e';						// n==1 이면 예약창으로
	//			else if (n == 2) 
	//				c1 = 'u';						// n==2이면 접종창으로 
	//			break;

	//			//예약
	//		case 'e':
	//			system("cls");
	//			fflush(stdin);
	//			reserv();					// 예약 창
	//			reservation();				// 예약 정보 입력
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// 병원 메인으로 전환
	//			break;

	//			//접종
	//		case 'u':
	//			system("cls");
	//			fflush(stdin);
	//			inocul();						// 접종 창
	//			inoculation();				// 접종 정보 입력
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// 병원 메인으로 전환
	//			break;

	//			//병원 정보수정 및 탈퇴
	//		case 't':
	//			system("cls");
	//			fflush(stdin);
	//			corrInformation();		// 정보수정 및 탈퇴 창
	//			editInformation();		// 정보 수정 및 탈퇴 기능
	//			system("pause");
	//			c1 = 'm';						// 병원 메인으로 전환
	//			break;
	//		case 'q':
	//			c = 'q';
	//			gotoxy(3, 20);
	//			printf("종료되었습니다");
	//			exit(0);
	//	}
	//}

	WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다./
	WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.


	//클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
}

// 요구사항 ID : S1
unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
    SOCKET sock = *((SOCKET*)arg);
    char msg[BUF_SIZE]="";		// 문자 합친것을 저장하기 위한 변수

    while (1) {
        switch (c) {
            case 'l':   //로그인
                printf("%s\t%s\n", id, pw);
                sprintf(msg, "%c@%s@%s", c, id, pw); //ID와 PW를 msg에 합치기
                send(sock, msg, strlen(msg), 0);  // msg 서버로 전달
                printf("\n\ngood\n");
                printf("%s", msg);
                c = '\0';
                break;
            case 'j':  //고객 회원가입
                sprintf(msg, "%c@%s@%s@%s@%s",        // 화원가입에 입력받았던 것 msg에 합치기
                    c, client.name, client.num, client.id, client.pw);
                send(sock, msg, strlen(msg), 0);          // msg 서버로 전달
                printf("%s", msg);
                break;
            case 'o':  //병원 회원가입
                sprintf(msg, "%c@%s@%s@%s@%s@%s",        // 화원가입에 입력받았던 것 msg에 합치기
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, msg, strlen(msg), 0);          // msg 서버로 전달
                printf("%s", msg);
                break;
            case 'f':   // 진료기록 확인 1
                sprintf(msg, "%c@%s", c, client.id);
                send(sock, msg, strlen(msg), 0);    // 고객 ID 서버로 전달
                printf("%s", msg);
                break;
            case 's': // 진료기록확인2
                sprintf(msg, "%c@%s", c, animNum);
                send(sock, msg, strlen(msg), 0);    // 고객 ID 서버로 전달break;
                break;
            case 'd':   // 예약날짜확인(고객)
            case 'w':   // 오늘 예약자 확인(병원)
            case 'b':   // 예약 내역확인(고객)
                sprintf(msg, "%c@%d@%d@%d@%d",        // date에 날짜 정보 합치기
                    c, today.year, today.month, today.day, today.hour);
                send(sock, msg, strlen(msg), 0);      // date 서버로 전달
                break;
            case 'r':   // 진료기록
                sprintf(msg, "%c@%s@%d@%d@%d@%s@%s",
                    c, mr1.num, mr1.date.year, mr1.date.month, mr1.date.day, mr1.mgName, mr1.record);
                send(sock, msg, strlen(msg), 0);
                break;
            case 'e':   // 예약
            case 'u':   // 접종
                sprintf(msg, "%c@%s@%s@%s@%d@%d@%d@%d@%s",
                    c, reser1.c_id, reser1.mg_id, reser1.num, reser1.date.year, reser1.date.month, reser1.date.day,
                    reser1.date.hour, reser1.cord);
                send(sock, msg, strlen(msg), 0);
                break;
            case 'n':   // 동물정보 등록
                sprintf(msg, "%c@%s@%d@%d@%d@%s",
                    c, animal.num, animal.bd.year, animal.bd.month, animal.bd.day, animal.c_id);
                send(sock, msg, strlen(msg), 0);
                break;
            case 'i':       // 고객 정보 수정
                sprintf(msg, "%c@%s@%s@%s@%s",        // 고객 수정 정보에 입력받았던 것 msg에 합치기
                    c, client.name, client.num, client.id, client.pw);
                send(sock, msg, strlen(msg), 0);          // msg 서버로 전달
                break;
            case 't':       // 관리자 정보 수정
                sprintf(msg, "%c@%s@%s@%s@%s@%s",        // 관리자 수정 정보에 입력받았던 것 msg에 합치기
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, msg, strlen(msg), 0);          // msg 서버로 전달
                break;
            case 'y':       // 관리자 탈퇴
                sprintf(msg, "%c@%s", c, manager.id);
                send(sock, msg, strlen(msg), 0);    // 관리자 ID 서버로 전달
                break;
            case 'v':       // 고객 탈퇴
                sprintf(msg, "%c@%s", c, client.id);
                send(sock, msg, strlen(msg), 0);    // 고객 ID 서버로 전달
                break;
            case 'q':
                printf("종료합니다.\n");
                send(sock, "q", 1, 0);
                closesocket(sock);
                exit(0);
                break;
        }
        c = '\0';
        strcpy(msg, "");
    }
    return 0;
}

unsigned WINAPI RecMsg(void* arg) {
    SOCKET sock = *((SOCKET*)arg);
    char result[BUF_SIZE];		// 문자 합친것을 저장하기 위한 변수

    int strLen;
    char* word = NULL;
    int w;
    ANIMAL* current;
    while (1) {
        strLen = recv(sock, result, BUF_SIZE - 1, 0);
        if (strLen == -1)
            return -1;
        result[strLen] = '\0';
        printf("%s\n", result);
        if (!strcmp(result, "q")) {
            printf("Client : Disconnection\n");
            closesocket(sock);
            exit(0);
        }
        else {
            word = strtok(result, "@");
            rc = word[0];
            //word = strtok(NULL, "@");
            switch (rc) {
            case 'l':		// 로그인 
                loinNum = atoi(strtok(NULL, "@"));
                printf("%d\n", loinNum);
                printf("loinNum : %d\n", loinNum);
                //switch (loinNum) {
                //case 0:     // 로그인 실패
                //    gotoxy(3, 7);
                //    textcolor(RED);
                //    printf("아이디 또는 비밀번호를 잘못 입력했습니다.");
                //    textcolor(WHITE);
                //    system("pause");
                //    c1 = 'a';
                //    printf("%c\n", c1);
                //    rc = '\0';
                //    strcpy(result, ""); 
                //    break;
                //case 1:     // 고객으로 로그인
                //    strcpy(client.name, strtok(NULL, "@"));
                //    strcpy(client.num, strtok(NULL, "@"));
                //    strcpy(client.id, strtok(NULL, "@"));
                //    strcpy(client.pw, strtok(NULL, "@"));
                //    textcolor(GREEN);
                //    printf("로그인 되었습니다");
                //    textcolor(WHITE);
                //    c1 = 'c';
                //    printf("%c\n", c1);
                //    //rc = '\0';
                //    strcpy(result, ""); 
                //    break;
                //case 2:     // 관리자 ( 병원 )으로 로그인
                //    strcpy(manager.name, strtok(NULL, "@"));
                //    strcpy(manager.lo.city, strtok(NULL, "@"));
                //    strcpy(manager.lo.dong, strtok(NULL, "@"));
                //    strcpy(manager.id, strtok(NULL, "@"));
                //    strcpy(manager.pw, strtok(NULL, "@"));
                //    textcolor(GREEN);
                //    printf("로그인 되었습니다");
                //    textcolor(WHITE);
                //    c1 = 'm';
                //    rc = '\0';
                //    strcpy(result, ""); 
                //    break;
                //}
                break;
            case 'j':		// 고객 회원가입
                joinNum = atoi(strtok(NULL, "@"));
                //switch (w) {
                //case 0:     // ID가 중복 될 시
                //    textcolor(RED);
                //    printf("ID가 중복됩니다");
                //    textcolor(WHITE);
                //    c1 = 'j';       // 다시 회원가입 화면으로 전환
                //    break;
                //case 1:     // 정상 회원가입
                //    system("cls");
                //    textcolor(GREEN);
                //    printf("가입되었습니다.\n");
                //    textcolor(WHITE);
                //    c1 = 'a';   // 시작 화면으로 전환
                //    break;
                //}
                rc = '\0';
                strcpy(result, ""); 
                break;
            case 'o':		// 관리자 ( 병원 ) 회원가입
                joinNum = atoi(strtok(NULL, "@"));
                //switch (w) {
                //case 0:     // ID가 중복 될 시
                //    textcolor(RED);
                //    printf("ID가 중복됩니다");
                //    textcolor(WHITE);
                //    c1 = 'o';   // 다시 회원가입 화면으로 전환
                //    break;
                //case 1:
                //    system("cls");
                //    textcolor(GREEN);
                //    printf("가입되었습니다.\n");
                //    textcolor(WHITE);
                //    c1 = 'a';   // 시작 화면으로 전환
                //    break;
                //}
                strcpy(result, "");
                break;
            case 'f':		// 진료 기록 확인 1 ( 동물등록번호 출력 )
                strcpy(animal.num, strtok(NULL, "@"));
                animal.bd.year = atoi(strtok(NULL, "@"));
                animal.bd.month = atoi(strtok(NULL, "@"));      //구조체에 정보 저장
                animal.bd.day = atoi(strtok(NULL, "@"));
                strcpy(animal.c_id, strtok(NULL, "@"));
                gotoxy(3, q);	printf("%d : %s\n", q2, animal.num);
                q2++;	q += 2;
                strcpy(result, "");
                break;
            case 's':		// 진료 기록 확인 2 ( 진료 기록 출력 )
                strcpy(mr1.num, strtok(NULL, "@"));
                mr1.date.year = atoi(strtok(NULL, "@"));
                mr1.date.month = atoi(strtok(NULL, "@"));       // 구조체에 정보 저장
                mr1.date.day = atoi(strtok(NULL, "@"));
                strcpy(mr1.mgName, strtok(NULL, "@"));
                strcpy(mr1.record, strtok(NULL, "@"));
                gotoxy(3, q);	printf("%d : %d-%d-%d\n", q2,
                    mr1.date.year, mr1.date.month, mr1.date.day);
                printf("%s\n", mr1.record);
                q2++;
                q += 4;
                strcpy(result, "");
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
                strcpy(result, "");
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
                strcpy(result, "");
                break;
            case 'r':		// 진료 기록
                textcolor(GREEN);
                printf("기록되었습니다.");
                textcolor(WHITE);
                break;
            case 'e':		// 예약
                ee = atoi(strtok(NULL, "@"));
                /*textcolor(GREEN);
                printf("예약되었습니다.");
                textcolor(WHITE);*/
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