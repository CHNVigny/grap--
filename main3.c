#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*给出图的深度和广度搜索算法（要求图的顶点不少于10个，边不少于20个，深度优先搜索要给出递归/非递归两种算法）。

应用搜索算法完成一种应用。
*/

typedef struct node//边表结点
{
	int adjvex;        //邻接点域（下标）
	struct node *next;//下一边链接指针 
} EdgeNode;
typedef struct //顶点表结点
{
	char  vertex[10];      //顶点数据域 
	EdgeNode * firstedge;//边链表头指针
} VertexNode;

typedef struct sta
{
	EdgeNode * edge;
}STA;


VertexNode*  CreateGraph(VertexNode* AdjGraph, int ver_num);//建立邻接表
int serch(VertexNode* AdjGraph, char *v_name, int max_num);//搜索所输入的顶点的位置
void printf_v(VertexNode *AdjGraph, int max_num);//打印邻接表
int DFS_pass(VertexNode* AdjGraph, int max_num, int choice, int *array_2);//判断是否搜索完毕
void DFS_print(VertexNode* AdjGraph, int *pass_array, int i, int flag, int *array_2, int max_num, int num, int the_tree_num);//递归深度遍历算法
void DFS_print_no_recursive(VertexNode * AdjGraph, int *pass_array, int i, int max_num);//非递归深度优先搜索算法
void BFS1(VertexNode * AdjGraph, int max_num, int *false_pass, int visit_num);//广度优先搜索算法
void print_tree(int tree_num, int *array_2, VertexNode *AdjGraph, int max_num);//打印生成森林（生成树）

int main()
{
	VertexNode* AdjGraph = NULL;
	int ver_num, *array_2;

	//初始化邻接表
	printf("请输入顶点的个数：");
	scanf("%d", &ver_num);
	AdjGraph = CreateGraph(AdjGraph, ver_num);
	array_2 = (int*)malloc(sizeof(int)*(ver_num * 2));
	int tree_num = 0;
	int choice;
	do {
		printf("-------------------------------------------\n");
		printf("1.深度优先遍历递归算法\n");
		printf("2.深度优先遍历非递归算法\n");
		printf("3.广度优先遍历\n");
		printf("4.求图中的森林\n");
		printf("5.打印图的邻接表\n");
		printf("请输入您的选择：\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			DFS_pass(AdjGraph, ver_num, 1, array_2);
			break;
		case 2:
			DFS_pass(AdjGraph, ver_num, 2, array_2);
			break;
		case 3:
			DFS_pass(AdjGraph, ver_num, 3, array_2);
			break;
		case 4:
			tree_num = DFS_pass(AdjGraph, ver_num, 4, array_2);
			print_tree(tree_num, array_2, AdjGraph, ver_num);
			break;
		case 5:
			printf_v(AdjGraph, ver_num);
			break;
		default:
			printf("输入有误，请重新再来！：\n");
			break;
		}

		printf("\n您还想继续遍历么？\n继续请输入1，退出请输入0.\n");
		do
		{
			scanf("%d", &choice);
		} while (choice != 0 && choice != 1);
	} while (choice == 1);
	return 0;
}

int serch(VertexNode* AdjGraph, char *v_name, int max_num)
{
	int i;
	for (i = 0; i < max_num; i++)
	{
		if (strcmp(AdjGraph[i].vertex, v_name) == 0)
		{
			return i + 1;
		}
	}
	printf("输入有误请重新输入\n");
	return 0;
}
VertexNode*  CreateGraph(VertexNode* AdjGraph, int ver_num)
{
	int edge_num;

	AdjGraph = (VertexNode*)malloc(sizeof(VertexNode)*ver_num);
	if (AdjGraph == NULL)
	{
		printf("程序异常退出！\n");
		exit(0);
	}
	printf("请输入边的个数：");
	scanf("%d", &edge_num);

	int i;
	printf("-------------------------------------------\n");
	for (i = 0; i < ver_num; i++)
	{
		printf("请输入第%d个顶点的名称（注：长度小于10个字符）：", i + 1);
		scanf("%s", AdjGraph[i].vertex);
		AdjGraph[i].firstedge = NULL;
	}

	for (i = 0; i < edge_num; i++)
	{
		char v1[10], v2[10];
		int v1_num = 0, v2_num = 0;
		printf("-------------------------------------------\n");
		printf("请输入第%d条边的第一个端点的名称：", i + 1);
		while (v1_num == 0)
		{
			scanf("%s", v1);
			v1_num = serch(AdjGraph, v1, ver_num);
		}

		printf("请输入第%d条边的第二个端点的名称：", i + 1);
		while (v2_num == 0)
		{
			scanf("%s", v2);
			v2_num = serch(AdjGraph, v2, ver_num);
		}

		EdgeNode *p, *pr;
		p = (EdgeNode*)malloc(sizeof(EdgeNode));
		if (p == NULL)
		{
			printf("程序异常退出！\n");
			exit(0);
		}

		pr = AdjGraph[v1_num - 1].firstedge;
		p->adjvex = v2_num - 1;
		p->next = NULL;
		if (pr == NULL)
		{
			AdjGraph[v1_num - 1].firstedge = p;
		}
		else
		{
			while (pr->next != NULL)
			{
				pr = pr->next;
			}
			pr->next = p;
		}

		p = (EdgeNode*)malloc(sizeof(EdgeNode));
		if (p == NULL)
		{
			printf("程序异常退出！\n");
			exit(0);
		}

		pr = AdjGraph[v2_num - 1].firstedge;
		p->adjvex = v1_num - 1;
		p->next = NULL;
		if (pr == NULL)
		{
			AdjGraph[v2_num - 1].firstedge = p;
		}
		else
		{
			while (pr->next != NULL)
			{
				pr = pr->next;
			}
			pr->next = p;
		}

	}
	return AdjGraph;
} //时间复杂度：O(2e+n) 
void printf_v(VertexNode *AdjGraph, int max_num)
{
	int i;
	for (i = 0; i < max_num; i++)
	{
		EdgeNode*p;
		p = AdjGraph[i].firstedge;
		printf("%s ->", AdjGraph[i].vertex);
		while (p != NULL)
		{
			printf("%d -> ", p->adjvex);
			p = p->next;
		}
		printf("NULL\n");
	}

}
int DFS_pass(VertexNode* AdjGraph, int max_num, int choice, int *array_2)
{
	int i;
	int flag = 1, tree_num = 0;

	int *pass_array;
	pass_array = (int*)malloc(sizeof(int)*max_num);

	for (i = 0; i < max_num; i++)
	{
		pass_array[i] = 0;
	}

	char first[10];
	int first_num = 0;

	printf("-------------------------------------------\n");
	printf("请输入第一个遍历顶点名称：");
	while (first_num == 0)
	{

		scanf("%s", first);
		first_num = serch(AdjGraph, first, max_num);
	}
	first_num--;

	if (choice == 1)
	{

		DFS_print(AdjGraph, pass_array, first_num, 1, array_2, max_num, -1, tree_num);

		while (flag != 0)
		{
			flag = 0;
			for (i = 0; i < max_num; i++)
			{
				if (pass_array[i] == 0)
				{
					DFS_print(AdjGraph, pass_array, i, 1, array_2, max_num, -1, ++tree_num);
					flag = 1;
				}
			}
		}
	}
	else if (choice == 2)
	{
		DFS_print_no_recursive(AdjGraph, pass_array, first_num, max_num);

		while (flag != 0)
		{
			flag = 0;
			for (i = 0; i < max_num; i++)
			{
				if (pass_array[i] == 0)
				{
					DFS_print_no_recursive(AdjGraph, pass_array, i, max_num);
					flag = 1;
				}
			}
		}
	}
	else if (choice == 3)
	{
		BFS1(AdjGraph, max_num, pass_array, first_num);
		while (flag != 0)
		{
			flag = 0;
			for (i = 0; i < max_num; i++)
			{
				if (pass_array[i] == 0)
				{
					BFS1(AdjGraph, max_num, pass_array, i);
					flag = 1;
				}
			}
		}
	}
	else
	{

		DFS_print(AdjGraph, pass_array, first_num, 0, array_2, max_num, -1, tree_num);

		while (flag != 0)
		{
			flag = 0;
			for (i = 0; i < max_num; i++)
			{
				if (pass_array[i] == 0)
				{
					DFS_print(AdjGraph, pass_array, i, 0, array_2, max_num, -1, ++tree_num);
					flag = 1;
				}
			}
		}
	}
	return tree_num;

}
void DFS_print(VertexNode* AdjGraph, int *pass_array, int i, int flag, int *array_2, int max_num, int num, int the_tree_num)
{                                                                            //num 是树所在的父亲位置  the_tree_num 带表子树的棵树
	EdgeNode *p;
	if (flag == 1)
	{
		printf("%s  ", AdjGraph[i].vertex);
	}

	array_2[max_num + i] = the_tree_num;
	array_2[i] = num;
	pass_array[i] = 1;

	p = AdjGraph[i].firstedge;
	while (p != NULL)
	{
		if (pass_array[p->adjvex] == 0)
		{
			DFS_print(AdjGraph, pass_array, p->adjvex, flag, array_2, max_num, i, the_tree_num);
		}
		p = p->next;
	}
}
void DFS_print_no_recursive(VertexNode * AdjGraph, int *pass_array, int i, int max_num)
{
	//初始化堆栈框架
	STA *sta;
	int top = -1;
	sta = (STA *)malloc(sizeof(STA)*max_num);
	if (sta == NULL)
	{
		printf("程序异常退出！\n");
		exit(0);
	}

	EdgeNode *p;
	printf("%s  ", AdjGraph[i].vertex);
	pass_array[i] = 1;
	p = AdjGraph[i].firstedge;
	while (p != NULL)
	{
		if (pass_array[p->adjvex] == 0)
		{
			break;
		}
		p = p->next;
	}
	if (p != NULL)
	{
		sta[++top].edge = p;
	}

	while (top != -1)
	{
		p = sta[top--].edge;
		printf("%s  ", AdjGraph[p->adjvex].vertex);
		pass_array[p->adjvex] = 1;
		p = AdjGraph[p->adjvex].firstedge;

		while (p != NULL)
		{
			if (pass_array[p->adjvex] == 0)
			{
				break;
			}
			p = p->next;
		}
		if (p != NULL)
		{
			sta[++top].edge = p;
		}
	}




}
void BFS1(VertexNode * AdjGraph, int max_num, int *false_pass, int visit_num)//这里没有进行先广编号
{
	int *Queue;
	int fist_num = 0, last_num = 0;
	Queue = (int*)malloc(sizeof(int)*max_num);
	if (Queue == NULL)
	{
		printf("程序异常退出！\n");
		exit(0);
	}

	printf("%s  ", AdjGraph[visit_num].vertex);
	false_pass[visit_num] = 1;

	Queue[last_num++] = visit_num;

	while (fist_num != last_num)
	{
		int top_num = Queue[fist_num++];
		EdgeNode *p;
		p = AdjGraph[top_num].firstedge;
		while (p != NULL)
		{
			if (false_pass[p->adjvex] == 0)
			{
				printf("%s  ", AdjGraph[p->adjvex].vertex);
				false_pass[p->adjvex] = 1;
				Queue[last_num % max_num] = p->adjvex;
				last_num++;
			}
			p = p->next;
		}
	}
}
void print_tree(int tree_num, int *array_2, VertexNode *AdjGraph, int max_num)
{
	int i, j;
	printf("树标号  下标  名称 父节点位置 父节点名称\n");
	for (i = 0; i < max_num; i++)
	{
		printf("  %d\t  %d\t%s\t%d\t", array_2[i + max_num], i, AdjGraph[i].vertex, array_2[i]);
		if (array_2[i] != -1)
		{
			printf("%s\n", AdjGraph[array_2[i]].vertex);
		}
		else
		{
			printf("NULL\n");
		}

	}
}