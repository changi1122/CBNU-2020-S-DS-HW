//EUC-KR

#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [�̿�â] [2019038074] -----]\n\n");
    
    int **x;

    printf("sizeof(x)   = %lu\n", sizeof(x));   //������ ������ ũ��
    printf("sizeof(*x)  = %lu\n", sizeof(*x));  //������ ������ ũ��
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //int �ڷ����� ũ��

    /* 64bit machine���� ������ ������ ũ��� 8 bytes�̳�, �����Ϸ��� 32bit ���α׷����� �������Ͽ� 4 bytes�� ��µǴ� ���ϴ�. */
}