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

char msg[BUF_SIZE] = "";
char result[BUF_SIZE] = "";

unsigned WINAPI SendMsg(void* arg);		// ���� ���� �Լ�

unsigned WINAPI RecMsg(void* arg);		// ���� ���� �Լ�

void main() {
	
	char serverIp[100];
	int  portNum;
	todayDate();
	strcpy(serverIp, "192.168.0.9");	// ���Ƿ� ����
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
	//		case 'a':		//�α��� or ȸ������
	//			system("cls");
 //               startInterface();
	//			switch (n) {
	//				case 1:			// �α���
	//					system("cls");
 //                       fflush(stdin);
 //                       loginInterface();
	//					gotoxy(3, 10);
 //                       printf("%s\n%s\n", id, pw);
 //                       c = 'l';
 //                       printf("%c", c);
 //                       sprintf(animNum, "%c@%s@%s",'c', id, pw);
 //                       printf("%s\n", animNum);
	//					//c1 = 'm'; �׽�Ʈ��
	//					break;
	//				case 2:			//ȸ������
	//					system("cls");
 //                       joinInterface();
	//					if (n == 1) {
	//						c1 = 'j';		// �� ȸ������ â���� �̵�
	//					}
	//					else if (n == 2) {
	//						c1 = 'o';		// ���� ȸ������ â���� �̵�
	//					}
	//					break;
	//			}
	//			break;
	//		case 'j':			//�� ȸ������
	//			system("cls");
	//			fflush(stdin);
 //               joinClientInterface();
	//			gotoxy(3, 12);
	//			c = 'j';
	//			system("pause");
	//			c1 = 'a';
	//			break;
	//		case 'o':				//���� ����
	//			system("cls");
	//			fflush(stdin);
 //               joinManagerInterface();
	//			
	//			gotoxy(3, 12);
	//			c = 'o'; 
	//			system("pause");
	//			c1 = 'a';
	//			break;
	//		// ������
	//		case 'c':
	//			system("cls");
	//			fflush(stdin);				// ���� �ִ� ���� �ʱ�ȭ
	//			cuMainScreen();			// �� ���θ�� â
	//			reservationBorder();	// ���೯¥ ĭ
	//			q = 5;
	//			q2 = 1; 
	//			reservationDate();		// ���� ��¥ Ȯ�� ( �ٰ����� ���� ��¥ )
	//			gotoxy(3, 12);	printf(">  ");	scanf("%d", &num);
	//			getchar();
	//			switch (num) {
	//				case 1:
	//					c1 = 'f';				// ���� ��� Ȯ�� â���� �̵�
	//					break;
	//				case 2:
	//					c1 = 'b';				// ���� ���� Ȯ�� â���� �̵�
	//					break;
	//				case 3:
	//					c1 = 'i';				// ���� ���� �� Ż�� â���� �̵�
	//					break;
	//				case 4:
	//					c = 'q';				// ����
	//					c1 = 'q';
	//					break;
	//				default:					// �ش� ���� ���� �Է� �޾�����
	//					printf("\n\t�ٽ��Է�\n");
	//					system("pause");
	//					break;
	//			}
	//			num = 0;
	//			break;

	//		case 'f':			//������Ȯ��
	//			system("cls");
	//			fflush(stdin);
	//			medicalRecordCheck();		// �� ���� ��� Ȯ�� â
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'c';								// �������� ��ȯ
	//			break;
	//		case 'b':
	//			system("cls");
	//			fflush(stdin);
	//			q = 5;
	//			q2 = 1; 
	//			findReservation();				// ���� ���� Ȯ�� â
	//			c = 'b';
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'c';
	//			break;
	//		case 'i':			//������������Ż��
	//			system("cls");
	//			fflush(stdin);
	//			corrInformation();		// �� ���� ���� �� Ż�� â
	//			editInformation();		// ���� ���� �� Ż�� ���
	//			system("pause");
	//			c1 = 'c';						// �������� ��ȯ
	//			break;
	//		case 'm':		//��������
	//			system("cls");
	//			fflush(stdin);
	//			mgMainScreen();		// ������( ���� ) ���θ�� â
	//			reservationBorder();	// ���೯¥ ĭ
	//			q = 5;
	//			q2 = 1;
	//			todayReservation();		// ���� ������ Ȯ��
	//			gotoxy(3, 16);	printf(">  ");	scanf("%d", &num);
	//			getchar();
	//			switch (num) {
	//			case 1:							// ���� ��� â���� ��ȯ
	//				c1 = 'r';
	//				break;
	//			case 2:							// �ݷ����� ��� â���� ��ȯ
	//				c1 = 'n';
	//				break;
	//			case 3:							// ���� �� ���� â���� ��ȯ
	//				c1 = 'p';
	//				break;
	//			case 4:							// ȯ�� ������ Ȯ��
	//				system("cls");
	//				fflush(stdin);
	//				gotoxy(3, 2);	printf("������Ϲ�ȣ : ");	gets(animNum);
	//				system("cls");
	//				myRecode2();
	//				gotoxy(3, 20);
	//				system("pause");
	//				c1 = 'm';							// ���� �������� ��ȯ
	//				break;
	//			case 5:									// ���� ���� �� Ż��
	//				c1 = 't';
	//				break;
	//			case 6:									// ����
	//				c = 'q';
	//				c1 = 'q';
	//				break;
	//			default:
	//				printf("\n\t�ٽ��Է�\n");		// �ش� ���� ���� �Է� �޾�����
	//				system("pause");
	//				break;
	//			}
	//			break;
	//		case 'r':			//����������
	//			system("cls");
	//			fflush(stdin);
	//			medicalRecord();			// ���� ������ â
	//			hosptalRecode();			// ���� ������ ���
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// ���� �������� ��ȯ
	//			break;
	//		case 'n':		//�ݷ����� ���
	//			system("cls");
	//			fflush(stdin);
	//			addAnimal();					// �ݷ����� ��� â
	//			animalNum();
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// ���� �������� ��ȯ
	//			break;
	//		case 'p':			//���Ό�������
	//			system("cls");
	//			fflush(stdin);
	//			reservOrInocul();			// ���� �� ���� â
	//			n = 0;
	//			scanf("%d", &n);
	//			getchar();
	//			if (n == 1) 
	//				c1 = 'e';						// n==1 �̸� ����â����
	//			else if (n == 2) 
	//				c1 = 'u';						// n==2�̸� ����â���� 
	//			break;

	//			//����
	//		case 'e':
	//			system("cls");
	//			fflush(stdin);
	//			reserv();					// ���� â
	//			reservation();				// ���� ���� �Է�
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// ���� �������� ��ȯ
	//			break;

	//			//����
	//		case 'u':
	//			system("cls");
	//			fflush(stdin);
	//			inocul();						// ���� â
	//			inoculation();				// ���� ���� �Է�
	//			gotoxy(3, 20);
	//			system("pause");
	//			c1 = 'm';						// ���� �������� ��ȯ
	//			break;

	//			//���� �������� �� Ż��
	//		case 't':
	//			system("cls");
	//			fflush(stdin);
	//			corrInformation();		// �������� �� Ż�� â
	//			editInformation();		// ���� ���� �� Ż�� ���
	//			system("pause");
	//			c1 = 'm';						// ���� �������� ��ȯ
	//			break;
	//		case 'q':
	//			c = 'q';
	//			gotoxy(3, 20);
	//			printf("����Ǿ����ϴ�");
	//			exit(0);
	//	}
	//}

	WaitForSingleObject(sendThread, INFINITE);//���ۿ� �����尡 �����ɶ����� ��ٸ���./
	WaitForSingleObject(recvThread, INFINITE);//���ſ� �����尡 �����ɶ����� ��ٸ���.


	//Ŭ���̾�Ʈ�� ���Ḧ �õ��Ѵٸ� ���� �Ʒ��� ����ȴ�.
	closesocket(sock);//������ �����Ѵ�.
	WSACleanup();//������ ���� ��������� �ü���� �˸���.
}

// �䱸���� ID : S1
unsigned WINAPI SendMsg(void* arg) {//���ۿ� �������Լ�
    SOCKET sock = *((SOCKET*)arg);
    char msg[BUF_SIZE]="";		// ���� ��ģ���� �����ϱ� ���� ����

    while (1) {
        switch (c) {
            case 'l':   //�α���
                printf("%s\t%s\n", id, pw);
                sprintf(msg, "%c@%s@%s", c, id, pw); //ID�� PW�� msg�� ��ġ��
                send(sock, msg, strlen(msg), 0);  // msg ������ ����
                printf("\n\ngood\n");
                printf("%s", msg);
                c = '\0';
                break;
            case 'j':  //�� ȸ������
                sprintf(msg, "%c@%s@%s@%s@%s",        // ȭ�����Կ� �Է¹޾Ҵ� �� msg�� ��ġ��
                    c, client.name, client.num, client.id, client.pw);
                send(sock, msg, strlen(msg), 0);          // msg ������ ����
                printf("%s", msg);
                break;
            case 'o':  //���� ȸ������
                sprintf(msg, "%c@%s@%s@%s@%s@%s",        // ȭ�����Կ� �Է¹޾Ҵ� �� msg�� ��ġ��
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, msg, strlen(msg), 0);          // msg ������ ����
                printf("%s", msg);
                break;
            case 'f':   // ������ Ȯ�� 1
                sprintf(msg, "%c@%s", c, client.id);
                send(sock, msg, strlen(msg), 0);    // �� ID ������ ����
                printf("%s", msg);
                break;
            case 's': // ������Ȯ��2
                sprintf(msg, "%c@%s", c, animNum);
                send(sock, msg, strlen(msg), 0);    // �� ID ������ ����break;
                break;
            case 'd':   // ���೯¥Ȯ��(��)
            case 'w':   // ���� ������ Ȯ��(����)
            case 'b':   // ���� ����Ȯ��(��)
                sprintf(msg, "%c@%d@%d@%d@%d",        // date�� ��¥ ���� ��ġ��
                    c, today.year, today.month, today.day, today.hour);
                send(sock, msg, strlen(msg), 0);      // date ������ ����
                break;
            case 'r':   // ������
                sprintf(msg, "%c@%s@%d@%d@%d@%s@%s",
                    c, mr1.num, mr1.date.year, mr1.date.month, mr1.date.day, mr1.mgName, mr1.record);
                send(sock, msg, strlen(msg), 0);
                break;
            case 'e':   // ����
            case 'u':   // ����
                sprintf(msg, "%c@%s@%s@%s@%d@%d@%d@%d@%s",
                    c, reser1.c_id, reser1.mg_id, reser1.num, reser1.date.year, reser1.date.month, reser1.date.day,
                    reser1.date.hour, reser1.cord);
                send(sock, msg, strlen(msg), 0);
                break;
            case 'n':   // �������� ���
                sprintf(msg, "%c@%s@%d@%d@%d@%s",
                    c, animal.num, animal.bd.year, animal.bd.month, animal.bd.day, animal.c_id);
                send(sock, msg, strlen(msg), 0);
                break;
            case 'i':       // �� ���� ����
                sprintf(msg, "%c@%s@%s@%s@%s",        // �� ���� ������ �Է¹޾Ҵ� �� msg�� ��ġ��
                    c, client.name, client.num, client.id, client.pw);
                send(sock, msg, strlen(msg), 0);          // msg ������ ����
                break;
            case 't':       // ������ ���� ����
                sprintf(msg, "%c@%s@%s@%s@%s@%s",        // ������ ���� ������ �Է¹޾Ҵ� �� msg�� ��ġ��
                    c, manager.name, manager.lo.city, manager.lo.dong, manager.id, manager.pw);
                send(sock, msg, strlen(msg), 0);          // msg ������ ����
                break;
            case 'y':       // ������ Ż��
                sprintf(msg, "%c@%s", c, manager.id);
                send(sock, msg, strlen(msg), 0);    // ������ ID ������ ����
                break;
            case 'v':       // �� Ż��
                sprintf(msg, "%c@%s", c, client.id);
                send(sock, msg, strlen(msg), 0);    // �� ID ������ ����
                break;
            case 'q':
                printf("�����մϴ�.\n");
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
    char result[BUF_SIZE];		// ���� ��ģ���� �����ϱ� ���� ����

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
            case 'l':		// �α��� 
                loinNum = atoi(strtok(NULL, "@"));
                printf("%d\n", loinNum);
                printf("loinNum : %d\n", loinNum);
                //switch (loinNum) {
                //case 0:     // �α��� ����
                //    gotoxy(3, 7);
                //    textcolor(RED);
                //    printf("���̵� �Ǵ� ��й�ȣ�� �߸� �Է��߽��ϴ�.");
                //    textcolor(WHITE);
                //    system("pause");
                //    c1 = 'a';
                //    printf("%c\n", c1);
                //    rc = '\0';
                //    strcpy(result, ""); 
                //    break;
                //case 1:     // ������ �α���
                //    strcpy(client.name, strtok(NULL, "@"));
                //    strcpy(client.num, strtok(NULL, "@"));
                //    strcpy(client.id, strtok(NULL, "@"));
                //    strcpy(client.pw, strtok(NULL, "@"));
                //    textcolor(GREEN);
                //    printf("�α��� �Ǿ����ϴ�");
                //    textcolor(WHITE);
                //    c1 = 'c';
                //    printf("%c\n", c1);
                //    //rc = '\0';
                //    strcpy(result, ""); 
                //    break;
                //case 2:     // ������ ( ���� )���� �α���
                //    strcpy(manager.name, strtok(NULL, "@"));
                //    strcpy(manager.lo.city, strtok(NULL, "@"));
                //    strcpy(manager.lo.dong, strtok(NULL, "@"));
                //    strcpy(manager.id, strtok(NULL, "@"));
                //    strcpy(manager.pw, strtok(NULL, "@"));
                //    textcolor(GREEN);
                //    printf("�α��� �Ǿ����ϴ�");
                //    textcolor(WHITE);
                //    c1 = 'm';
                //    rc = '\0';
                //    strcpy(result, ""); 
                //    break;
                //}
                break;
            case 'j':		// �� ȸ������
                joinNum = atoi(strtok(NULL, "@"));
                //switch (w) {
                //case 0:     // ID�� �ߺ� �� ��
                //    textcolor(RED);
                //    printf("ID�� �ߺ��˴ϴ�");
                //    textcolor(WHITE);
                //    c1 = 'j';       // �ٽ� ȸ������ ȭ������ ��ȯ
                //    break;
                //case 1:     // ���� ȸ������
                //    system("cls");
                //    textcolor(GREEN);
                //    printf("���ԵǾ����ϴ�.\n");
                //    textcolor(WHITE);
                //    c1 = 'a';   // ���� ȭ������ ��ȯ
                //    break;
                //}
                rc = '\0';
                strcpy(result, ""); 
                break;
            case 'o':		// ������ ( ���� ) ȸ������
                joinNum = atoi(strtok(NULL, "@"));
                //switch (w) {
                //case 0:     // ID�� �ߺ� �� ��
                //    textcolor(RED);
                //    printf("ID�� �ߺ��˴ϴ�");
                //    textcolor(WHITE);
                //    c1 = 'o';   // �ٽ� ȸ������ ȭ������ ��ȯ
                //    break;
                //case 1:
                //    system("cls");
                //    textcolor(GREEN);
                //    printf("���ԵǾ����ϴ�.\n");
                //    textcolor(WHITE);
                //    c1 = 'a';   // ���� ȭ������ ��ȯ
                //    break;
                //}
                strcpy(result, "");
                break;
            case 'f':		// ���� ��� Ȯ�� 1 ( ������Ϲ�ȣ ��� )
                strcpy(animal.num, strtok(NULL, "@"));
                animal.bd.year = atoi(strtok(NULL, "@"));
                animal.bd.month = atoi(strtok(NULL, "@"));      //����ü�� ���� ����
                animal.bd.day = atoi(strtok(NULL, "@"));
                strcpy(animal.c_id, strtok(NULL, "@"));
                gotoxy(3, q);	printf("%d : %s\n", q2, animal.num);
                q2++;	q += 2;
                strcpy(result, "");
                break;
            case 's':		// ���� ��� Ȯ�� 2 ( ���� ��� ��� )
                strcpy(mr1.num, strtok(NULL, "@"));
                mr1.date.year = atoi(strtok(NULL, "@"));
                mr1.date.month = atoi(strtok(NULL, "@"));       // ����ü�� ���� ����
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
            case 'd':		// ���೯¥ Ȯ�� ( �� )
            case 'w':		// ( ���� ) ���� ������ Ȯ��
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
            case 'b':		// ���� ���� Ȯ��
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
            case 'r':		// ���� ���
                textcolor(GREEN);
                printf("��ϵǾ����ϴ�.");
                textcolor(WHITE);
                break;
            case 'e':		// ����
                ee = atoi(strtok(NULL, "@"));
                /*textcolor(GREEN);
                printf("����Ǿ����ϴ�.");
                textcolor(WHITE);*/
                break;
            case 'u':		// ����
                textcolor(GREEN);
                printf("���� ����Ǿ����ϴ�");
                textcolor(WHITE);
                break;
            case 'n':		// �������� ���
                textcolor(GREEN);
                printf("��ϵǾ����ϴ�");
                textcolor(WHITE);
                break;
            case 'i':	// �� ���� ����
            case 't':	// ������ ���� ����
                gotoxy(10, 20);
                textcolor(YELLOW);
                printf("����Ǿ����ϴ�");
                break;
            case 'y':		// ������ Ż��
            case 'v':		// �� Ż��
                gotoxy(10, 20);
                textcolor(YELLOW);
                printf("Ż��Ǿ����ϴ�");
                c1 = 'q';
                break;
            case 'q':		// ����
                gotoxy(10, 20);
                printf("����Ǿ����ϴ�");
                closesocket(sock);
                exit(0);
                break;
            }
            
        }
    }
}