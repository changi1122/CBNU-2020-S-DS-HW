/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	/* 최소값을 선택하여 가장 값으로 교체하는 정렬 */

	int min;		// 최소값을 저장
	int minindex;   // 최소값의 인덱스 저장
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		/* minindex를 정렬되지 않은 가장 앞 인덱스로 설정 */
		/* min을 가장 앞 인덱스의 값으로 설정 */
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			/* 가장 작은 값 찾기 */
			/* min, minindex 갱신 */
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		/* 가장 작은 값과 가장 앞의 원소를 교체 */
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	/* 정렬되지 않은 집합에서 원소를 선택하여 */
	/* 정렬된 집합에 삽입하는 정렬 */

	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		/* t에 정렬된 집합에 삽입할 원소 저장 */
		/* j를 정렬된 집합의 마지막 인덱스로 설정 */
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			/* 현재 a[j - 1] 원소가 삽입할 원소보다 작으면 j--로 이동한다 */
			/* 앞에 삽입할 것이므로 a[j - 1] 원소를 뒤로 옮긴다 */
			a[j] = a[j-1];
			j--;
		}
		/* 앞의 원소가 t보다 작아지면 반복문 탈출 후 */
		/* j 위치에 t 삽입 */
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	/* 인접한 두 원소를 검사하여 정렬 */

	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	/* 모든 원소가 정렬될 때까지 반복 */
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		/* 한번 버블이 지나가면 뒤쪽 원소가 하나씩 제일 큰 것이 보장됨 */
		for (j = 1; j < MAX_ARRAY_SIZE - i; j++)
		{
			/* 두 인접 원소에서 앞의 원소가 크면 서로 교환 */
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	/* 삽입정렬을 보완한 알고리즘으로 */
	/* h만큼 떨어진 요소를 삽입하는 정렬 방법 */

	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	/* 간격을 줄이며 반복 */
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				/* v에 삽입될 a[j]를 저장 */
				v = a[j];

				k = j;
				/* v가 a[k-h]보다 작으면 서로 교체함 */
				while (k > h-1 && a[k-h] > v)
				{
					/* 작은 동안 계속 교체, 이동  */
					a[k] = a[k-h];
					k -= h;
				}
				/* v를 위치에 삽입 */
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	/* 피벗을 중심으로 분할하여 정렬하는 방법 */

	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];	// 마지막 원소 : 피벗
		i = -1;  	// -1 인덱스부터
		j = n - 1; 	// 마지막 인덱스부터

		while(1)
		{
			/* 앞에서부터 이동, 피벗보다 큰 원소에서 정지 */
			while(a[++i] < v);
			/* 뒤에서부터 이동, 피벗보다 작은 원소에서 정지 */
			while(a[--j] > v);

			/* 두 값이 같아지면 탈출 */
			if (i >= j) break;

			/* 아니면 교환 후 반복 */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		/* 중심 위치에 피벗 삽입 */
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		/* 오른쪽 부분 집합, 왼쪽 부분 집합에 재귀 호출 */
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
	/* 제산(division) 함수 */
	/* 모드 연산자(%)에 의해 홈 버킷 결정 */
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		/* 각 원소의 값을 해시테이블 인덱스로 변환 */
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			/* hashtable[hashcode]에 값이 없으면 원소 저장 */
			hashtable[hashcode] = key;
		} else 	{
			/* hashtable[hashcode]에 값이 있으면 */
			index = hashcode;

			/* 빈 버켓까지 인덱스 증가 */
			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			/* 빈 버켓에 원소 저장 */
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{	
	/* key를 해시테이블 인덱스로 변환 */
	int index = hashCode(key);

	/* 해당 인덱스에 값이 바로 있으면 바로 인덱스 반환 */
	if(ht[index] == key)
		return index;

	/* 바로 없으면 인덱스를 증가시키며 찾아 인덱스 반환 */
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



