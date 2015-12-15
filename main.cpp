#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct path
{
	int x;
	path *next;
};

class sc_map
{
private:
	int i, j, k;
	int *check;//check数组存储的是各点是否访问过
	path *Map[100];//链表存储图
	int n;
	path *head, *s, *s1, *ss;
public:
	sc_map()
	{
		cout << "Please input the number of points:" << endl;
		cin >> n;
		for (i = 1; i <= n; i++)
			Map[i] = (path*)new(path);
		for (i = 1; i <= n; i++)
		{
			Map[i]->x = i;//Map[i]存的是自己的标号，Map[i]->next才是i点连接的第一个点。
			Map[i]->next = NULL;//初始化链表
		}

		check = new int[n + 1];

		for (i = 1; i <= n - 1; i++)
			for (j = i + 1; j <= n; j++)
			{
				k = rand() % 2;  //k=1代表i与j之间有一条无向边，k=0代表没有边
				if (k)
				{
					cout << '[' << i << "-->" << j << ']' << endl;
					s = (path*)new(path);
					ss = (path*)new(path);
					ss = Map[i];
					while (ss->next != NULL)
						ss = ss->next;
					s->x = j;
					s->next = NULL;
					ss->next = s;


					s = (path*)new(path);//无向边，所以还要反向存一次
					ss = (path*)new(path);
					ss = Map[j];
					while (ss->next != NULL) //找到链表尾
						ss = ss->next;
					s->x = i;
					s->next = NULL;
					ss->next = s;
				}

			}
		cout << "deep1:" << endl;
		for (i = 1; i <= n; i++)
			check[i] = 0; //DFS之前先设置所有点都没有访问过
		for (k = 1; k <= n; k++)
			if (check[k] == 0)
			{
				check[k] = 1;
				deep1(k);
			}
		cout << endl;

		cout << "deep2:" << endl;
		for (i = 1; i <= n; i++)
			check[i] = 0;
		head = (path*)new(path);
		s1 = (path*)new(path);
		deep2();
		cout << endl;

		cout << "width:" << endl;
		for (i = 1; i <= n; i++)
			check[i] = 0;
		width();
	}

	void push(int num)//将路径的节点压入链表
	{
		path *s2;//新建一个节点s2，存入num信息后加到链表尾
		s2 = (path*)new(path);
		s2->x = num;
		s1->next = s2;
		s2->next = NULL;
	}

	int pop()//将节点弹出路径
	{
		path *s2;
		s2 = (path*)new(path);
		s2 = head;
		if (s2->next == NULL)//当链表只有一个节点时
		{
			s1 = NULL;//链表尾弹出后，链表为NULL
			return 0;
		}

		while (s2->next != s1)
			s2 = s2->next;

		s2->next = NULL;
		s1 = s2;
	}

	int deep1(int num)
	{
		int i;
		path *s2;
		s2 = (path*)new(path);
		cout << num << ' ';
		s2 = Map[num]->next;// Map[num]->next是num点连接的第一个点
		if (s2 == NULL)
			return 0;
		while (1)
		{
			if (check[s2->x] == 0)
			{
				check[s2->x] = 1;
				deep1(s2->x);
			}
			if (s2->next == NULL)
				break;
			s2 = s2->next;
		}
	}

	void deep2()
	{
		int i, j, find_out = 0;
		for (i = 1; i <= n; i++)
			if (check[i] == 0)
			{
				cout << i << ' ';
				head->x = i;
				head->next = NULL;
				s1 = head; //链表位尾指针指向链表头
				check[i] = 1;
				while (1)
				{
					find_out = 0;
					s = (path*)new(path);
					s = Map[s1->x]->next;
					while (1)
					{
						if (check[s->x] == 1 && s->next == NULL) //如果到达了链表尾还没有找到可以到达的点
							break;
						if (check[s->x] == 0) //找到了可以到达的点
						{
							find_out = 1; //设置标记
							break;
						}
						s = s->next;
					}

					if (find_out == 1) //如果找到了可以到达的点
					{
						cout << s->x << ' ';
						check[s->x] = 1;//设置该点为“到达过”
						push(s->x); //将该点加入链表
						s1 = s1->next; //s1移动到链表尾
					}
					if (find_out == 0) //如果没有可以到达的点了
						pop(); //将链表尾弹出（相当于回溯过程）
					if (s1 == NULL) //如归链表为空，强制弹出
						break;
				}
			}
	}

	void width()
	{
		int i, j, find_out = 0;
		for (i = 1; i <= n; i++)
			if (check[i] == 0)
			{
				cout << i << ' ';
				head->x = i;
				head->next = NULL;
				s1 = head;//指针s1指向链表头
				check[i] = 1;
				while (1)
				{
					find_out = 0;//清除标志位
					s = Map[s1->x]->next; //找到s1->x连接的点
					while (1)
					{
						if (check[s->x] == 0) //如果该点没有被访问过
						{
							find_out = 1; //设置标志位
							cout << s->x << ' ';
							check[s->x] = 1; //设置该点为“访问过”
							push(s->x); //将该点加入队列
										//这里因为是宽度优先搜索，所以对比deep2，我们找到可以加入路径中的点后没有立马跳出，而是继续搜索相同深度的其他点。
						}
						if (s->next == NULL)
							break;
						s = s->next; //找到s1->x连接的下一个点
					}
					s1 = s1->next; //指针后移
					if (s1 == NULL)//如归链表为空，强制弹出
						break;
				}
			}
	}
};
int main()
{
	srand(time(NULL));
	sc_map m;
	//system("pause");
	return 0;
}