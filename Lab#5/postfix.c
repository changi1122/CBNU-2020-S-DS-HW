/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}


void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}

}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		if(getToken(*exp) == operand) // *exp가 피연산자라면
		{
			charCat(exp);
		}
		else // *exp가 연산자라면
		{
			if (getToken(*exp) == rparen)
			{
				x = postfixPop();

				// 닫는 괄호이면 여는 괄호까지 스택 pop
				while(getToken(x) != lparen)
				{
					charCat(&x);
					x = postfixPop();
				}
			}
			else if (getToken(*exp) == lparen)
			{
				// 여는 괄호이면 스택에 push
				postfixPush(*exp);
			}
			else
			{
				// 연산자이면 스택의 top들과 *exp를 비교하면서 스택의 top이 우선순위가 높으면(또는 같으면)
				// 스택에서 pop하고 넘기기, *exp이 우선순위 높으면 스택에 push
				while(postfixStackTop != -1 && getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
				{
					x = postfixPop();
					charCat(&x);
				}

				postfixPush(*exp);
			}
			
		}

		exp++;
	}

	// 스택의 남은 연산자들 넘기기
	while (postfixStackTop != -1)
	{
		x = postfixPop(); 
		charCat(&x);
	}
}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

/**
 * postfixExp의 수식을 evalStack을 이용하여 계산한다.
 */
void evaluation()
{
	char *exp = postfixExp; // postfixExp의 문자 하나씩을 읽기위한 포인터
	int val1;				// 임시로 값을 저장하기 위한 변수
	int val2;				// 임시로 값을 저장하기 위한 변수

	// exp를 증가하며 postfixExp 왼쪽부터 오른쪽으로 이동
	while (*exp != '\0')
	{
		if (getToken(*exp) == operand) // *exp가 피연산자이면
		{
			evalPush(*exp - '0');
		}
		else // *exp가 연산자이면
		{
			// 스택에서 피연산자 두 개를 pop
			val2 = evalPop();
			val1 = evalPop();

			// 연산자의 종류에 따라 피연산자 두 개를 연산 후 다시 스택에 push
			precedence operator = getToken(*exp);

			switch (operator)
			{
			case plus:
				val1 = val1 + val2;
				evalPush(val1);
				break;
			case minus:
				val1 = val1 - val2;
				evalPush(val1);
				break;
			case times:
				val1 = val1 * val2;
				evalPush(val1);
				break;
			case divide:
				val1 = val1 / val2;
				evalPush(val1);
				break;
			}
		}

		exp++;
	}
	
	// evalStack에 남은 값이 계산 결과
	evalResult = evalPop();
}


int main()
{
	printf("[----- 이우창 2019038074 -----]\n\n");

	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;


}
