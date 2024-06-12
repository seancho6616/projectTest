#define _WINSOCK_DEPRECATED_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 소켓관련 경고 무시용
#define _CRT_SECURE_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 입력관련 경고 무시용
#pragma comment(lib, "ws2_32")  //비주얼스튜디오 환경에서 개발시 소켓 라이브러리 지정용#pragma warning(disable:4996)
//#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include "client.h"
#include "0609.h"

void main() {
	int n = 0;

	char serverIp[100];
	int  portNum;

	strcpy(serverIp, "10.20.12.4");	// 임의로 설정
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

	while (1) {
		switch (c) {
			//로그인 or 회원가입
			case 'a':
				system("cls");
				gotoxy(3, 1);	printf("1. 로그인");
				gotoxy(3, 3);	printf("2. 회원가입");
				gotoxy(3, 5);	printf(">");	scanf("%d", &n);
				switch (n) {
					case 1:			// 로그인
						system("cls");
						gotoxy(3, 1);	printf("[로그인]");
						gotoxy(3, 3);	printf("ID :");
						gotoxy(3, 5);	printf("P.W :\n");
						system("pause");
						c = 'c';
						break;
					case 2:			//회원가입
						system("cls");
						gotoxy(3, 1);	printf("[회원가입]");
						gotoxy(3, 3);	printf("1. 고객");
						gotoxy(3, 5);	printf("2. 병원");
						gotoxy(3, 7);	printf(">");	scanf("%d", &n);
						if (n == 1) {
							c = 'j';
							break;
						}
						else if (n == 2) {
							c = 'o';
						}
						break;
				}
				break;
			case 'j':			//고객 회원가입
				system("cls");
				gotoxy(3, 1);		printf("[고객] 회원가입");
				gotoxy(3, 3);		printf("ID :");
				gotoxy(3, 5);		printf("P.W :");
				gotoxy(3, 7);		printf("이름 :");
				gotoxy(3, 9);		printf("전화번호 :");
				break;
			case 'o':				//병원 가입
				system("cls");
				gotoxy(3, 1);		printf("[병원] 회원가입");
				gotoxy(3, 3);		printf("ID :");
				gotoxy(3, 5);		printf("P.W :");
				gotoxy(3, 7);		printf("병원명 :");
				gotoxy(3, 9);		printf("지역 :");
				gotoxy(3, 10);	printf("(시, 동)");
				break;
			// 고객메인
			case 'c':
				system("cls");
				cuMainScreen();			// 고객 메인목록 창
				reservationBorder();	// 예약날짜 칸
				reservationDate();		// 예약 날짜 확인 ( 다가오는 예약 날짜 )
				gotoxy(3, 12);	printf(">");	scanf("%d", &num);
				switch (num) {
					case 1:
						c = 'f';				// 진료 기록 확인 창으로 이동
						break;
					case 2:
						c = 'b';				// 예약 내역 확인 창으로 이동
					case 3:
						c = 'x';				// 정보 수정 및 탈퇴 창으로 이동
						break;
					case 4:
						c = 'q';				// 종료
						break;
					default:
						printf("다시입력");
						break;
				}
				num = 0;
				break;

			case 'f':			//진료기록확인
				system("cls");
				medicalRecordCheck();		// 고객 진료 기록 확인 창
				c = 'c';								// 메인으로 전환

				system("pause");
				break;
			case 'b':
				system("cls");
				findReservation();				// 예약 내역 확인 창
				getchar();
				system("\n\npause");
				c = 'c';
				break;
			case 'x':			//고객정보수정및탈퇴
				system("cls");
				corrInformation();		// 고객 정보 수정 및 탈퇴 창
				editInformation();		// 정보 수정 및 탈퇴 기능
				system("pause");
				c = 'c';						// 메인으로 전환
				break;
			case 'm':		//병원메인
				system("cls");
				mgMainScreen();		// 관리자( 병원 ) 메인목록 창
				reservationBorder();	// 예약날짜 칸
				todayReservation();		// 오늘 예약자 확인
				gotoxy(3, 16);	printf(">");	scanf("%d", &num);
				switch (num) {
				case 1:							// 진료 기록 창으로 전환
					c = 'R';
					break;
				case 2:							// 반려동물 등록 창으로 전환
					c = 'N';
				case 3:							// 예약 및 접종 창으로 전환
					c = 'p';
					break;
				case 4:							// 환자 진료기록 확인
					system("cls");
					gotoxy(3, 2);	printf("동물등록번호 : ");	gets(animalNum);
					myRecode2();
					system("pause");
					c = 'm';						// 병원 메인으로 전환
					break;
				case 5:							// 정보 수정 및 탈퇴
					c = 'z';
					break;
				case 6:							// 종료
					c = 'q';
					break;
				}
				break;
			case 'R':			//병원진료기록
				system("cls");
				medicalRecord();		// 병원 진료기록 창
				hosptalRecode();		// 병원 진료기록 기능
				system("pause");
				c = 'm';						// 병원 메인으로 전환
				break;
			case 'N':		//반려동물 등록
				system("cls");
				addAnimal();				// 반려동물 등록 창
				animalNum();
				system("pause");
				c = 'm';						// 병원 메인으로 전환
				break;
			case 'p':			//진료예약및접좁
				reservOrInocul();		// 예약 및 접종 창
				n = 0;
				scanf("%d", &n);
				if (n == 1) 
					c = 'E';					// n==1 이면 예약창으로
				else if (n == 2) 
					c = 'U';					// n==2이면 접종창으로 
				break;

				//예약
			case 'E':
				system("cls");
				reserv();					// 예약 창
				reservationCheck();		// 예약 날짜 중복 확인
				reservation();				// 예약 정보 입력
				system("pause");
				c = 'm';						// 병원 메인으로 전환
				break;

				//접종
			case 'U':
				system("cls");
				inocul();						// 접종 창
				inoculation();				// 접종 정보 입력
				system("pause");
				c = 'm';						// 병원 메인으로 전환
				break;

				//병원 정보수정 및 탈퇴
			case 'z':
				system("cls");
				corrInformation();		// 정보수정 및 탈퇴 창
				editInformation();		// 정보 수정 및 탈퇴 기능
				system("pause");
				c = 'm';						// 병원 메인으로 전환
				break;
			case 'q':
				printf("종료되었습니다");
				break;
			default:
				printf("다시입력");
				break;
		}
	}

	WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다./
	WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.


	//클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
}