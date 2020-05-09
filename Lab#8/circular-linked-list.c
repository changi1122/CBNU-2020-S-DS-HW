/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("[----- 2019038074 이우창 -----]\n\n");

	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	/* 리스트의 앞부터 할당 해제 */
	listNode* temp = h->rlink;
	listNode* prev = NULL;
	while(temp != h)
	{
		prev = temp;
		temp = temp->rlink;
		free(prev);
	}

	/* 헤드노드 해제 */
	free(h);

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* new = (listNode*)malloc(sizeof(listNode));
	new->key = key;
	
	listNode* last = h->llink;

	/* new의 rlink는 h로, new의 llink는 last로 함 */
	/* last의 rlink는 new로, h의 llink는 new로 함 */
	new->rlink = h;
	new->llink = last;
	last->rlink = new;
	h->llink = new;

	return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if(h->rlink != h) { // list가 빈 상태가 아니라면
		listNode* last = h->llink;

		/* last->llink의 rlink는 last->rlink로, h의 llink는 last->llink로 함 */
		last->llink->rlink = last->rlink;
		h->llink = last->llink;

		/* last 할당 해제 */
		free(last);
	}
	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* new = (listNode*)malloc(sizeof(listNode));
	new->key = key;
	
	listNode* first = h->rlink;

	/* new의 rlink는 first, new의 llink는 h */
	/* first의 llink는 new, h의 rlink는 new */
	new->rlink = first;
	new->llink = h;
	first->llink = new;
	h->rlink = new;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if(h->rlink != h) { //list가 빈 상태가 아니라면
		listNode* first = h->rlink;

		/* first->rlink의 llink는 h, h의 rlink는 first->rlink */
		first->rlink->llink = h;
		h->rlink = first->rlink;

		/* first 할당 해제 */
		free(first);
	}
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	/* list의 모든 노드에서 rlink와 llink를 교환 */
	listNode* temp = h->rlink;
	while(temp != h) {
		listNode* swap = temp->rlink;
		temp->rlink = temp->llink;
		temp->llink = swap;

		temp = temp->llink;
	}

	/* h의 rlink와 llink를 교환 */
	listNode* swap = h->rlink;
	h->rlink = h->llink;
	h->llink = swap;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* new = (listNode*)malloc(sizeof(listNode));
	new->key = key;

	/* search를 list를 따라 이동시키며 큰값이 나오는 노드이면 break */
	listNode* search = h->rlink;
	while(search != h) {
		if(key < search->key)
			break;
		search = search->rlink;
	}

	/* new의 rlink는 search, new의 llink는 search->llink */
	/* search->llink->rlink는 new, search->llink는 new */
	new->rlink = search;
	new->llink = search->llink;
	search->llink->rlink = new;
	search->llink = new;

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	/* 삭제할 노드 찾기 */
	listNode* search = h->rlink;
	while(search != h) {
		if(key == search->key)
			break;
		search = search->rlink;
	}

	if (search != h)
	{
		/* search->llink의 rlink는 search->rlink, search->rlink의 llink는 search->llink */
		search->llink->rlink = search->rlink;
		search->rlink->llink = search->llink;

		/* search 할당 해제 */
		free(search);
	}
	else // 삭제할 노드가 없는 경우
	{
		printf("cannot find the node for key = %d\n", key);
	}
	
	return 0;
}
