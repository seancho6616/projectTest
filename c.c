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
#include "client.h"
#include "0609.h"

unsigned WINAPI RecMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg); 
	int strLen;
	char* word = NULL;
	while (1) {
		strLen = recv(sock, join, BUF_SIZE - 1, 0);
		if (strLen == -1)
			return -1;
		join[strLen] = '\0';
		if (!strcmp(join, "q")) {
			printf("Client : Disconnection\n");
			closesocket(sock);
			exit(0);
		}
		else {
			word = strtok(join, "@");
			rc = word[0];
			switch (rc) {
				case 'l':
			}

		}
	}

}