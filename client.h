#pragma once
#define ID 16			// ID 배열크기
#define PW 20			// PW 배열크기
#define MAX 12			// 이름 배열크기
#define NUM 16			// 번호(전화번호, 등록번호) 배열크기
#define RECORD 500		// 진료 기록 배열크기
#define LO 6			// 지역과 코드 배열크기
#define BUF_SIZE 100
#include <time.h>

typedef struct today {	// 날짜 구조체
	int year;			// 년
	int month;			// 월
	int day;			// 일
	int hour;			// 시간
}TODAY;

typedef struct local {	// 지역 구조체
	char city[LO];		// 시
	char dong[LO];		// 동
}LOCAL;

typedef struct client {	// 고객 구조체
	char name[MAX];		// 이름
	char num[NUM];		// 전화번호
	char id[ID];		// 고객ID
	char pw[PW];		// P.W
	struct client* next;// 다음 노드
}CLIENT;

typedef struct manager {// 관리자(병원) 구조체
	char name[MAX];		// 병원명
	LOCAL lo;			// 지역 구조체
	char id[ID];		// 관리자ID
	char pw[PW];		// P.W
	struct manager* next;// 다음 노드
}MANAGER;

typedef struct animal {	// 반려동물 구조체
	char num[NUM];		// 동물등록번호
	TODAY bd;			// 생일 날짜 구조체
	char c_id[ID];		// 고객ID
	struct animal* next;// 다음 노드
}ANIMAL;

typedef struct mr {		// 진료 기록 구조체
	char num[NUM];		// 동물등록번호
	TODAY date;			// 진료 날짜
	char mgName[MAX];	// 병원명
	char record[RECORD];// 기록
	struct mr* next;	// 다음 노드
}MR;

typedef struct reser {	// 예약.접종 관리 구조체
	char c_id[ID];		// 고객ID
	char mg_id[ID];		// 관리자(병원)ID
	char num[NUM];		// 동물등록번호
	TODAY date;			// 예약.접종날짜
	char cord[LO];		// 예약.접종 분류 코드
	struct reser* next;	// 다음 노드
}RESER;

struct tm* todayDate();

void myRecode1(char aniNum);