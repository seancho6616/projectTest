#pragma once
void textcolor(int colorNum);	// ���� �� ��ȯ
void reservationBorder();			// ����â �׵θ�
void corrInformation();			// ���� ���� �� Ż��
void medicalRecordCheck();		// ���� ��� Ȯ�� - f
void cuMainScreen();				// ������ȭ�� - c
void mgMainScreen();				// ��������ȭ�� -  
void medicalRecord();				// ���᳻�����
void reservOrInocul();				// ( ���� )����/���� ����
void reserv();							// ( ���� )����
void inocul();							// ( ���� )����
void addAnimal();					// ������Ϲ�ȣ���
void findReservation();			// ���೻��Ȯ��
void startInterface();				// ����ȭ��
void loginInterface();				// �α����������̽�
void joinInterface();				// ȸ������ â
void joinClientInterface();
void joinManagerInterface();

int n;

enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;