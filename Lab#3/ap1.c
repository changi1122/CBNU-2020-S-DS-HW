//EUC-KR

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("[----- [�̿�â] [2019038074] -----]\n\n");
    
    // ���� �迭
    int list[5];
    int *plist[5] = {NULL, };

    // ���� ������
    plist[0] = (int *)malloc(sizeof(int)); //������ ���� �Ҵ� ����.

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;
    
    printf("value of list[0] = %d\n", list[0]); 
    printf("address of list[0]          = %p\n", &list[0]);
    printf("value of list               = %p\n", list);
    printf("address of list (&list)     = %p\n", &list);
    /* �迭 �̸�, 0��° �ּ�, �迭�� �ּ� ��� ���� */

    printf("-----------------------------------------\n\n");
    printf("value of list[1]            = %d\n", list[1]);
    printf("address of list[1]          = %p\n", &list[1]);
    printf("value of *(list + 1)        = %d\n", *(list + 1));
    printf("address of list + 1         = %p\n", list + 1);
    /* �迭 �ּҿ� ���� ����� intũ�� ��ŭ �̵�*/

    printf("-----------------------------------------\n\n");
    printf("value of *plist[0]          = %d\n", *plist[0]);
    printf("&plist[0]                   = %p\n", &plist[0]);
    printf("&plist                      = %p\n", &plist);
    printf("plist                       = %p\n", plist);
    printf("plist[0]                    = %p\n", plist[0]); //���� �Ҵ�� ������ �ּ� ��µ�.
    printf("plist[1]                    = %p\n", plist[1]);
    printf("plist[2]                    = %p\n", plist[2]);
    printf("plist[3]                    = %p\n", plist[3]);
    printf("plist[4]                    = %p\n", plist[4]);

    free(plist[0]);

    return 0;
}