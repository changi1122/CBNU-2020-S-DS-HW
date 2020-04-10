#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [이우창] [2019038074] -----]\n\n");

    int list[5];
    int *plist[5];

    list[0] = 10;
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int));

    printf("list[0]     = %d\n", list[0]);
    printf("address of list     = %p\n", list);
    printf("address of list[0]  = %p\n", &list[0]);
    printf("address of list + 0 = %p\n", list + 0);
    printf("address of list + 1 = %p\n", list + 1);
    printf("address of list + 2 = %p\n", list + 2);
    printf("address of list + 3 = %p\n", list + 3);
    printf("address of list + 4 = %p\n", list + 4);
    printf("address of list[4]  = %p\n", &list[4]);

    /* 배열은 연속적, 포인터 타입에 증감 연산시 크기만큼 이동 */

    free(plist[0]);

    return;
}