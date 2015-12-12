#include <stdio.h>
#include <stdlib.h>
typedef struct node/*边表结点*/
{
	int adjvex;//临界点域（下标）
	struct node *next;
}EdgeNode;
typedef struct /*顶点表结点*/
{
	int vertex;/*顶点数据域*/
	int visited;/*此节点是否被访问过*/
	EdgeNode *firstedge;/*边链表头指针*/
}VertexNode;
typedef struct/*图的邻接表*/
{
	VertexNode vexlist[100];
	int n, e;/*顶点个数与边数*/
}AdjGraph;

void CreatGraph(AdjGraph *G)
{
	int i;
	printf("请输入顶点个数和边数：");
	scanf_s("%d %d", &(G->n), &(G->e));
	for (i = 0;i<G->n;i = i + 1)/*建立顶点表*/
	{
		printf("请输入顶点编号 ：");
		scanf_s("%d", &(G->vexlist[i].vertex));/*输入顶点信息*/
		G->vexlist[i].firstedge = NULL;/*边表置为空表*/
	}
	for (i = 0;i<G->e;i = i + 1)/*逐条边输入，建立边表*/
	{
		int tail, head;
		printf("请输入相邻两前后结点编号：\n");
		scanf_s("%d %d", &tail, &head);
		EdgeNode *p;
		p = (EdgeNode *)malloc(sizeof(EdgeNode));/*建立边结点*/
		p->adjvex = head;/*设置边结点*/
		p->next = G->vexlist[tail].firstedge;/*链入第tail号链表的前端*/
		G->vexlist[tail].firstedge = p;
	}
}

//广度优先搜索


int main()
{
	AdjGraph G;
	CreatGraph(&G);
	return 0;
}
