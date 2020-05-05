/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("[----- 2019038074 이우창 -----]\n\n");

	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	/* 이미 할당된 공간이 있으면 freeList 호출 */
	if(*h != NULL)
		freeList(*h);

	/* headNode만큼 공간을 할당받아 *h에 그 주소를 저장 */
	/* headnode의 값을 바꿔야하므로, &headnode를 매개변수로 받음 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 0;
}

int freeList(headNode* h){
	/* 리스트의 앞부터 할당 해제 */
	listNode* temp = h->first;
	listNode* prev = NULL;
	while(temp != NULL)
	{
		prev = temp;
		temp = temp->rlink;
		free(prev);
	}

	/* 헤드노드 해제 */
	free(h);

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* last = h->first;
	while(last && last->rlink != NULL)
	{
		last = last->rlink;
	}
	
	/* 마지막 노드의 right를 temp로, temp의 llink를 마지막 노드로 함 */
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;
	temp->rlink = NULL;
	temp->llink = last;

	if(last)
		last->rlink = temp;
	else //첫 노드인 경우
	{
		h->first = temp;
	}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* last = h->first;
	while(last && last->rlink != NULL)
	{
		last = last->rlink;
	}

	/* 이전 노드가 있다면, 이전 노드의 rlink를 NULL로 하고, last는 할당 해제 */
	if(last != NULL) //리스트가 빈 상태가 아니라면
	{
		if(last->llink != NULL)
			last->llink->rlink = NULL;
		else //삭제할 노드가 첫 노드라면
			h->first = NULL;
		
		free(last);
	}

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	/* temp->rlink는 first, first->llink는 temp, first가 temp를 가리키도록 함 */
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;
	temp->rlink = h->first;
	temp->llink = NULL;

	if(h->first != NULL)
		h->first->llink = temp;
	
	h->first = temp;
	
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/* temp에 첫 노드 넣고, first가 두번째 노드 가리키게 함 */
	/* 두번째 노드의 llink를 NULL로 만든 후, temp를 할당 해제*/
	if(h->first != NULL) //리스트가 빈 상태가 아니라면
	{
		listNode* temp = h->first;
		h->first = h->first->rlink;

		if (h->first != NULL)
			h->first->llink = NULL;

		free(temp);			
	}

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	/* first를 마지막 노드 가리키게 하고, 모든 노드 rlink, llink 바꾸기 */
	listNode* temp = h->first;
	while(temp)
	{
		listNode* swap = temp->rlink;
		temp->rlink = temp->llink;
		temp->llink = swap;

		if(temp->llink != NULL)
			temp = temp->llink;
		else //마지막 노드이면
			break;
	}

	h->first = temp;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;
	
	/* 리스트를 따라가다가 key보다 큰값이 나오는 노드가 있으면 삽입 후 break */
	listNode* search = h->first;
	if(search != NULL)
	{
		while(search != NULL)
		{
			if(key < search->key)
			{
				if(search->llink == NULL) //첫 노드 앞에 삽입하는 경우
				{
					temp->rlink = search;
					temp->llink = NULL;
					search->llink = temp;
					h->first = temp;
				}
				else
				{
					temp->rlink = search;
					temp->llink = search->llink;
					search->llink->rlink = temp;
					search->llink = temp;
				}
				break;
			}

			if(search->rlink != NULL)
				search = search->rlink;
			else //마지막 노드 뒤에 삽입하는 경우
			{
				temp->rlink = NULL;
				temp->llink = search;
				search->rlink = temp;
				break;
			}
		}
	}
	else //리스트가 빈 상태이면
	{
		free(temp);
		insertFirst(h, key);
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* 리스트를 따라가다가 key와 일치하는 노드가 있으면 삭제 */
	listNode* search = h->first;

	while(search != NULL)
	{
		if(search->key == key)
			break;

		search = search->rlink;
	}

	if(search != NULL) //삭제할 항목이 있다면
	{
		if(search->llink == NULL) //첫 노드 삭제시
			h->first = search->rlink;

		if(search->llink != NULL) //첫 노드 삭제가 아니면
			search->llink->rlink = search->rlink;
		if(search->rlink != NULL) //마지막 노드 삭제가 아니면
			search->rlink->llink = search->llink;
		free(search);	
	}

	return 1;
}


