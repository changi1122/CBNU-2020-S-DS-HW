/*
 * Graph
 *
 * 2019038074 이우창
 * 
 * Data Structures Term Project
 * Created on: 2020.06.12.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/* 상수 */
#define TRUE 1
#define FALSE 0

#define MAX_VERTEX 20

#define MAX_STACK_SIZE 20
#define MAX_QUEUE_SIZE 20


/* 구조체 */
typedef struct Vertex {
    int num;                /* Vertex 번호 */
    struct Vertex* link;    /* 다음 인접 Vertex로의 link */
} Vertex;

typedef struct VertexHead {
    Vertex* head;           /* 인접 Vertex들의 연결 리스트 */
} VertexHead;

typedef struct Graph {
    VertexHead* vlist;      /* Vertex 배열: vlist[MAX_VERTEX] */
} Graph;


/* 함수 */
void createGraph(Graph* g);                    	/* 빈 그래프 생성 */
void destroyGraph(Graph* g);                    /* 그래프에 할당된 메모리 반환 */
void insertVertex(Graph g, int vertex_num);    	/* Vertex 삽입 */
void deleteVertex(Graph g, int vertex_num);    	/* Vertex 삭제 */
void insertEdge(Graph g, int from, int to);    	/* 두 Vertex 사이의 Edge 생성 */
void deleteEdge(Graph g, int from, int to);    	/* Edge 삭제 */
void depthFS(Graph g, int vertex_num);         	/* 깊이 우선 탐색 using 스택 */
void breadthFS(Graph g, int vertex_num);       	/* 너비 우선 탐색 using 큐 */
void printGraph(Graph g);                      	/* 그래프의 Vertex, Edge 출력 */

/* 추가 구현 함수 */
void insertToLinkedList(Graph g, int vertex_num, Vertex* v);	/* 인접 정점 리스트에 삽입 */
void deleteFromLinkedList(Graph g, int vertex_num, int to);		/* 인접 정점 리스트에서 삭제 */

int adjacentVertex(Graph g, int vertex_num);					/* 방문하지 않은 인접 Vertex 번호 반환, 없으면 -1 반환 */
void clearVisitFlag();		/* visit flag 초기화 */

// 스택
void push(int v);
int pop();

// 큐
void enQueue(int v);
int deQueue();


/* 전역 변수 */
Graph graph;                // 그래프
int vflag[MAX_VERTEX];      // Vertex 생성 여부 : TRUE or FALSE
int visit_flag[MAX_VERTEX]; // 방문 플래그 : TRUE or FALSE

int stack_top = -1;
int stack[MAX_STACK_SIZE];

int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;


int main()
{
    graph.vlist = NULL;
    
    char command;
    int key = -1;
    int from = -1;
    int to = -1;
    
    printf("2019038074 이우창\n\n");
    do{
		printf("----------------------------------------------------------------\n");
		printf("                              Graph                             \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Insert vertex    = v           Delete vertex    = b\n");
		printf(" Insert edge      = e           Delete edge      = d\n");
		printf(" DepthFS          = f           BreadthFS        = s\n");
		printf(" Print Graph      = p\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			createGraph(&graph);
			break;
		case 'q': case 'Q':
			destroyGraph(&graph);
			break;
		case 'v': case 'V':
			printf("Your Key(1~%d) = ", MAX_VERTEX);
			scanf("%d", &key);
			insertVertex(graph, key - 1);
			break;
		case 'b': case 'B':
			printf("Your Key(1~%d) = ", MAX_VERTEX);
			scanf("%d", &key);
			deleteVertex(graph, key - 1);
			break;
		case 'e': case 'E':
			printf("from(1~%d) = ", MAX_VERTEX);
			scanf("%d", &from);
            printf("to  (1~%d) = ", MAX_VERTEX);
            scanf("%d", &to);
			insertEdge(graph, from - 1, to - 1);
			break;
		case 'd': case 'D':
			printf("from(1~%d) = ", MAX_VERTEX);
			scanf("%d", &from);
            printf("to  (1~%d) = ", MAX_VERTEX);
            scanf("%d", &to);
			deleteEdge(graph, from - 1, to - 1);
			break;
		case 'f': case 'F':
			printf("Your Key(1~%d) = ", MAX_VERTEX);
			scanf("%d", &key);
			depthFS(graph, key - 1);
			break;

		case 's': case 'S':
			printf("Your Key(1~%d) = ", MAX_VERTEX);
			scanf("%d", &key);
			breadthFS(graph, key - 1);
			break;

		case 'p': case 'P':
			printGraph(graph);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

    return 0;
}

/* 빈 그래프 생성 */
void createGraph(Graph* g)
{
	if (g->vlist != NULL)
		destroyGraph(g);
	
	// 벡터 헤드 공간 할당
	g->vlist = malloc(sizeof(VertexHead) * MAX_VERTEX);
	for (int i = 0; i < MAX_VERTEX; i++) {
		g->vlist[i].head = NULL;
	}

	// 벡터 생성 플래그 초기화
	for (int v = 0; v < MAX_VERTEX; v++)
		vflag[v] = FALSE;
}

/* 그래프에 할당된 메모리 반환 */
void destroyGraph(Graph* g)
{
	if (g->vlist != NULL) {
		// 연결리스트 해제
		for (int i = 0; i < MAX_VERTEX; i++) {
			Vertex* search = g->vlist[i].head;
			while(search) {
				int delete_num = search->num;
				search = search->link;

				deleteFromLinkedList(*g, i, delete_num);
				deleteFromLinkedList(*g, delete_num, i);
			}
		}	

		// 정점 배열 해제
		free(g->vlist);
	}
	g->vlist = NULL;
}

/* Vertex 삽입 */
void insertVertex(Graph g, int vertex_num)
{
	if (g.vlist == NULL) {
		printf("그래프가 초기화되지 않음.\n");
		return;
	}
	else if (vflag[vertex_num] == TRUE) {
		printf("정점이 이미 삽입됨.\n");
		return;
	}

	// 플래그 및 NULL 설정
	g.vlist[vertex_num].head = NULL;
	vflag[vertex_num] = TRUE;
}

/* Vertex 삭제 */
void deleteVertex(Graph g, int vertex_num)
{
	if (g.vlist == NULL) {
		printf("그래프가 초기화되지 않음.\n");
		return;
	}
	else if (vflag[vertex_num] == FALSE) {
		printf("정점이 이미 삽입되지 않음.\n");
		return;
	}

	// 간선 삭제
	Vertex* search = g.vlist[vertex_num].head;
	int delete_num = -1;

	while (search != NULL) {
		delete_num = search->num;
		search = search->link;

		deleteFromLinkedList(g, vertex_num, delete_num);
		deleteFromLinkedList(g, delete_num, vertex_num);
	}

	g.vlist[vertex_num].head = NULL;	

	// 플래그 설정
	vflag[vertex_num] = FALSE;
}

/* 두 Vertex 사이의 Edge 생성 */
void insertEdge(Graph g, int from, int to)
{
	if (g.vlist == NULL) {
		printf("그래프가 초기화되지 않음.\n");
		return;
	}
	if (vflag[from] == FALSE || vflag[to] == FALSE) {
		printf("삽입되지 않은 정점에 간선을 삽입할 수 없음.\n");
		return;
	}

	// 삽입할 인접 정점
	Vertex* v = malloc(sizeof(Vertex));
	v->num = to;
	Vertex* v_rev = malloc(sizeof(Vertex));
	v_rev->num = from;

	//인접 정점 리스트 삽입
	insertToLinkedList(g, from, v);
	insertToLinkedList(g, to, v_rev);
}

/* Edge 삭제 */
void deleteEdge(Graph g, int from, int to)
{
	if (g.vlist == NULL) {
		printf("그래프가 초기화되지 않음.\n");
		return;
	}

	deleteFromLinkedList(g, from, to);
	deleteFromLinkedList(g, to, from);
}

/* 깊이 우선 탐색 using 스택 */
void depthFS(Graph g, int vertex_num)
{
	if (g.vlist == NULL) {
		printf("그래프가 초기화되지 않음.\n");
		return;
	}
	if (vflag[vertex_num] == FALSE || g.vlist[vertex_num].head == NULL) {
		printf("삽입되지 않은 정점, 간선이 없는 정점에서 깊이 우선 탐색할 수 없음.\n");
		return;
	}

	printf("\nDepth First Search:\n");
	
	int v = vertex_num;

	while(TRUE) {
		// 정점 방문
		if (visit_flag[v] == FALSE) {
			printf("[%d] ", v + 1);
			visit_flag[v] = TRUE;
		}
		
		int w = adjacentVertex(g, v); // 인접 정점
		if (w != -1) {
			// 방문하지 않는 인접 정점이 존재하면
			push(v);
			v = w;
		}
		else {
			// 방문하지 않는 인접 정점이 존재하지 않으면
			v = pop();

			if (v == -1) {
				// 스택이 공백이 되면
				break;
			}
		}
	}

	printf("\n\n");
	clearVisitFlag();
}

/* 너비 우선 탐색 using 큐 */
void breadthFS(Graph g, int vertex_num)
{
	if (g.vlist == NULL) {
		printf("그래프가 초기화되지 않음.\n");
		return;
	}
	if (vflag[vertex_num] == FALSE || g.vlist[vertex_num].head == NULL) {
		printf("삽입되지 않은 정점, 간선이 없는 정점에서 너비 우선 탐색할 수 없음.\n");
		return;
	}

	printf("\nBreadth First Search:\n");

	// 시작 정점
	int v = vertex_num;
	
	printf("[%d] ", v + 1);
	visit_flag[v] = TRUE;
	enQueue(v);
	
	while (TRUE) {
		v = deQueue();	// 큐에서 탐색할 부모 정점 번호 추출
		if (v == -1) {
			// 큐가 비면
			break;
		}

		for (Vertex* w = g.vlist[v].head; w; w = w->link) {
			// 자식들을 탐색 후 큐에 삽입
			if (visit_flag[w->num] == FALSE) {
				printf("[%d] ", w->num + 1);
				visit_flag[w->num] = TRUE;
				enQueue(w->num);
			}
		}
	}

	printf("\n\n");
	clearVisitFlag();
}

/* 그래프의 Vertex, Edge 출력 */
void printGraph(Graph g)
{
	if (g.vlist == NULL) {
		printf("그래프가 초기화되지 않음.\n");
		return;
	}

	// 필드명
	printf("\n[Init]  [Num ] -> [Adjacent Vertex]\n\n");

	for (int i = 0; i < MAX_VERTEX; i++) {
		printf("[  %c ]  [%3d ]", (vflag[i]) ? 'T' : 'F', i + 1);
		
		Vertex* search = g.vlist[i].head;
		while(search) {
			printf(" -> [%3d ]", search->num + 1);
			search = search->link;
		}
		printf("\n");
	}
}




/* 인접 정점 리스트에 삽입 */
void insertToLinkedList(Graph g, int vertex_num, Vertex* v)
{
	// 인접 정점 리스트는 오름차순임을 보장
	// 리스트를 따라가다 알맞은 위치에 삽입
	
	Vertex* search = g.vlist[vertex_num].head;
	Vertex* previous = NULL;

	while(search != NULL)
	{
		if (v->num > search->num) {
			previous = search;
			search = search->link;
		}
		else if (v->num == search->num) {
			// 이미 같은 간선이 있으면
			return;
		}
		else
			break;
	}

	// 삽입
	if (previous != NULL) {
		v->link = previous->link;
		previous->link = v;
	}
	else {
		// 맨 앞에 삽입
		v->link = g.vlist[vertex_num].head;
		g.vlist[vertex_num].head = v;
	}
}

/* 인접 정점 리스트에서 삭제 */
void deleteFromLinkedList(Graph g, int vertex_num, int to)
{
	Vertex* search = g.vlist[vertex_num].head;
	Vertex* previous = NULL;
	
	// 삭제할 간선 찾기
	while(search) {
		if (to > search->num) {
			previous = search;
			search = search->link;
		}
		else if (to == search->num) {
			// 찾은 경우
			break;
		}
		else
			// 삭제할 간선이 없음
			return;
	}

	if (search == NULL)
		// 삭제할 간선이 없음
		return;

	if (previous != NULL) {
		previous->link = search->link;
	}
	else {
		// 맨 앞 요소 삭제
		g.vlist[vertex_num].head = search->link;
	}

	free(search);
}


/* 스택 관련 함수 */
void push(int v)
{
	if (stack_top >= MAX_STACK_SIZE - 1) {
		printf("\n Stack is Full!\n");
		return;
	}

    stack[++stack_top] = v;
}

int pop()
{
    int v;
    if(stack_top == -1)
		// 빈 스택
        return -1;
    else {
    	v = stack[stack_top--];
    }
    return v;
}

/* 큐 관련 함수 */
void enQueue(int v)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (rear == front) {
		printf("\n Queue is Full!\n");
		rear = (rear - 1) % MAX_QUEUE_SIZE;
		return;
	}

	queue[rear] = v;
}

int deQueue()
{
	if(front == rear) {
		// 빈 큐
		return -1;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}


/* 방문하지 않은 인접 Vertex 반환, 없으면 -1 반환 */
int adjacentVertex(Graph g, int vertex_num)
{
	Vertex* search = g.vlist[vertex_num].head;

	while(search) {
		if (visit_flag[search->num] == FALSE)
			return search->num;
		search = search->link;
	}

	return -1;
}

/* visit flag 초기화 */
void clearVisitFlag()
{
	for (int i = 0; i < MAX_VERTEX; i++)
		visit_flag[i] = FALSE;
}
