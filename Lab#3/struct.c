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
    printf("[----- [이우창] [2019038074] -----]\n\n");

    struct student1 st1 = {'A', 100, 'A'};

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.lastName = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'}; //typedef를 사용하면 구조체 선언시 struct를 생략 가능
    
    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.lastName = %c\n", st2.grade);

    student2 st3;
    st3 = st2; //깊은 복사
    
    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.lastName = %c\n", st3.grade);

    //비교
    /*
    if(st3 == st2)      //오류 발생 : 구조체 직접 비교 불가능
        printf("equal\n");
    else
        printf("not equal\n");
    */

   return 0;
}