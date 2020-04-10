#include <stdio.h>

int main(void)
{
    printf("----- 이우창  2019038074 -----\n\n");

    char charType;
    int integerType;
    float floatType;
    double doubleType;

    // 각 변수의 크기(바이트) 출력
    printf("Size of char: %ld byte\n", sizeof(charType));
    printf("Size of int: %ld byte\n", sizeof(integerType));
    printf("Size of float: %ld byte\n", sizeof(floatType));
    printf("Size of double: %ld byte\n", sizeof(doubleType));
    /* char, int, float, double 변수의 크기를 확인합니다. */

    printf("-----------------------------------------\n");

    // 각 자료형의 크기(바이트) 출력
    printf("Size of char: %ld byte\n", sizeof(char));
    printf("Size of int: %ld byte\n", sizeof(int));
    printf("Size of float: %ld byte\n", sizeof(float));    
    printf("Size of double: %ld byte\n", sizeof(double));
    /* char, int, float, double 자료형의 크기를 확인합니다. */

    printf("-----------------------------------------\n");

    // 각 자료형별 포인터의 크기(바이트) 출력
    printf("Size of char*: %ld byte\n", sizeof(char*));
    printf("Size of int*: %ld byte\n", sizeof(int*));
    printf("Size of float*: %ld byte\n", sizeof(float*));
    printf("Size of double*: %ld byte\n", sizeof(double*));
    /* 포인터 변수는 변수의 주소를 담기에 자료형이 달라도 그 크기는 같다는 걸 알 수 있습니다. */

    return 0;
}