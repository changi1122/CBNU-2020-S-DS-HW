//EUC-KR

#include <stdio.h>

int main(void)
{
    printf("----- �̿�â  2019038074 -----\n\n");

    char charType;
    int integerType;
    float floatType;
    double doubleType;

    // �� ������ ũ��(����Ʈ) ���
    printf("Size of char: %ld byte\n", sizeof(charType));
    printf("Size of int: %ld byte\n", sizeof(integerType));
    printf("Size of float: %ld byte\n", sizeof(floatType));
    printf("Size of double: %ld byte\n", sizeof(doubleType));
    /* char, int, float, double ������ ũ�⸦ Ȯ���մϴ�. */

    printf("-----------------------------------------\n");

    // �� �ڷ����� ũ��(����Ʈ) ���
    printf("Size of char: %ld byte\n", sizeof(char));
    printf("Size of int: %ld byte\n", sizeof(int));
    printf("Size of float: %ld byte\n", sizeof(float));    
    printf("Size of double: %ld byte\n", sizeof(double));
    /* char, int, float, double �ڷ����� ũ�⸦ Ȯ���մϴ�. */

    printf("-----------------------------------------\n");

    // �� �ڷ����� �������� ũ��(����Ʈ) ���
    printf("Size of char*: %ld byte\n", sizeof(char*));
    printf("Size of int*: %ld byte\n", sizeof(int*));
    printf("Size of float*: %ld byte\n", sizeof(float*));
    printf("Size of double*: %ld byte\n", sizeof(double*));
    /* ������ ������ ������ �ּҸ� ��⿡ �ڷ����� �޶� �� ũ��� ���ٴ� �� �� �� �ֽ��ϴ�. */

    return 0;
}