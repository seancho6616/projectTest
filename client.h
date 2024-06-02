#pragma once
#define ID 20			// ID �迭ũ��
#define PW 20			// PW �迭ũ��
#define MAX 12			// �̸� �迭ũ��
#define NUM 16			// ��ȣ(��ȭ��ȣ, ��Ϲ�ȣ) �迭ũ��
#define RECORD 500		// ���� ��� �迭ũ��
#define LO 6			// ������ �ڵ� �迭ũ��
#define BUF_SIZE 100

char c;	// ��� �ڵ�
char rc;	// ���Ź��� ��� �ڵ�

typedef struct today {	// ��¥ ����ü
	int year;					// ��
	int month;				// ��
	int day;					// ��
	int hour;				// �ð�
}TODAY;

typedef struct local {	// ���� ����ü
	char city[LO];			// ��
	char dong[LO];		// ��
}LOCAL;

typedef struct client {	// �� ����ü
	char name[MAX];		// �̸�
	char num[NUM];		// ��ȭ��ȣ
	char id[ID];		// ��ID
	char pw[PW];		// P.W
	struct client* next;// ���� ���
}CLIENT;

typedef struct manager {// ������(����) ����ü
	char name[MAX];		// ������
	LOCAL lo;			// ���� ����ü
	char id[ID];		// ������ID
	char pw[PW];		// P.W
	struct manager* next;// ���� ���
}MANAGER;

typedef struct animal {	// �ݷ����� ����ü
	char num[NUM];		// ������Ϲ�ȣ
	TODAY bd;			// ���� ��¥ ����ü
	char c_id[ID];		// ��ID
	struct animal* next;// ���� ���
}ANIMAL;

typedef struct mr {		// ���� ��� ����ü
	char num[NUM];		// ������Ϲ�ȣ
	TODAY date;			// ���� ��¥
	char mgName[MAX];	// ������
	char record[RECORD];// ���
	struct mr* next;	// ���� ���
}MR;

typedef struct reser {	// ����.���� ���� ����ü
	char c_id[ID];		// ��ID
	char mg_id[ID];		// ������(����)ID
	char num[NUM];		// ������Ϲ�ȣ
	TODAY date;			// ����.������¥
	char cord[LO];		// ����.���� �з� �ڵ�
	struct reser* next;	// ���� ���
}RESER;

TODAY today;
CLIENT client;
MANAGER manager;
ANIMAL animal;
MR mr;
RESER reser;

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;

			
char id, pw;		// �α����Ϸ��� id, pw
char join;
char animNum;

void gotoxy(int x, int y);

void todayDate();

void myRecode1();

void myRecode2();

void reservationDate();

void reservationDerails();

void editInformation();

