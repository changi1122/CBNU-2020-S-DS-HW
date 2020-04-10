#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("[----- [이우창] [2019038074] -----]\n\n");
    
    // 정수 배열
    int list[5];
    int *plist[5] = {NULL, };

    // 정수 포인터
    plist[0] = (int *)malloc(sizeof(int)); //힙에서 동적 할당 받음.

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;
    
    printf("value of list[0] = %d\n", list[0]); 
    printf("address of list[0]          = %p\n", &list[0]);
    printf("value of list               = %p\n", list);
    printf("address of list (&list)     = %p\n", &list);
    /* 배열 이름, 0번째 주소, 배열의 주소 모두 동일 */

    printf("-----------------------------------------\n\n");
    printf("value of list[1]            = %d\n", list[1]);
    printf("address of list[1]          = %p\n", &list[1]);
    printf("value of *(list + 1)        = %d\n", *(list + 1));
    printf("address of list + 1         = %p\n", list + 1);
    /* 배열 주소에 증감 연산시 int크기 만큼 이동*/

    printf("-----------------------------------------\n\n");
    printf("value of *plist[0]          = %d\n", *plist[0]);
    printf("&plist[0]                   = %p\n", &plist[0]);
    printf("&plist                      = %p\n", &plist);
    printf("plist                       = %p\n", plist);
    printf("plist[0]                    = %p\n", plist[0]); //동적 할당된 영역의 주소 출력됨.
    printf("plist[1]                    = %p\n", plist[1]);
    printf("plist[2]                    = %p\n", plist[2]);
    printf("plist[3]                    = %p\n", plist[3]);
    printf("plist[4]                    = %p\n", plist[4]);

    free(plist[0]);

    return 0;
}