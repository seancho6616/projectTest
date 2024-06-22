#pragma once
#define ID 20					// ID 배열크기
#define PW 20				// PW 배열크기
#define MAX 12				// 이름 배열크기
#define NUM 16				// 번호(전화번호, 등록번호) 배열크기
#define RECORD 500		// 진료 기록 배열크기
#define LO 6					// 지역과 코드 배열크기
#define BUF_SIZE 700

char c;				// 목록 코드
char c1;				// 클라이언트 창 이동하기 위한 코드
char rc;				// 수신받은 목록 코드
char resercheck;	// 예약 날짜 중복 여부
int loinNum;		// 로그인 확인 여부
int num;

typedef struct today {	// 날짜 구조체
	int year;					// 년
	int month;				// 월
	int day;					// 일
	int hour;				// 시간
}TODAY;

typedef struct local {	// 지역 구조체
	char city[LO];			// 시
	char dong[LO];		// 동
}LOCAL;

typedef struct client {	// 고객 구조체
	char name[MAX];	// 이름
	char num[NUM];		// 전화번호
	char id[ID];			// 고객ID
	char pw[PW];			// P.W
	struct client* next;// 다음 노드
}CLIENT;

typedef struct manager {// 관리자(병원) 구조체
	char name[MAX];		// 병원명
	LOCAL lo;					// 지역 구조체
	char id[ID];				// 관리자ID
	char pw[PW];				// P.W
	struct manager* next;// 다음 노드
}MANAGER;

typedef struct animal {	// 반려동물 구조체
	char num[NUM];			// 동물등록번호
	TODAY bd;					// 생일 날짜 구조체
	char c_id[ID];				// 고객ID
	struct animal* next;	// 다음 노드
}ANIMAL;

typedef struct mr {			// 진료 기록 구조체
	char num[NUM];			// 동물등록번호
	TODAY date;				// 진료 날짜
	char mgName[MAX];	// 병원명
	char record[RECORD];// 기록
	struct mr* next;			// 다음 노드
}MR;

typedef struct reser {	// 예약.접종 관리 구조체
	char c_id[ID];			// 고객ID
	char mg_id[ID];		// 관리자(병원)ID
	char num[NUM];		// 동물등록번호
	TODAY date;			// 예약.접종날짜
	char cord[LO];		// 예약.접종 분류 코드
	struct reser* next;	// 다음 노드
}RESER;

TODAY today;			
CLIENT client;
MANAGER manager;
ANIMAL animal;
MR mr1;					// 서버로 전달하기 위해 저장하기 위한 구조체
RESER reser1;

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;

int q;
int q2;

char id[ID], pw[PW];		// 로그인하려는 id, pw

char animNum[NUM];		// 입력 받은 동물등록번호 

void gotoxy(int x, int y);		// 위치 이동함수

void todayDate();				// 오늘의 날짜 함수

void myRecode1();				// 해당 고객 반려동물 목록 불러오는 함수

void myRecode2();				// 해당 반려동물 진료 기록 부르는 함수

void reservationDate();		// 예약 날짜 확인( 다가오는 예약 날짜 )

void editInformation();		// 정보 수정 및 탈퇴

void todayReservation();		// 오늘 예약자 확인 ( 관리자 ( 병원 ) )

void hosptalRecode();			// 진료 기록

void animalNum();				// 반려동물 등록

void reservation();				// 예약

void inoculation();				// 접종

void beforInterface();			// 첫 시작화면

void clientInterface();			// 고객 클라이언트 화면

void managerInterface();		// 관리자 클라이언트 화면