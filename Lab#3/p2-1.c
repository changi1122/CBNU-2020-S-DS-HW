//EUC-KR

#include <stdio.h>

#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main()
{
    printf("[----- [�̿�â] [2019038074] -----]\n\n");

    for(i = 0; i < MAX_SIZE; i++)
        input[i] = i;

    /* call by reference Ȯ�� ���� input�� �ּ� */
    printf("address of input = %p\n", input);

    answer = sum(input, MAX_SIZE);
    printf("The sum is: %f\n", answer);
}

float sum(float list[], int n)
{
    printf("value of list = %p\n", list);
    printf("address of list = %p\n\n", &list); //�Լ� ȣ��� list��� ������ ������ ���� (������ �ּ� ����)

    int j;
    float tempsum = 0;
    for(j = 0; j < n; j++)
        tempsum += list[j];
    return tempsum;
}