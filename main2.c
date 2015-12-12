#define MAX_VERTEXT_NUM 100
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define INFINITY INT_MAX
int *visited;
typedef struct arcnode/*边*/
{
	int adjindex;/*边权值*/
	int weight;
	struct arcnode * next;
}arc;
typedef struct vertexnode/*顶点*/
{
	char info[10];
	arc *firstarc;
} vertex;
typedef struct/*图*/
{
	vertex vertexlist[MAX_VERTEXT_NUM];
	int vertexnum;
	int arcnum;
}graph;

//栈的结构定义
struct _node
{
	int ivex;
	struct _node *next;
};
typedef struct _node node, *pnode;
struct _stack
{
	int size;
	pnode ptop;
};
typedef struct _stack stack, *pstack;

//堆的结构定义
struct _queue
{
	pnode front;
	pnode rear;
};
typedef struct _queue queue, *pqueue;

//栈的实现
pstack init_stack(int size)
{
	pnode pn = NULL;
	pstack ps = NULL;
	pn = (pnode)malloc(sizeof(node));
	ps = (pstack)malloc(sizeof(stack));
	pn->ivex = -1;
	pn->next = NULL;
	ps->size = size;
	ps->ptop = pn;
	return ps;
}
int empty_stack(pstack ps)
{
	if (ps->ptop->next == NULL)
		return 1;
	else
		return 0;
}
void push_stack(pstack ps, int ivex)
{
	pnode pn = NULL;
	pn = (pnode)malloc(sizeof(node));
	pn->ivex = ivex;
	pn->next = ps->ptop;
	ps->ptop = pn;
}
int pop_stack(pstack ps)
{
	int ivex = -1;
	pnode pn = NULL;
	if (!empty_stack(ps))
	{
		pn = ps->ptop;
		ps->ptop = ps->ptop->next;
		ivex = pn->ivex;
		free(pn);
	}
	return ivex;
}

//堆的实现
queue init_queue()
{
	pnode pn = NULL;
	queue qu;
	pn = (pnode)malloc(sizeof(node));
	pn->next;
	pn->ivex = -1;
	qu.front = qu.rear = pn;
	return qu;
}
int empty_queue(queue qu)
{
	if (qu.front == qu.rear)
		return 1;
	else
		return 0;
}
void en_queue(queue qu, int ivex)
{
	pnode pn = NULL;
	pn = (pnode)malloc(sizeof(node));
	pn->ivex = ivex;
	pn->next = qu.rear->next;
	qu.rear = pn;
}
int de_queue(queue qu)
{
	int ivex = -1;
	pnode pn = NULL;
	if (!empty_queue(qu))
	{
		pn = qu.front;
		qu.front = qu.front->next;
		ivex = pn->ivex;
		free(pn);
	}
	return ivex;
}

void initgraph(graph *gh)/*建立图*/
{
	int i, adjindex;
	int weight;
	char info[10];
	arc *tmparc, *lastarc;
	printf("\n请输入顶点个数:");
	scanf_s("%d", &(gh->vertexnum));
	printf("\n请输入边的个数:");
	scanf_s("%d", &(gh->arcnum));
	printf("\n请输入顶点的数据:");
	for (i = 0;i<gh->vertexnum;i++)
	{

		scanf_s("%s", info,10);
		strcpy_s((gh->vertexlist[i]).info, 10, info);
		(gh->vertexlist[i]).firstarc = NULL;
	}
	printf("\n请输入边的权值:");
	for (i = 0;i<gh->vertexnum;i++)
	{
		lastarc = NULL;
		for (scanf_s("%d,%d", &adjindex, &weight);adjindex >= 0;scanf_s("%d,%d", &adjindex, &weight))
		{
			tmparc = (arc*)malloc(sizeof(arc));
			if (tmparc == NULL)
				exit(-1);
			tmparc->adjindex = adjindex;
			tmparc->weight = weight;
			(gh->vertexlist[i]).firstarc = tmparc;
			tmparc->next = lastarc;
			lastarc = tmparc;
		}
	}
	printf("\n图的建立完成！！！\n");
}

void printgraph(graph gh)
{
	arc *parc;
	int i;
	for (i = 0;i<gh.vertexnum;i++)
	{
		printf("\n%s:", gh.vertexlist[i].info);
		parc = gh.vertexlist[i].firstarc;
		while (parc != NULL)
		{
			printf("%d,%d ", parc->adjindex, parc->weight);
			parc = parc->next;
		}
	}
}

//
void dfs(graph gh, int v, int visited[])
{
	arc * parc;
	visited[v] = 1;
	printf("%s\n", (gh.vertexlist[v]).info);
	for (parc = (gh.vertexlist[v]).firstarc;parc != NULL;parc = parc->next)
	{
		if (visited[parc->adjindex] == 0)
		{
			dfs(gh, parc->adjindex, visited);
		}
	}
}

//深度优先搜索
void dfsgraph(graph gh)
{
	int i;
	int *visited = (int *)malloc(sizeof(int)*gh.vertexnum);
	if (visited == NULL)
		exit(-1);
	for (i = 0;i<gh.vertexnum;i++)
	{
		visited[i] = 0;
	}
	printf("\n深度优先搜索:");
	for (i = 0;i<gh.vertexnum;i++)
	{
		if (visited[i] == 0)
		{
			dfs(gh, i, visited);
		}
	}
	printf("\n");
}

//广度优先搜索
void bfsgraph(graph gh)
{
	char *stack;
	int top;
	arc * parc;
	int stopelem;
	int *visited, i;

	stack = (char*)malloc(sizeof(char)*gh.vertexnum);
	if (stack == NULL)
		exit(-1);
	top = 0;
	visited = (int *)malloc(sizeof(int)*gh.vertexnum);
	if (visited == NULL)
		exit(-1);
	for (i = 0;i<gh.vertexnum;i++)
	{
		visited[i] = 0;
	}

	printf("\n广度优先搜索:");
	for (i = 0;i<gh.vertexnum;i++)
	{
		if (visited[i] == 0)
		{
			printf("%s", (gh.vertexlist[i]).info);
			visited[i] = 1;
			stack[top++] = i;
			while (top>0)
			{
				stopelem = stack[--top];
				for (parc = (gh.vertexlist[stopelem]).firstarc;parc != NULL;parc = parc->next)
				{
					if (visited[parc->adjindex] == 0)
					{
						printf("%s", (gh.vertexlist[parc->adjindex]).info);
						visited[parc->adjindex] = 1;
						stack[top++] = parc->adjindex;
					}
				}
			}
		}
	}
}

//非递归深度优先搜索
void DFS2_Graph(graph g)
{
	int i, j, k;
	pstack ps = NULL;
	ps = init_stack(g.vertexnum);
	visited = (int *)malloc((g.vertexnum + 1)*sizeof(int));
	for (i = 1; i <= g.vertexnum; i++)
		visited[i] = 0;
	for (i = 1; i <= g.vertexnum; i++)
		if (!visited[i])
		{
			visited[i] = 1;
			printf("%3c", g.vertexlist[i]);
			push_stack(ps, i);
			k = i;
			while (!empty_stack(ps))
			{
				if (!visited[j])
				{
					visited[j] = 1;
					printf("%3c", g.vertexlist[j]);
					push_stack(ps, j); /* push all visited ivex */
					k = j; /* newer node */
				}
				k = pop_stack(ps);
			}
		}
}

//主函数
int main()
{
	graph gh;
	initgraph(&gh);
	printgraph(gh);
	dfsgraph(gh);
	bfsgraph(gh);
	bfsgraph_no_in(gh);
	return 0;
}