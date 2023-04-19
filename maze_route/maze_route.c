#include <stdio.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10

typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return(s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "Stack Full\n");
		return;
	}
	else {
		s->top++;
		s->data[s->top] = item;
		return;
	}
}

element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "Stack Empty\n");
		return;
	}

	else return s->data[(s->top--)];
}

element peek(StackType* s)
{
	return s->data[s->top];
}

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {

		{'1','1','1','1','1','1','1','1','1','1'},

		{'e','1','0','1','0','0','0','1','0','1'},

		{'0','0','0','1','0','0','0','1','0','1'},

		{'0','1','0','0','0','1','1','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','0','0','1','0','1','1'},

		{'1','0','1','1','1','0','1','1','0','1'},

		{'1','1','0','0','0','0','0','0','0','x'},

		{'1','1','1','1','1','1','1','1','1','1'}
};

// 미로 위치 
void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0)	return;

	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

// 미로 출력
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
	printf("---------");
}

// 경로 삽입
void maze_route(StackType* s, int r, int c) {
	element route;
	route.r = r;
	route.c = c;

	push(s, route);
}

// 경로 출력
void print_route(StackType* s) {
	for (int i = 0; i <= s->top; i++) {
		printf("(%d, %d) ", s->data[i].r, s->data[i].c);
	}
	printf("\n");
}

int main()
{
	int r, c;
	int count = 0;
	StackType s, route;

	init_stack(&s);
	init_stack(&route);
	here = entry;

	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;

		maze[r][c] = '.';
		maze_print(maze);
		maze_route(&route, r, c);

		push_loc(&s, r, c - 1);
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c + 1);

		if (is_empty(&s)) {
			printf("Fail\n");
			return;
		}
		else
			here = pop(&s);

		//Back Count
		if ((maze[r - 1][c] == '1' || maze[r - 1][c] == '.') &&
			(maze[r + 1][c] == '1' || maze[r + 1][c] == '.') &&
			(maze[r][c - 1] == '1' || maze[r][c - 1] == '.') &&
			(maze[r][c + 1] == '1' || maze[r][c + 1] == '.'))
		{
			count++;
		}
	}

	printf("\n\nSuccess\n");
	printf("Back Count: %d\n", count);
	printf("Maze Route: ");
	print_route(&route);

	return;
}