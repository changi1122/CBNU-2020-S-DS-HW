/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
int isLeafNode(Node* node); /* node가 리프 노드이면 1 반환 */
void freeRecursive(Node* ptr); /* ptr과 그 자식 노드들을 재귀적으로 해제 */


int main()
{
	printf("[----- 이우창 2019038074 -----]\n\n");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}



void inorderTraversal(Node* ptr)
{
	// 재귀 호출로 ptr->left, ptr, ptr->right 순으로 출력
	if(ptr) {
		if(ptr->left)
			inorderTraversal(ptr->left);

		printf("[%d] ", ptr->key);

		if(ptr->right)
			inorderTraversal(ptr->right);
	}
	return;
}

void preorderTraversal(Node* ptr)
{
	// 재귀 호출로 ptr, ptr->left, ptr->right 순으로 출력
	if(ptr) {
		printf("[%d] ", ptr->key);

		if(ptr->left)
			preorderTraversal(ptr->left);

		if(ptr->right)
			preorderTraversal(ptr->right);
	}
	return;
}

void postorderTraversal(Node* ptr)
{
	// 재귀 호출로 ptr->left, ptr->right, ptr 순으로 출력
	if(ptr) {
		if(ptr->left)
			postorderTraversal(ptr->left);

		if(ptr->right)
			postorderTraversal(ptr->right);
		
		printf("[%d] ", ptr->key);
	}
	return;
}


int insert(Node* head, int key)
{
	Node* find = head->left;

	if (find != NULL) // 트리가 빈 상태가 아닌 경우
	{
		// 노드를 삽입할 부모 노드 탐색
		while (1) {
			if (key < find->key) {
				if (find->left == NULL) {
					// 삽입할 부모 노드 찾음
					Node* new = (Node*)malloc(sizeof(Node));
					new->key = key;
					new->left = NULL;
					new->right = NULL;
					
					find->left = new;
					break; 
				}
				else
					find = find->left;
			}
			else if (key > find->key) {
				if (find->right == NULL) {
					// 삽입할 부모 노드 찾음
					Node* new = (Node*)malloc(sizeof(Node));
					new->key = key;
					new->left = NULL;
					new->right = NULL;
					
					find->right = new;
					break;
				}
				else
					find = find->right;
			}
			else // key == find->key : 중복되는 값을 가진 노드는 무시
				return 0;
		}
	}
	else // 트리가 빈 상태인 경우
	{
		// root에 새 노드 삽입
		Node* new = (Node*)malloc(sizeof(Node));
		new->key = key;
		new->left = NULL;
		new->right = NULL;

		head->left = new;
	}
	
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	// parent와 ptr을 자식 노드로 이동시키며 일치하는 노드가 있으면 삭제
	Node* ptr = head->left;
	Node* parent = head;
	
	if(ptr) { // 트리가 빈 상태가 아니면
		while(ptr != NULL) {
			if(key < ptr->key) {
				parent = ptr;
				ptr = ptr->left;
			}
			else if (key > ptr->key) {
				parent = ptr;
				ptr = ptr->right;
			}
			else { //key == ptr->key
				if (isLeafNode(ptr)) // 리프 노드이면
				{
					if (parent == head || key < parent->key) parent->left = NULL;
					else if (key > parent->key) parent->right = NULL;

					free(ptr);
					return 0;
				}
				else // 리트 노드가 아니면 
				{
					printf("\nthe node [%d] is not a leaf\n", key);
					return 0;
				}
			}
		}
		printf("\n Cannot find the node [%d]\n", key);
	}
	return 0;
}

int isLeafNode(Node* node)
{
	// node가 리프 노드이면 1 반환, 아니면 0 반환
	return (node->left == NULL) && (node->right == NULL);
}

Node* searchRecursive(Node* ptr, int key)
{	
	// 재귀 호출하여 key와 일치하는 노드가 있으면 주소 반환
	if(ptr) {
		if (key < ptr->key)
			return searchRecursive(ptr->left, key);
		else if (key > ptr->key)
			return searchRecursive(ptr->right, key);
		else {
			// 일치하는 노드를 찾은 경우 (key == ptr->key)
			return ptr;
		}
	}
	else {
		// 일치하는 노드를 찾을 수 없는 경우
		return NULL;
	}
}

Node* searchIterative(Node* head, int key)
{
	// ptr을 자식 노드로 이동시키며 일치하는 노드가 있으면 주소 반환
	Node* ptr = head->left;
	while(ptr != NULL)
	{
		if (key < ptr->key)
			ptr = ptr->left;
		else if (key > ptr->key)
			ptr = ptr->right;
		else //key == ptr->key
			break;
	}
	return ptr;
}


int freeBST(Node* head)
{
	// freeRecursive에서 root와 그 아래 트리를 해제
	if (head->left != NULL)
		freeRecursive(head->left);

	// head를 해제
	free(head);
	
	return 0;
}

void freeRecursive(Node* ptr)
{
	// ptr->left, ptr->right, ptr 순으로 해제
	if (ptr->left)
		freeRecursive(ptr->left);
	if (ptr->right)
		freeRecursive(ptr->right);
	free(ptr);
	return;
}
