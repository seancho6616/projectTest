#pragma once
void textcolor(int colorNum);	// 글자 색 변환
void reservationBorder();			// 예약창 테두리
void corrInformation();			// 정보 수정 및 탈퇴
void medicalRecordCheck();		// 진료 기록 확인 - f
void cuMainScreen();				// 고객메인화면 - c
void mgMainScreen();				// 병원메인화면 -  
void medicalRecord();				// 진료내용기입
void reservOrInocul();				// ( 병원 )예약/접종 선택
void reserv();							// ( 병원 )예약
void inocul();							// ( 병원 )접종
void addAnimal();					// 동물등록번호등록
void findReservation();			// 예약내역확인
void startInterface();				// 시작화면
void loginInterface();				// 로그인인터페이스
void joinInterface();				// 회원가입 창
void joinClientInterface();
void joinManagerInterface();

int n;

enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;