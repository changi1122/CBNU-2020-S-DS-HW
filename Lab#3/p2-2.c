//EUC-KR
#include <stdio.h>

void print1 (int *ptr, int rows);

int main()
{
    printf("[----- [�̿�â] [2019038074] -----]\n\n");

    int one[] = {0, 1, 2, 3, 4};

    printf("one     = %p\n", one);
    printf("&one    = %p\n", &one);
    printf("&one[0] = %p\n", &one[0]);
    printf("\n");
    
    /* ��� �迭�� ó�� �ּҰ� ��µȴ�. */

    print1(&one[0], 5);

    return 0;
}

// �����ͷ� ������ �迭 ���
void print1 (int *ptr, int rows)
{
    int i;
    printf("Address \t  Contents\n");
    for (i = 0; i < rows; i++)
        printf("%p \t  %5d\n", ptr + i, *(ptr + i));
    printf("\n");
}