#include <stdio.h>

int main()
{
    printf("----- 이우창  2019038074 -----\n\n");

    int i;
    int *ptr;
    int **dptr;

    i = 1234;
    
    printf("[checking values before ptr = &i]\n");
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);

    // ptr에 i의 주소 대입
    ptr = &i;

    printf("\n[checking values after ptr = &i]\n");
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);
    printf("value of *ptr == %d\n", *ptr);

    /* 포인터 ptr의 담고 있는 주소, 자신의 주소, 저장된 i의 주소를 이용해 역참조하는 걸 보입니다. */

    // dptr에 ptr의 주소 대입
    dptr = &ptr;

    printf("\n[checking values after dptr = &ptr]\n");
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of dptr == %p\n", dptr);
    printf("address of dptr == %p\n", &dptr);
    printf("value of *dptr == %p\n", *dptr);
    printf("value of **dptr == %d\n", **dptr);

    /* 이중 포인터 dptr에 대해 담고 있는 주소, 자신의 주소, 한번 역참조한 값, 두번 역참조한 값을 보입니다. */

    // *ptr의 값 변경
    *ptr = 7777;
    
    printf("\n[after *ptr = 7777]\n");
    printf("value of i == %d\n", i);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of **dptr == %d\n", **dptr);
    
    /* ptr의 값을 이용해 i를 변경한 걸 보입니다. */

    // **dptr의 값 변경
    **dptr = 8888;

    printf("\n[after **dptr = 8888]\n");
    printf("value of i == %d\n", i);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of **dptr == %d\n", **dptr);

    /* 이중 포인터 dptr의 값을 이용해 i를 변경한 걸 보입니다. */

    return 0;
}