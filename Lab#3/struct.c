//EUC-KR

#include <stdio.h>

struct student1 {
    char lastName;
    int studentId;
    char grade;
};

typedef struct {
    char lastName;
    int studentId;
    char grade;
} student2;

int main() {
    printf("[----- [�̿�â] [2019038074] -----]\n\n");

    struct student1 st1 = {'A', 100, 'A'};

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.lastName = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'}; //typedef�� ����ϸ� ����ü ����� struct�� ���� ����
    
    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.lastName = %c\n", st2.grade);

    student2 st3;
    st3 = st2; //���� ����
    
    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.lastName = %c\n", st3.grade);

    //��
    /*
    if(st3 == st2)      //���� �߻� : ����ü ���� �� �Ұ���
        printf("equal\n");
    else
        printf("not equal\n");
    */

   return 0;
}