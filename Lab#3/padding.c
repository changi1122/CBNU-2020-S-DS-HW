#include <stdio.h>

struct student {
    char lastName[13];  /* 13 bytes */
    int studentId;      /* 4 bytes */
    short grade;        /* 2 bytes */
};

int main() {
    printf("[----- [이우창] [2019038074] -----]\n\n");

    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student));
    printf("size of int = %ld\n", sizeof(int));
    printf("size of short = %ld\n", sizeof(short));

    /* 단순 구조체 멤버 크기 합은 19 bytes이지만, 실제 구조체 크기는 24 bytes이다. */

    return 0;
}