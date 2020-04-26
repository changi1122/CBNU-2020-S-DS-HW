/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	listNode* lead = h->first;
	listNode* previous = NULL;
	
	//lead가 큰값이 나오는 노드이면 break
	while(lead) {
		if(key < lead->key)
			break;

		previous = lead;
		lead = lead->link;
	}

	if(previous == NULL) {
		//처음 위치에 삽입
		node->link = h->first;
		h->first = node;
	}
	else {
		//previous 앞에 노드 삽입
		node->link = previous->link;
		previous->link = node;
	}

	return 0;
}

/**
 * list에 마지막에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	
	//마지막 노드가 될 것임으로 link = NULL
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	
	if (h->first == NULL) {
		//리스트가 빈 경우
		h->first = node;
	}
	else {
		//마지막 노드까지 이동 후 link = node
		listNode* temp = h->first;
		while(temp->link != NULL) {
			temp = temp->link;
		}

		temp->link = node;
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(!h || h->first == NULL) {
		//리스트가 빈 경우
		printf("리스트가 빔.\n");
		return -1;
	}

	/* h가 가리키는 노드를 두번째 노드로 변경 후 첫 노드를 free */
	listNode* temp = h->first;
	h->first = temp->link;
	free(temp);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if(!h || h->first == NULL) {
		//리스트가 빈 경우
		printf("리스트가 빔.\n");
		return -1;
	}
	
	listNode* lead = h->first;
	listNode* previous = NULL;
	
	//lead를 리스트에 따라 진행
	while(lead) {
		//key와 일치는 노드가 있으면 삭제
		if(lead->key == key)
		{
			if(previous == NULL) {
				//첫 노드이면
				h->first = lead->link;
				free(lead);
			}
			else {
				previous->link = lead->link;
				free(lead);
			}

			break;
		}

		previous = lead;
		lead = lead->link;
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if(!h || h->first == NULL) {
		//리스트가 빈 경우
		printf("리스트가 빔.\n");
		return -1;
	}
	
	/* 마지막 이전 노드의 link = NULL, 마지막 노드를 free */
	listNode* last = h->first;
	listNode* previous = NULL;
	
	while(last->link != NULL) {
		previous = last;
		last = last->link;
	}

	if(previous == NULL) {
		//리스트가 비게된 경우
		h->first = NULL;
		free(last);
	}
	else {
		previous->link = NULL;
		free(last);
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* lead = h->first;
	listNode* trail;
	listNode* middle = NULL;

	/* lead, middle, trail 순으로 리스트를 이동하면서 각 노드가 이전 노드를 가리키도록 한다 */
	while(lead) {
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}

	h->first = middle;

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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

