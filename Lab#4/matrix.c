#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 함수 프로토타입 */
int** create_matrix(int row, int col); //2차원 배열 생성, 이중 포인터로 반환
int free_matrix(int** matrix, int row, int col); //2차원 배열의 메모리 할당 해제
void print_matrix(int** matrix, int row, int col); //행렬 출력
int fill_data(int** matrix, int row, int col); //행렬에 난수값 채움
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //matrix를 전치하여 matrix_t에 반환
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col); //matrix_a와 matrix_b를 더해 matrix_sum에 반환
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col); //matrix_a에서 matrix_b를 빼 matrix_sub에 반환
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col); //matrix_a와 matrix_t를 곱해 matrix_axt에 반환


int main()
{
    printf("[----- 이우창 2019038074 -----]\n");

    //난수 생성
    srand(time(NULL));

    //입력
    int row, col;
    printf("행의 수 : ");
    scanf("%d", &row);
    printf("열의 수 : ");
    scanf("%d", &col);


    //행렬 생성, 데이터 채우기
    int** matrix_a = create_matrix(row, col);
    if (fill_data(matrix_a, row, col) == -1)
        return -1;
    
    int** matrix_b = create_matrix(row, col);
    if (fill_data(matrix_b, row, col) == -1)
        return -1;
    
    //행렬 출력
    printf("\nA = \n");
    print_matrix(matrix_a, row, col);

    printf("\nB = \n");
    print_matrix(matrix_b, row, col);

    
    //행렬 덧셈
    int** ret = create_matrix(row, col);
    if (addition_matrix(matrix_a, matrix_b, ret, row, col) == -1)
        return -1;

    printf("\nA + B = \n");
    print_matrix(ret, row, col);


    //행렬 뺄셈
    if (subtraction_matrix(matrix_a, matrix_b, ret, row, col) == -1)
        return -1;

    printf("\nA - B = \n");
    print_matrix(ret, row, col);

    //전치 행렬
    int** matrix_t = create_matrix(col, row);
    if (transpose_matrix(matrix_a, matrix_t, row, col) == -1)
        return -1;

    printf("\nAt = \n");
    print_matrix(matrix_t, col, row);

    //행렬과 전치행렬의 곱
    int** multi = create_matrix(row, row);
    if (multiply_matrix(matrix_a, matrix_t, multi, row, col) == -1)
        return -1;

    printf("\nA x At = \n");
    print_matrix(multi, row, row);

    //메모리 할당 해제
    free_matrix(matrix_a, row, col);
    free_matrix(matrix_b, row, col);
    free_matrix(ret, row, col);
    free_matrix(matrix_t, col, row);
    free_matrix(multi, row, row);

    return 0;
}

/* 2차원 배열 생성, 이중 포인터로 반환 */
int** create_matrix(int row, int col)
{
    //전처리 검사
    if (row <= 0 || col <= 0) {
        printf("행 또는 열의 크기가 잘못되었습니다.\n");
        return NULL;
    }

    //int 포인터의 배열 공간(행) 할당
    int** matrix = (int**)malloc(sizeof(int*) * row);
    
    //각 행마다 배열 공간 할당
    for (int r = 0; r < row; r++) {
        matrix[r] = (int*)malloc(sizeof(int) * col);
    }


    //후처리 검사
    if (matrix == NULL) {
        printf("공간 할당이 잘못되었습니다.\n");
        return NULL;
    }
    else {
        for (int r = 0; r < row; r++) {
            if (matrix[r] == NULL) {
                printf("공간 할당이 잘못되었습니다.\n");
                return NULL;
            }
        }
    }

    return matrix;
}

/* 2차원 배열의 메모리 할당 해제 */
int free_matrix(int** matrix, int row, int col)
{
    //전처리 검사
    if (matrix == NULL || row <= 0 || col <= 0) {
        printf("할당 해제할 배열이 잘못되었습니다.\n");
        return -1;
    }

    //열부터 할당 해제
    for (int r = 0; r < row; r++) {
        free(matrix[r]);
    }
    //포인터 배열 할당 해제
    free(matrix);

    return 1;
}

/* 행렬 출력 */
void print_matrix(int** matrix, int row, int col)
{
    //전처리 검사
    if (row <= 0 || col <= 0) {
        printf("행 또는 열의 크기가 잘못되었습니다.\n");
        return;
    }
    if (matrix == NULL) {
        printf("함수의 매개변수 'matrix'는 미리 메모리 공간을 할당받아야 합니다.\n");
        return;
    }

    //출력
    printf("\n");
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++)
            printf("%2d ", matrix[r][c]);
        printf("\n");
    }

    return;
}

/* matrix 행렬에 난수값 채움 */
int fill_data(int** matrix, int row, int col)
{
    //전처리 검사
    if (row <= 0 || col <= 0) {
        printf("행 또는 열의 크기가 잘못되었습니다.\n");
        return -1;
    }
    if (matrix == NULL) {
        printf("함수의 매개변수 'matrix'는 미리 메모리 공간을 할당받아야 합니다.\n");
        return -1;
    }
    

    //난수 대입
    for (int r = 0; r < row; r++)
        for (int c = 0; c < col; c++)
            matrix[r][c] = rand() % 20;

    return 1;
}

/* matrix를 전치하여 matrix_t에 반환, matrix_t는 col x row 행렬임이 보장되어야 함.*/
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    //전처리 검사
    if (row <= 0 || col <= 0) {
        printf("행 또는 열의 크기가 잘못되었습니다.\n");
        return -1;
    }
    if (matrix == NULL || matrix_t == NULL) {
        printf("함수의 매개변수 'matrix'와 'matrix_t'는 미리 메모리 공간을 할당받아야 합니다.\n");
        return -1;
    }

    //전치하여 대입
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++)
            matrix_t[c][r] = matrix[r][c];
    }

    return 1;
}

/* matrix_a와 matrix_b를 더해 matrix_sum에 반환, matrix_sum은 row x col 행렬임이 보장되어야 함. */
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col)
{
    //전처리 검사
    if (row <= 0 || col <= 0) {
        printf("행 또는 열의 크기가 잘못되었습니다.\n");
        return -1;
    }
    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
        printf("함수의 매개변수 'matrix_a'와 'matrix_b', 'matrix_sum'은 미리 메모리 공간을 할당받아야 합니다.\n");
        return -1;
    }

    //두 행렬을 더한 후 대입
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++)
            matrix_sum[r][c] = matrix_a[r][c] + matrix_b[r][c];
    }

    return 1;
}

/* matrix_a에서 matrix_b를 빼 matrix_sub에 반환, matrix_sub는 row x col 행렬임이 보장되어야 함. */
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)
{
    //전처리 검사
    if (row <= 0 || col <= 0) {
        printf("행 또는 열의 크기가 잘못되었습니다.\n");
        return -1;
    }
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
        printf("함수의 매개변수 'matrix_a'와 'matrix_b', 'matrix_sub'은 미리 메모리 공간을 할당받아야 합니다.\n");
        return -1;
    }

    //matrix_a에서 matrix_b를 뺀 후 대입
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++)
            matrix_sub[r][c] = matrix_a[r][c] - matrix_b[r][c];
    }

    return 1;
}

/* matrix_a와 matrix_t를 곱해 matrix_axt에 반환, matrix_axt는 row x row 행렬임이 보장되어야 함. */
/* matrix_t는 col x row 행렬임이 보장되어야 함. */
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)
{
    //전처리 검사
    if (row <= 0 || col <= 0) {
        printf("행 또는 열의 크기가 잘못되었습니다.\n");
        return -1;
    }
    if (matrix_a == NULL || matrix_t == NULL || matrix_axt == NULL) {
        printf("함수의 매개변수 'matrix_a'와 'matrix_t', 'matrix_sub'은 미리 메모리 공간을 할당받아야 합니다.\n");
        return -1;
    }

    //전치 행렬 만들기
    int success = transpose_matrix(matrix_a, matrix_t, row, col);
    if (success == -1) {
        printf("전치행렬을 만들 수 없습니다.\n");
        return -1;
    }

    //행렬곱 계산
    for (int r1 = 0; r1 < row; r1++) {
        for (int r2 = 0; r2 < row; r2++) {
            
            int sum = 0;

            for (int c = 0; c < col; c++)
                sum += matrix_a[r1][c] * matrix_t[c][r2];

            matrix_axt[r1][r2] = sum;
        }
    }

    return 1;
}