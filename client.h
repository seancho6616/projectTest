#pragma once
#define ID 20					// ID �迭ũ��
#define PW 20				// PW �迭ũ��
#define MAX 12				// �̸� �迭ũ��
#define NUM 16				// ��ȣ(��ȭ��ȣ, ��Ϲ�ȣ) �迭ũ��
#define RECORD 500		// ���� ��� �迭ũ��
#define LO 6					// ������ �ڵ� �迭ũ��
#define BUF_SIZE 700

char c;				// ��� �ڵ�
char c1;				// Ŭ���̾�Ʈ â �̵��ϱ� ���� �ڵ�
char rc;				// ���Ź��� ��� �ڵ�
char resercheck;	// ���� ��¥ �ߺ� ����
int loinNum;		// �α��� Ȯ�� ����
int num;

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
	char name[MAX];	// �̸�
	char num[NUM];		// ��ȭ��ȣ
	char id[ID];			// ��ID
	char pw[PW];			// P.W
	struct client* next;// ���� ���
}CLIENT;

typedef struct manager {// ������(����) ����ü
	char name[MAX];		// ������
	LOCAL lo;					// ���� ����ü
	char id[ID];				// ������ID
	char pw[PW];				// P.W
	struct manager* next;// ���� ���
}MANAGER;

typedef struct animal {	// �ݷ����� ����ü
	char num[NUM];			// ������Ϲ�ȣ
	TODAY bd;					// ���� ��¥ ����ü
	char c_id[ID];				// ��ID
	struct animal* next;	// ���� ���
}ANIMAL;

typedef struct mr {			// ���� ��� ����ü
	char num[NUM];			// ������Ϲ�ȣ
	TODAY date;				// ���� ��¥
	char mgName[MAX];	// ������
	char record[RECORD];// ���
	struct mr* next;			// ���� ���
}MR;

typedef struct reser {	// ����.���� ���� ����ü
	char c_id[ID];			// ��ID
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
MR mr1;					// ������ �����ϱ� ���� �����ϱ� ���� ����ü
RESER reser1;

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;

int q;
int q2;

char id[ID], pw[PW];		// �α����Ϸ��� id, pw

char animNum[NUM];		// �Է� ���� ������Ϲ�ȣ 

void gotoxy(int x, int y);		// ��ġ �̵��Լ�

void todayDate();				// ������ ��¥ �Լ�

void myRecode1();				// �ش� �� �ݷ����� ��� �ҷ����� �Լ�

void myRecode2();				// �ش� �ݷ����� ���� ��� �θ��� �Լ�

void reservationDate();		// ���� ��¥ Ȯ��( �ٰ����� ���� ��¥ )

void editInformation();		// ���� ���� �� Ż��

void todayReservation();		// ���� ������ Ȯ�� ( ������ ( ���� ) )

void hosptalRecode();			// ���� ���

void animalNum();				// �ݷ����� ���

void reservation();				// ����

void inoculation();				// ����

void beforInterface();			// ù ����ȭ��

void clientInterface();			// �� Ŭ���̾�Ʈ ȭ��

void managerInterface();		// ������ Ŭ���̾�Ʈ ȭ��