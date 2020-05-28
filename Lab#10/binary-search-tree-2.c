/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */




int main()
{
	printf("[----- 2019038074 이우창 -----]\n\n");

	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	while(1) {
		// 부모 노드를 스택에 넣으면서 왼쪽 자식 노드로 이동
		for(; node; node = node->left) {
			push(node);
		}

		// 스택에서 pop으로 가져오기
		node = pop();

		if (!node) {
			// 가져올 노드가 없으면
			break;
		}
		// 현재 노드 출력 후 오른쪽 자식 노드에 대해 반복
		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(ptr == NULL) // 트리가 빈 상태
		return;

	enQueue(ptr);
	while(1) {
		// 큐에서 나온 노드를 출력하고 그 노드의 자식 노드들을 큐에 넣는다
		// 큐가 빈 상태가 되면 모든 노드가 출력된 것이다
		ptr = deQueue();
		if (ptr != NULL) {
			printf(" [%d] ", ptr->key);
			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else
		{
			break;
		}
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* parent = head;
	Node* search = head->left;

	// 삭제할 노드를 탐색한다
	while(search) {
		if (search->key == key) // search 노드와 key가 일치
			break;

		parent = search;
		if (search->key > key) // key보다 search 노드가 크면 왼쪽
			search = search->left;
		else // key보다 search 노드가 작으면 오른쪽
			search = search->right;
	}

	if (search == NULL) {
		// 일치하는 노드를 못 찾음
		return -1;
	}

	if (search->left == NULL && search->right == NULL) {
		// 리프 노드이면 바로 삭제
		if (parent->key > search->key || parent == head)
			parent->left = NULL;
		else
			parent->right = NULL;
		
		free(search);
	}
	else {
		if (search->left == NULL) {
			// 오른쪽 자식 노드만 가지고 있으면 오른쪽 자식 노드 올림
			if (parent->key > search->key || parent == head)
				parent->left = search->right;
			else
				parent->right = search->right;
			free(search);
		}
		else if (search->right == NULL) {
			// 왼쪽 자식 노드만 가지고 있으면 왼쪽 자식 노드 올림
			if (parent->key > search->key || parent == head)
				parent->left = search->left;
			else
				parent->right = search->left;
			free(search);
		}
		else {
			// 양쪽 자식 노드를 모두 가지면 오른쪽 자식노드에서
			// 가장 작은 노드를 search 위치로 올림
			Node* carry = search->right;
			Node* carryParent = search;
			while(carry->left != NULL) {
				carryParent = carry;
				carry = carry->left;
			}
			int carryKey = carry->key;

			// 원 위치의 carry 삭제
			deleteNode(head, carry->key);

			// search의 key를 carry의 key로 설정
			search->key = carryKey;
		}		
	}
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top <= -1) {
		// 스택이 빈 상태
		//printf("\n Stack is Empty!\n");
		return NULL;
	}

	// 스택의 top 위치 값을 반환하고, top을 감소
	return stack[top--];
}

void push(Node* aNode)
{
	if (top >= MAX_STACK_SIZE - 1) {
		// top이 MAX_STACK_SIZE-1이면 스택이 가득 참
		printf("\n Stack is Full!\n");
		return;
	}

	// 스택의 top을 증가시키고 그 위치에 삽입
	stack[++top] = aNode;
}



Node* deQueue()
{
	if(front == rear) {
		// 큐가 빈 상태
		//printf("\n Queue is Empty!\n");
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (rear == front) {
		// 큐가 가득 참
		printf("\n Queue is Full!\n");
		rear = (rear - 1) % MAX_QUEUE_SIZE;
		return;
	}

	queue[rear] = aNode;
}


