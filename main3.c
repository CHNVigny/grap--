#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*����ͼ����Ⱥ͹�������㷨��Ҫ��ͼ�Ķ��㲻����10�����߲�����20���������������Ҫ�����ݹ�/�ǵݹ������㷨����

Ӧ�������㷨���һ��Ӧ�á�
*/

typedef struct node//�߱���
{
	int adjvex;        //�ڽӵ����±꣩
	struct node *next;//��һ������ָ�� 
} EdgeNode;
typedef struct //�������
{
	char  vertex[10];      //���������� 
	EdgeNode * firstedge;//������ͷָ��
} VertexNode;

typedef struct sta
{
	EdgeNode * edge;
}STA;


VertexNode*  CreateGraph(VertexNode* AdjGraph, int ver_num);//�����ڽӱ�
int serch(VertexNode* AdjGraph, char *v_name, int max_num);//����������Ķ����λ��
void printf_v(VertexNode *AdjGraph, int max_num);//��ӡ�ڽӱ�
int DFS_pass(VertexNode* AdjGraph, int max_num, int choice, int *array_2);//�ж��Ƿ��������
void DFS_print(VertexNode* AdjGraph, int *pass_array, int i, int flag, int *array_2, int max_num, int num, int the_tree_num);//�ݹ���ȱ����㷨
void DFS_print_no_recursive(VertexNode * AdjGraph, int *pass_array, int i, int max_num);//�ǵݹ�������������㷨
void BFS1(VertexNode * AdjGraph, int max_num, int *false_pass, int visit_num);//������������㷨
void print_tree(int tree_num, int *array_2, VertexNode *AdjGraph, int max_num);//��ӡ����ɭ�֣���������

int main()
{
	VertexNode* AdjGraph = NULL;
	int ver_num, *array_2;

	//��ʼ���ڽӱ�
	printf("�����붥��ĸ�����");
	scanf("%d", &ver_num);
	AdjGraph = CreateGraph(AdjGraph, ver_num);
	array_2 = (int*)malloc(sizeof(int)*(ver_num * 2));
	int tree_num = 0;
	int choice;
	do {
		printf("-------------------------------------------\n");
		printf("1.������ȱ����ݹ��㷨\n");
		printf("2.������ȱ����ǵݹ��㷨\n");
		printf("3.������ȱ���\n");
		printf("4.��ͼ�е�ɭ��\n");
		printf("5.��ӡͼ���ڽӱ�\n");
		printf("����������ѡ��\n");
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
			printf("����������������������\n");
			break;
		}

		printf("\n�������������ô��\n����������1���˳�������0.\n");
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
	printf("������������������\n");
	return 0;
}
VertexNode*  CreateGraph(VertexNode* AdjGraph, int ver_num)
{
	int edge_num;

	AdjGraph = (VertexNode*)malloc(sizeof(VertexNode)*ver_num);
	if (AdjGraph == NULL)
	{
		printf("�����쳣�˳���\n");
		exit(0);
	}
	printf("������ߵĸ�����");
	scanf("%d", &edge_num);

	int i;
	printf("-------------------------------------------\n");
	for (i = 0; i < ver_num; i++)
	{
		printf("�������%d����������ƣ�ע������С��10���ַ�����", i + 1);
		scanf("%s", AdjGraph[i].vertex);
		AdjGraph[i].firstedge = NULL;
	}

	for (i = 0; i < edge_num; i++)
	{
		char v1[10], v2[10];
		int v1_num = 0, v2_num = 0;
		printf("-------------------------------------------\n");
		printf("�������%d���ߵĵ�һ���˵�����ƣ�", i + 1);
		while (v1_num == 0)
		{
			scanf("%s", v1);
			v1_num = serch(AdjGraph, v1, ver_num);
		}

		printf("�������%d���ߵĵڶ����˵�����ƣ�", i + 1);
		while (v2_num == 0)
		{
			scanf("%s", v2);
			v2_num = serch(AdjGraph, v2, ver_num);
		}

		EdgeNode *p, *pr;
		p = (EdgeNode*)malloc(sizeof(EdgeNode));
		if (p == NULL)
		{
			printf("�����쳣�˳���\n");
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
			printf("�����쳣�˳���\n");
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
} //ʱ�临�Ӷȣ�O(2e+n) 
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
	printf("�������һ�������������ƣ�");
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
{                                                                            //num �������ڵĸ���λ��  the_tree_num ���������Ŀ���
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
	//��ʼ����ջ���
	STA *sta;
	int top = -1;
	sta = (STA *)malloc(sizeof(STA)*max_num);
	if (sta == NULL)
	{
		printf("�����쳣�˳���\n");
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
void BFS1(VertexNode * AdjGraph, int max_num, int *false_pass, int visit_num)//����û�н����ȹ���
{
	int *Queue;
	int fist_num = 0, last_num = 0;
	Queue = (int*)malloc(sizeof(int)*max_num);
	if (Queue == NULL)
	{
		printf("�����쳣�˳���\n");
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
	printf("�����  �±�  ���� ���ڵ�λ�� ���ڵ�����\n");
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