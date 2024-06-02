#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include "client.h"



int main()
{
    todayDate();
    

    char name;
    printf("%d-%d-%d-%d\n", today.year, today.month, today.day, today.hour);
 
    return 0;
}

