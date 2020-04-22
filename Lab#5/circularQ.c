/*
 * circularQ.c
 * 
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
	printf("[----- 이우창 2019038074 -----]\n\n");

	QueueType *cQ = createQueue();
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* 큐가 비었는지 1 또는 0으로 반환 */
int isEmpty(QueueType *cQ)
{
	/* front와 rear의 값이 같을 때 큐가 빔 */
	/* 큐의 최대 element 개수가 MAX_QUEUE_SIZE - 1이면, full이 front == rear에 해당되지 않음 */
    return (cQ->front == cQ->rear);
}

/* 큐가 가득 찼는지 1 또는 0으로 반환 */
int isFull(QueueType *cQ)
{
	/* rear의 다음 element가 front의 element이면 큐가 가득 참 */
	/* 원형 큐에서는 rear가 마지막 element일 수도 있기에 MAX_QUEUE_SIZE로 mod 연산함 */
    return ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front);
}


/* 큐에 item을 삽입 */
void enQueue(QueueType *cQ, element item)
{
	if (isFull(cQ)) { //큐가 가득 참
		fprintf(stderr, "\n큐가 가득 찼습니다.\n");
		return;
	}

	/* rear가 마지막 element이면 0으로 이동하기 위해 MAX_QUEUE_SIZE로 mod 연산함 */
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	//queue[rear]에 item 대입
	cQ->queue[cQ->rear] = item;

	return;
}

/* 큐에서 item에 데이터를 반환하고, 삭제 */
void deQueue(QueueType *cQ, element *item)
{
	if (isEmpty(cQ)) { //큐가 빔
		fprintf(stderr, "\n큐가 비었습니다.\n");
		return;
	}

	/* front가 마지막 element이면 0으로 이동하기 위해 MAX_QUEUE_SIZE로 mod 연산함 */
	cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;

	//item이 가리키는 변수에 데이터를 반환
	*item = cQ->queue[cQ->front];

    return;
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


