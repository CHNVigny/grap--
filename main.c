#include <stdio.h>
#include <stdlib.h>
typedef struct node/*�߱���*/
{
	int adjvex;//�ٽ�����±꣩
	struct node *next;
}EdgeNode;
typedef struct /*�������*/
{
	int vertex;/*����������*/
	int visited;/*�˽ڵ��Ƿ񱻷��ʹ�*/
	EdgeNode *firstedge;/*������ͷָ��*/
}VertexNode;
typedef struct/*ͼ���ڽӱ�*/
{
	VertexNode vexlist[100];
	int n, e;/*������������*/
}AdjGraph;

void CreatGraph(AdjGraph *G)
{
	int i;
	printf("�����붥������ͱ�����");
	scanf_s("%d %d", &(G->n), &(G->e));
	for (i = 0;i<G->n;i = i + 1)/*���������*/
	{
		printf("�����붥���� ��");
		scanf_s("%d", &(G->vexlist[i].vertex));/*���붥����Ϣ*/
		G->vexlist[i].firstedge = NULL;/*�߱���Ϊ�ձ�*/
	}
	for (i = 0;i<G->e;i = i + 1)/*���������룬�����߱�*/
	{
		int tail, head;
		printf("������������ǰ�����ţ�\n");
		scanf_s("%d %d", &tail, &head);
		EdgeNode *p;
		p = (EdgeNode *)malloc(sizeof(EdgeNode));/*�����߽��*/
		p->adjvex = head;/*���ñ߽��*/
		p->next = G->vexlist[tail].firstedge;/*�����tail�������ǰ��*/
		G->vexlist[tail].firstedge = p;
	}
}

//�����������


int main()
{
	AdjGraph G;
	CreatGraph(&G);
	return 0;
}
