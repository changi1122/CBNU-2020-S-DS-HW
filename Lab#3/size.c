//EUC-KR

#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [이우창] [2019038074] -----]\n\n");
    
    int **x;

    printf("sizeof(x)   = %lu\n", sizeof(x));   //포인터 변수의 크기
    printf("sizeof(*x)  = %lu\n", sizeof(*x));  //포인터 변수의 크기
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //int 자료형의 크기

    /* 64bit machine에서 포인터 변수의 크기는 8 bytes이나, 컴파일러가 32bit 프로그램으로 컴파일하여 4 bytes가 출력되는 듯하다. */
}