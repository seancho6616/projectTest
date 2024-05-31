#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "client.h"

struct tm* todayDate(){     // 오늘 날짜 함수
    time_t *curr;
    curr = time(NULL);
    return localtion(&curr);
}

void myRecode1(char c_id){  // 해당 고객 반려동물 목록 불러오는 함수
    //소켓으로 전달
    char anim[5][2];

    for(int i=0; i<5; i++){
        printf("번호 : %s\t이름 : %s\n", anim[i][0], anim[i][1]);
    }    
}

void myRecode2(char animNum){
    // 소켓으로 전달

}

void reservationDate(TODAY d){
    char date[20];
    sprintf(date, "%d@%d@%d@%d", d.year, d.month, d.day, d.hour);

    while(1){

    } 

    printf("%d");
}

void hospitalRecode(){
    
}

void anumalNum(ANIMAL infor){
    char i[40];
    sprintf(i, "%s@%s@%s@%s@%s",
    infor.num, infor.bd.year, infor.bd.month, infor.bd.day, infor.c_id);
}

unsigned WINAPI SendMsg(void* arg){//전송용 쓰레드함수
    SOCKET sock=*((SOCKET*)arg);//서버용 소켓을 전달한다.
    char msg[BUF_SIZE]="";
    gets(msg);//입력을 받는다.
    if(!strcmp(msg,"q")){//q를 입력하면 종료한다.
        send(sock,"q",1,0);//nameMsg를 서버에게 전송한다.
        strcpy(msg, "");
    }
    else{
        send(sock,msg,strlen(msg),0);
        strcpy(msg, "");
    }
    return 0;
}

unsigned WINAPI RecvMsg(void* arg){// 소켓send함수
    SOCKET sock=*((SOCKET*)arg);//서버용 소켓을 전달한다.
    char msg[BUF_SIZE]="";
    int strLen;
    while(1){//반복
        strLen=recv(sock,msg,BUF_SIZE-1,0);//서버로부터 메시지를 수신한다.
        if(strLen==-1) return -1;
        msg[strLen]='\0';//문자열의 끝을 알리기 위해 설정
        if(!strcmp(msg,"q")){
            printf("left\n");
            closesocket(sock);
            exit(0);
        }
        else{
            printf("Result : %s\n", msg);
        }
        strcpy(msg, "");
    }
    return 0;
} 

