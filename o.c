#define _WINSOCK_DEPRECATED_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� ���ϰ��� ��� ���ÿ�
#define _CRT_SECURE_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� �Է°��� ��� ���ÿ�
#pragma comment(lib, "ws2_32")  //���־�Ʃ��� ȯ�濡�� ���߽� ���� ���̺귯�� ������#pragma warning(disable:4996)
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

	strcpy(serverIp, "10.20.12.4");	// ���Ƿ� ����
	portNum = 55555;		// ���Ƿ� ���� " 55555 "

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = socket(PF_INET, SOCK_STREAM, 0);//������ �ϳ� �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);
	serverAddr.sin_port = htons(portNum);

	connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);		//�޽��� ���ۿ� �����尡 ����ȴ�.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecMsg, (void*)&sock, 0, NULL);		//�޽��� ���ſ� �����尡 ����ȴ�.

	while (1) {
		switch (c) {
			//�α��� or ȸ������
			case 'a':
				system("cls");
				gotoxy(3, 1);	printf("1. �α���");
				gotoxy(3, 3);	printf("2. ȸ������");
				gotoxy(3, 5);	printf(">");	scanf("%d", &n);
				switch (n) {
					case 1:			// �α���
						system("cls");
						gotoxy(3, 1);	printf("[�α���]");
						gotoxy(3, 3);	printf("ID :");
						gotoxy(3, 5);	printf("P.W :\n");
						system("pause");
						c = 'c';
						break;
					case 2:			//ȸ������
						system("cls");
						gotoxy(3, 1);	printf("[ȸ������]");
						gotoxy(3, 3);	printf("1. ��");
						gotoxy(3, 5);	printf("2. ����");
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
			case 'j':			//�� ȸ������
				system("cls");
				gotoxy(3, 1);		printf("[��] ȸ������");
				gotoxy(3, 3);		printf("ID :");
				gotoxy(3, 5);		printf("P.W :");
				gotoxy(3, 7);		printf("�̸� :");
				gotoxy(3, 9);		printf("��ȭ��ȣ :");
				break;
			case 'o':				//���� ����
				system("cls");
				gotoxy(3, 1);		printf("[����] ȸ������");
				gotoxy(3, 3);		printf("ID :");
				gotoxy(3, 5);		printf("P.W :");
				gotoxy(3, 7);		printf("������ :");
				gotoxy(3, 9);		printf("���� :");
				gotoxy(3, 10);	printf("(��, ��)");
				break;
			// ������
			case 'c':
				system("cls");
				cuMainScreen();			// �� ���θ�� â
				reservationBorder();	// ���೯¥ ĭ
				reservationDate();		// ���� ��¥ Ȯ�� ( �ٰ����� ���� ��¥ )
				gotoxy(3, 12);	printf(">");	scanf("%d", &num);
				switch (num) {
					case 1:
						c = 'f';				// ���� ��� Ȯ�� â���� �̵�
						break;
					case 2:
						c = 'b';				// ���� ���� Ȯ�� â���� �̵�
					case 3:
						c = 'x';				// ���� ���� �� Ż�� â���� �̵�
						break;
					case 4:
						c = 'q';				// ����
						break;
					default:
						printf("�ٽ��Է�");
						break;
				}
				num = 0;
				break;

			case 'f':			//������Ȯ��
				system("cls");
				medicalRecordCheck();		// �� ���� ��� Ȯ�� â
				c = 'c';								// �������� ��ȯ

				system("pause");
				break;
			case 'b':
				system("cls");
				findReservation();				// ���� ���� Ȯ�� â
				getchar();
				system("\n\npause");
				c = 'c';
				break;
			case 'x':			//������������Ż��
				system("cls");
				corrInformation();		// �� ���� ���� �� Ż�� â
				editInformation();		// ���� ���� �� Ż�� ���
				system("pause");
				c = 'c';						// �������� ��ȯ
				break;
			case 'm':		//��������
				system("cls");
				mgMainScreen();		// ������( ���� ) ���θ�� â
				reservationBorder();	// ���೯¥ ĭ
				todayReservation();		// ���� ������ Ȯ��
				gotoxy(3, 16);	printf(">");	scanf("%d", &num);
				switch (num) {
				case 1:							// ���� ��� â���� ��ȯ
					c = 'R';
					break;
				case 2:							// �ݷ����� ��� â���� ��ȯ
					c = 'N';
				case 3:							// ���� �� ���� â���� ��ȯ
					c = 'p';
					break;
				case 4:							// ȯ�� ������ Ȯ��
					system("cls");
					gotoxy(3, 2);	printf("������Ϲ�ȣ : ");	gets(animalNum);
					myRecode2();
					system("pause");
					c = 'm';						// ���� �������� ��ȯ
					break;
				case 5:							// ���� ���� �� Ż��
					c = 'z';
					break;
				case 6:							// ����
					c = 'q';
					break;
				}
				break;
			case 'R':			//����������
				system("cls");
				medicalRecord();		// ���� ������ â
				hosptalRecode();		// ���� ������ ���
				system("pause");
				c = 'm';						// ���� �������� ��ȯ
				break;
			case 'N':		//�ݷ����� ���
				system("cls");
				addAnimal();				// �ݷ����� ��� â
				animalNum();
				system("pause");
				c = 'm';						// ���� �������� ��ȯ
				break;
			case 'p':			//���Ό�������
				reservOrInocul();		// ���� �� ���� â
				n = 0;
				scanf("%d", &n);
				if (n == 1) 
					c = 'E';					// n==1 �̸� ����â����
				else if (n == 2) 
					c = 'U';					// n==2�̸� ����â���� 
				break;

				//����
			case 'E':
				system("cls");
				reserv();					// ���� â
				reservationCheck();		// ���� ��¥ �ߺ� Ȯ��
				reservation();				// ���� ���� �Է�
				system("pause");
				c = 'm';						// ���� �������� ��ȯ
				break;

				//����
			case 'U':
				system("cls");
				inocul();						// ���� â
				inoculation();				// ���� ���� �Է�
				system("pause");
				c = 'm';						// ���� �������� ��ȯ
				break;

				//���� �������� �� Ż��
			case 'z':
				system("cls");
				corrInformation();		// �������� �� Ż�� â
				editInformation();		// ���� ���� �� Ż�� ���
				system("pause");
				c = 'm';						// ���� �������� ��ȯ
				break;
			case 'q':
				printf("����Ǿ����ϴ�");
				break;
			default:
				printf("�ٽ��Է�");
				break;
		}
	}

	WaitForSingleObject(sendThread, INFINITE);//���ۿ� �����尡 �����ɶ����� ��ٸ���./
	WaitForSingleObject(recvThread, INFINITE);//���ſ� �����尡 �����ɶ����� ��ٸ���.


	//Ŭ���̾�Ʈ�� ���Ḧ �õ��Ѵٸ� ���� �Ʒ��� ����ȴ�.
	closesocket(sock);//������ �����Ѵ�.
	WSACleanup();//������ ���� ��������� �ü���� �˸���.
}