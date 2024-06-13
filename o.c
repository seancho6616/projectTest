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

void main() {
	int n = 0;
	char serverIp[100];
	int  portNum;
	todayDate();
	strcpy(serverIp, "10.20.12.4");	// 임의로 설정
	portNum = 55555;		// 임의로 설정 " 55555 "

	//WSAStartup(MAKEWORD(2, 2), &wsaData);
	//sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	//memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = inet_addr(serverIp);
	//serverAddr.sin_port = htons(portNum);

	//connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


	//sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);		//메시지 전송용 쓰레드가 실행된다.
	//recvThread = (HANDLE)_beginthreadex(NULL, 0, RecMsg, (void*)&sock, 0, NULL);		//메시지 수신용 쓰레드가 실행된다.

	while (1) {
		switch (c1) {
			case 'a':		//로그인 or 회원가입
				system("cls");
				gotoxy(3, 1);	printf("1. 로그인");
				gotoxy(3, 3);	printf("2. 회원가입");
				gotoxy(3, 5);	printf(">  ");	scanf("%d", &n);
				getchar();
				switch (n) {
					case 1:			// 로그인
						system("cls");
						gotoxy(3, 1);	printf("[로그인]");
						gotoxy(3, 3);	printf("ID :");
						gotoxy(3, 5);	printf("P.W :\n");
						gotoxy(10, 3);   gets(id);         // ID 입력
						gotoxy(10, 5);   gets(pw);         // PW 입력
						c = 'l';
						gotoxy(3, 10);
						system("pause");
						c1 = 'c';
						//c = 'c';
						break;
					case 2:			//회원가입
						system("cls");
						gotoxy(3, 1);	printf("[회원가입]");
						gotoxy(3, 3);	printf("1. 고객");
						gotoxy(3, 5);	printf("2. 병원");
						gotoxy(3, 7);	printf(">  ");	scanf("%d", &n);
						getchar();
						if (n == 1) {
							c1 = 'j';
						}
						else if (n == 2) {
							c1 = 'o';
						}
						break;
				}
				break;
			case 'j':			//고객 회원가입
				system("cls");
				fflush(stdin);
				gotoxy(3, 1);		printf("[고객] 회원가입");
				gotoxy(3, 3);		printf("ID :");
				gotoxy(3, 5);		printf("P.W :");
				gotoxy(3, 7);		printf("이름 :");
				gotoxy(3, 9);		printf("전화번호 :");
				gotoxy(15, 3);	gets(client.id);
				gotoxy(15, 5);	gets(client.pw);
				gotoxy(15, 7);	gets(client.name);
				gotoxy(15, 9);	gets(client.num);
				system("pause");
				c = 'j';
				c1 = 'a';
				break;
			case 'o':				//병원 가입
				system("cls");
				fflush(stdin);
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
				gets(manager.lo.dong); gotoxy(40, 9); printf("동\n");
				gotoxy(2, 12);
				system("pause");

				c = 'o';
				c1 = 'a';
				break;
			// 고객메인
			case 'c':
				system("cls");
				fflush(stdin);
				cuMainScreen();			// 고객 메인목록 창
				reservationBorder();	// 예약날짜 칸
				reservationDate();		// 예약 날짜 확인 ( 다가오는 예약 날짜 )
				gotoxy(3, 12);	printf(">  ");	scanf("%d", &num);
				getchar();
				switch (num) {
					case 1:
						c1 = 'f';				// 진료 기록 확인 창으로 이동
						break;
					case 2:
						c1 = 'b';				// 예약 내역 확인 창으로 이동
						break;
					case 3:
						c1 = 'i';				// 정보 수정 및 탈퇴 창으로 이동
						break;
					case 4:
						c = 'q';				// 종료
						break;
					default:
						printf("\n\t다시입력\n");
						system("pause");
						break;
				}
				num = 0;
				break;

			case 'f':			//진료기록확인
				system("cls");
				fflush(stdin);
				medicalRecordCheck();		// 고객 진료 기록 확인 창
				gotoxy(3, 20);
				system("pause");

				c1 = 'c';								// 메인으로 전환

				break;
			case 'b':
				system("cls");
				fflush(stdin);
				findReservation();				// 예약 내역 확인 창
				c = 'b';
				gotoxy(3, 20);
				system("pause");
				c1 = 'c';
				break;
			case 'i':			//고객정보수정및탈퇴
				system("cls");
				fflush(stdin);
				corrInformation();		// 고객 정보 수정 및 탈퇴 창
				editInformation();		// 정보 수정 및 탈퇴 기능
				system("pause");
				c1 = 'c';						// 메인으로 전환
				break;
			case 'm':		//병원메인
				system("cls");
				fflush(stdin);
				mgMainScreen();		// 관리자( 병원 ) 메인목록 창
				reservationBorder();	// 예약날짜 칸
				todayReservation();		// 오늘 예약자 확인
				gotoxy(3, 16);	printf(">  ");	scanf("%d", &num);
				getchar();
				switch (num) {
				case 1:							// 진료 기록 창으로 전환
					c1 = 'r';
					break;
				case 2:							// 반려동물 등록 창으로 전환
					c1 = 'n';
					break;
				case 3:							// 예약 및 접종 창으로 전환
					c1 = 'p';
					break;
				case 4:							// 환자 진료기록 확인
					system("cls");
					fflush(stdin);
					gotoxy(3, 2);	printf("동물등록번호 : ");	gets(animNum);
					system("cls");
					myRecode2();
					gotoxy(3, 20);
					system("pause");
					c1 = 'm';						// 병원 메인으로 전환
					break;
				case 5:							// 정보 수정 및 탈퇴
					c1 = 't';
					break;
				case 6:							// 종료
					c = 'q';
					break;
				default:
					printf("\n\t다시입력\n");
					system("pause");
					break;
				}
				break;
			case 'r':			//병원진료기록
				system("cls");
				fflush(stdin);
				medicalRecord();		// 병원 진료기록 창
				hosptalRecode();		// 병원 진료기록 기능
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// 병원 메인으로 전환
				break;
			case 'n':		//반려동물 등록
				system("cls");
				fflush(stdin);
				addAnimal();				// 반려동물 등록 창
				animalNum();
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// 병원 메인으로 전환
				break;
			case 'p':			//진료예약및접좁
				system("cls");
				fflush(stdin);
				reservOrInocul();		// 예약 및 접종 창
				n = 0;
				scanf("%d", &n);
				getchar();
				if (n == 1) 
					c1 = 'e';					// n==1 이면 예약창으로
				else if (n == 2) 
					c1 = 'u';					// n==2이면 접종창으로 
				break;

				//예약
			case 'e':
				system("cls");
				fflush(stdin);
				reserv();					// 예약 창
				reservationCheck();		// 예약 날짜 중복 확인
				reservation();				// 예약 정보 입력
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// 병원 메인으로 전환
				break;

				//접종
			case 'u':
				system("cls");
				fflush(stdin);
				inocul();						// 접종 창
				inoculation();				// 접종 정보 입력
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// 병원 메인으로 전환
				break;

				//병원 정보수정 및 탈퇴
			case 't':
				system("cls");
				fflush(stdin);
				corrInformation();		// 정보수정 및 탈퇴 창
				editInformation();		// 정보 수정 및 탈퇴 기능
				system("pause");
				c1 = 'm';						// 병원 메인으로 전환
				break;
			case 'q':
				printf("종료되었습니다");
				break;
		}
	}

	//WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다./
	//WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.


	////클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	//closesocket(sock);//소켓을 종료한다.
	//WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
}