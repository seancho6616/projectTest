#define _WINSOCK_DEPRECATED_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� ���ϰ��� ��� ���ÿ�
#define _CRT_SECURE_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� �Է°��� ��� ���ÿ�
#pragma comment(lib, "ws2_32")  //���־�Ʃ��� ȯ�濡�� ���߽� ���� ���̺귯�� ������#pragma warning(disable:4996)
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

#define ID 20			// ID �迭ũ��
#define PW 20			// PW �迭ũ��
#define MAX 12			// �̸� �迭ũ��
#define NUM 16			// ��ȣ(��ȭ��ȣ, ��Ϲ�ȣ) �迭ũ��
#define RECORD 500		// ���� ��� �迭ũ��
#define LO 6			// ������ �ڵ� �迭ũ��
#define BUF_SIZE 700

void main() {
	int n = 0;
	char serverIp[100];
	int  portNum;
	todayDate();
	strcpy(serverIp, "10.20.12.4");	// ���Ƿ� ����
	portNum = 55555;		// ���Ƿ� ���� " 55555 "

	//WSAStartup(MAKEWORD(2, 2), &wsaData);
	//sock = socket(PF_INET, SOCK_STREAM, 0);//������ �ϳ� �����Ѵ�.

	//memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = inet_addr(serverIp);
	//serverAddr.sin_port = htons(portNum);

	//connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


	//sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);		//�޽��� ���ۿ� �����尡 ����ȴ�.
	//recvThread = (HANDLE)_beginthreadex(NULL, 0, RecMsg, (void*)&sock, 0, NULL);		//�޽��� ���ſ� �����尡 ����ȴ�.

	while (1) {
		switch (c1) {
			case 'a':		//�α��� or ȸ������
				system("cls");
				gotoxy(3, 1);	printf("1. �α���");
				gotoxy(3, 3);	printf("2. ȸ������");
				gotoxy(3, 5);	printf(">  ");	scanf("%d", &n);
				getchar();
				switch (n) {
					case 1:			// �α���
						system("cls");
						gotoxy(3, 1);	printf("[�α���]");
						gotoxy(3, 3);	printf("ID :");
						gotoxy(3, 5);	printf("P.W :\n");
						gotoxy(10, 3);   gets(id);         // ID �Է�
						gotoxy(10, 5);   gets(pw);         // PW �Է�
						c = 'l';
						gotoxy(3, 10);
						system("pause");
						c1 = 'c';
						//c = 'c';
						break;
					case 2:			//ȸ������
						system("cls");
						gotoxy(3, 1);	printf("[ȸ������]");
						gotoxy(3, 3);	printf("1. ��");
						gotoxy(3, 5);	printf("2. ����");
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
			case 'j':			//�� ȸ������
				system("cls");
				fflush(stdin);
				gotoxy(3, 1);		printf("[��] ȸ������");
				gotoxy(3, 3);		printf("ID :");
				gotoxy(3, 5);		printf("P.W :");
				gotoxy(3, 7);		printf("�̸� :");
				gotoxy(3, 9);		printf("��ȭ��ȣ :");
				gotoxy(15, 3);	gets(client.id);
				gotoxy(15, 5);	gets(client.pw);
				gotoxy(15, 7);	gets(client.name);
				gotoxy(15, 9);	gets(client.num);
				system("pause");
				c = 'j';
				c1 = 'a';
				break;
			case 'o':				//���� ����
				system("cls");
				fflush(stdin);
				gotoxy(3, 1);		printf("[����] ȸ������");
				gotoxy(3, 3);		printf("ID :");
				gotoxy(3, 5);		printf("P.W :");
				gotoxy(3, 7);		printf("������ :");
				gotoxy(3, 9);		printf("���� :");
				gotoxy(3, 10);	printf("(��, ��)");
				gotoxy(15, 3);  gets(manager.id);
				gotoxy(15, 5);  gets(manager.pw);
				gotoxy(15, 7);  gets(manager.name);
				gotoxy(15, 9);  gets(manager.lo.city); 
				gotoxy(25, 9);	 printf(" ��\t");
				gets(manager.lo.dong); gotoxy(40, 9); printf("��\n");
				gotoxy(2, 12);
				system("pause");

				c = 'o';
				c1 = 'a';
				break;
			// ������
			case 'c':
				system("cls");
				fflush(stdin);
				cuMainScreen();			// �� ���θ�� â
				reservationBorder();	// ���೯¥ ĭ
				reservationDate();		// ���� ��¥ Ȯ�� ( �ٰ����� ���� ��¥ )
				gotoxy(3, 12);	printf(">  ");	scanf("%d", &num);
				getchar();
				switch (num) {
					case 1:
						c1 = 'f';				// ���� ��� Ȯ�� â���� �̵�
						break;
					case 2:
						c1 = 'b';				// ���� ���� Ȯ�� â���� �̵�
						break;
					case 3:
						c1 = 'i';				// ���� ���� �� Ż�� â���� �̵�
						break;
					case 4:
						c = 'q';				// ����
						break;
					default:
						printf("\n\t�ٽ��Է�\n");
						system("pause");
						break;
				}
				num = 0;
				break;

			case 'f':			//������Ȯ��
				system("cls");
				fflush(stdin);
				medicalRecordCheck();		// �� ���� ��� Ȯ�� â
				gotoxy(3, 20);
				system("pause");

				c1 = 'c';								// �������� ��ȯ

				break;
			case 'b':
				system("cls");
				fflush(stdin);
				findReservation();				// ���� ���� Ȯ�� â
				c = 'b';
				gotoxy(3, 20);
				system("pause");
				c1 = 'c';
				break;
			case 'i':			//������������Ż��
				system("cls");
				fflush(stdin);
				corrInformation();		// �� ���� ���� �� Ż�� â
				editInformation();		// ���� ���� �� Ż�� ���
				system("pause");
				c1 = 'c';						// �������� ��ȯ
				break;
			case 'm':		//��������
				system("cls");
				fflush(stdin);
				mgMainScreen();		// ������( ���� ) ���θ�� â
				reservationBorder();	// ���೯¥ ĭ
				todayReservation();		// ���� ������ Ȯ��
				gotoxy(3, 16);	printf(">  ");	scanf("%d", &num);
				getchar();
				switch (num) {
				case 1:							// ���� ��� â���� ��ȯ
					c1 = 'r';
					break;
				case 2:							// �ݷ����� ��� â���� ��ȯ
					c1 = 'n';
					break;
				case 3:							// ���� �� ���� â���� ��ȯ
					c1 = 'p';
					break;
				case 4:							// ȯ�� ������ Ȯ��
					system("cls");
					fflush(stdin);
					gotoxy(3, 2);	printf("������Ϲ�ȣ : ");	gets(animNum);
					system("cls");
					myRecode2();
					gotoxy(3, 20);
					system("pause");
					c1 = 'm';						// ���� �������� ��ȯ
					break;
				case 5:							// ���� ���� �� Ż��
					c1 = 't';
					break;
				case 6:							// ����
					c = 'q';
					break;
				default:
					printf("\n\t�ٽ��Է�\n");
					system("pause");
					break;
				}
				break;
			case 'r':			//����������
				system("cls");
				fflush(stdin);
				medicalRecord();		// ���� ������ â
				hosptalRecode();		// ���� ������ ���
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// ���� �������� ��ȯ
				break;
			case 'n':		//�ݷ����� ���
				system("cls");
				fflush(stdin);
				addAnimal();				// �ݷ����� ��� â
				animalNum();
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// ���� �������� ��ȯ
				break;
			case 'p':			//���Ό�������
				system("cls");
				fflush(stdin);
				reservOrInocul();		// ���� �� ���� â
				n = 0;
				scanf("%d", &n);
				getchar();
				if (n == 1) 
					c1 = 'e';					// n==1 �̸� ����â����
				else if (n == 2) 
					c1 = 'u';					// n==2�̸� ����â���� 
				break;

				//����
			case 'e':
				system("cls");
				fflush(stdin);
				reserv();					// ���� â
				reservationCheck();		// ���� ��¥ �ߺ� Ȯ��
				reservation();				// ���� ���� �Է�
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// ���� �������� ��ȯ
				break;

				//����
			case 'u':
				system("cls");
				fflush(stdin);
				inocul();						// ���� â
				inoculation();				// ���� ���� �Է�
				gotoxy(3, 20);
				system("pause");
				c1 = 'm';						// ���� �������� ��ȯ
				break;

				//���� �������� �� Ż��
			case 't':
				system("cls");
				fflush(stdin);
				corrInformation();		// �������� �� Ż�� â
				editInformation();		// ���� ���� �� Ż�� ���
				system("pause");
				c1 = 'm';						// ���� �������� ��ȯ
				break;
			case 'q':
				printf("����Ǿ����ϴ�");
				break;
		}
	}

	//WaitForSingleObject(sendThread, INFINITE);//���ۿ� �����尡 �����ɶ����� ��ٸ���./
	//WaitForSingleObject(recvThread, INFINITE);//���ſ� �����尡 �����ɶ����� ��ٸ���.


	////Ŭ���̾�Ʈ�� ���Ḧ �õ��Ѵٸ� ���� �Ʒ��� ����ȴ�.
	//closesocket(sock);//������ �����Ѵ�.
	//WSACleanup();//������ ���� ��������� �ü���� �˸���.
}