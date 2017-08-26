/*
 * maze.c
 *
 *  Created on: 2017年8月25日
 *      Author: songmingyu
 *      利用栈来走迷宫的代码。程序会随机生成8行10列的数组代表迷宫，在迷宫中，
 “1”代表路不通，“0”代表路通。因为迷宫是有边界的，所以第一行和第八行，
 第1列和第10列都是墙（不通），直接判断为1。可以直接从2,7行，2,9列开始计算。
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define m 6 /*迷宫的实际需要计算的行数*/
#define n 8 //迷宫的实际需要计算的列数

typedef struct { //创建一个数据类型，存放路径地址和方向
	int x, y, d;
} datatype;

typedef struct StackNode{ //存放datatype的链栈
	datatype data;
	struct StackNode *next;
} StackNode;

typedef struct { //存放方向的结构
	int a, b;
} direction;

StackNode *InitStack(); //初始化栈
int Empty_StackNode (StackNode *s); //判断栈空
StackNode *Push_StackNode(StackNode *s, datatype temp); //入栈
StackNode *Pop_StackNode(StackNode *s); //出栈
int Top_StackNode(StackNode * s, datatype *temp); //取栈顶元素

int main(int argc, char **argv) {
	printf("hellowWorld!\n");
	int maze[m + 2][n + 2] =
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 0, 1, 1, 1, 0,	1, 1, 1, 1,
          1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 
          1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
          1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 
          1, 1, 0, 0, 1, 1, 0, 0, 0, 1,
          1, 0,	1, 1, 0, 0, 1, 1, 0, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int i = 0, j = 0;
	int x, y, d;
	datatype temp;
	StackNode *s;
	direction move[8]; //存放路径地址
	move[0].a = move[2].b = move[6].b = move[4].a = 0;
	move[0].b = move[1].a = move[1].b = move[2].a = move[3].a = move[7].b = 1;
	move[3].b = move[4].b = move[5].a = move[5].b = move[6].a = move[7].a = -1;
	s = InitStack();
	temp.x = temp.y = 1;
	temp.d = -1;
	s = Push_StackNode(s, temp);
	while (!Empty_StackNode (s)) {
		Top_StackNode(s, &temp);
		x = temp.x;
		y = temp.y;
		d = temp.d + 1;
		while (d < 8) {
			i = x + move[d].a;
			j = y + move[d].b;
			if (maze[i][j] == 0) {
				x = i;
				y = j;
				temp.x = x;
				temp.y = y;
				temp.d = d;
				s = Push_StackNode(s, temp);
				maze[x][y] = -1;
				if (x == m && y == n) { //到达出口
					printf("找到出口\n");
					exit(0);
				} else {
                    printf("\n(%d,%d)\n",x,y);
					d = 0;
				}
			} else {
				++d;
			}
		}/*while(d<8)*/
		/*如果一个点判断周围7个点都不通，则需要返回前一个点，出栈一个数据*/
		s = Pop_StackNode(s);
	}
	return 0;
}

StackNode *InitStack() {
	StackNode *s;
	s = NULL;
	return s;
}

int Empty_StackNode (StackNode *s) {
	if (s == NULL) { //如果链栈为空
		return 1;
	} else { //链栈不为空
		return 0;
	}
}

StackNode *Push_StackNode(StackNode *s, datatype temp) {
	StackNode *p;
    p = (StackNode *)malloc(sizeof(StackNode));
	p->data = temp;
	p->next = s;
	s = p;
	return s;
}

int Top_StackNode(StackNode *s, datatype *temp) //取栈顶元素
{
	(*temp) = s->data;
	return 0;
}

StackNode *Pop_StackNode(StackNode *s) //取栈顶元素
{
	StackNode *p;
	p = s;
	s = s->next;
	free(p);
	p = NULL;
	return s;
}

