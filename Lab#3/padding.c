//EUC-KR

#include <stdio.h>

struct student {
    char lastName[13];  /* 13 bytes */
    int studentId;      /* 4 bytes */
    short grade;        /* 2 bytes */
};

int main() {
    printf("[----- [�̿�â] [2019038074] -----]\n\n");

    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student));
    printf("size of int = %ld\n", sizeof(int));
    printf("size of short = %ld\n", sizeof(short));

    /* �ܼ� ����ü ��� ũ�� ���� 19 bytes������, ���� ����ü ũ��� 24 bytes�̴�. */

    return 0;
}