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
	int *check;//check����洢���Ǹ����Ƿ���ʹ�
	path *Map[100];//����洢ͼ
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
			Map[i]->x = i;//Map[i]������Լ��ı�ţ�Map[i]->next����i�����ӵĵ�һ���㡣
			Map[i]->next = NULL;//��ʼ������
		}

		check = new int[n + 1];

		for (i = 1; i <= n - 1; i++)
			for (j = i + 1; j <= n; j++)
			{
				k = rand() % 2;  //k=1����i��j֮����һ������ߣ�k=0����û�б�
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


					s = (path*)new(path);//����ߣ����Ի�Ҫ�����һ��
					ss = (path*)new(path);
					ss = Map[j];
					while (ss->next != NULL) //�ҵ�����β
						ss = ss->next;
					s->x = i;
					s->next = NULL;
					ss->next = s;
				}

			}
		cout << "deep1:" << endl;
		for (i = 1; i <= n; i++)
			check[i] = 0; //DFS֮ǰ���������е㶼û�з��ʹ�
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

	void push(int num)//��·���Ľڵ�ѹ������
	{
		path *s2;//�½�һ���ڵ�s2������num��Ϣ��ӵ�����β
		s2 = (path*)new(path);
		s2->x = num;
		s1->next = s2;
		s2->next = NULL;
	}

	int pop()//���ڵ㵯��·��
	{
		path *s2;
		s2 = (path*)new(path);
		s2 = head;
		if (s2->next == NULL)//������ֻ��һ���ڵ�ʱ
		{
			s1 = NULL;//����β����������ΪNULL
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
		s2 = Map[num]->next;// Map[num]->next��num�����ӵĵ�һ����
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
				s1 = head; //����λβָ��ָ������ͷ
				check[i] = 1;
				while (1)
				{
					find_out = 0;
					s = (path*)new(path);
					s = Map[s1->x]->next;
					while (1)
					{
						if (check[s->x] == 1 && s->next == NULL) //�������������β��û���ҵ����Ե���ĵ�
							break;
						if (check[s->x] == 0) //�ҵ��˿��Ե���ĵ�
						{
							find_out = 1; //���ñ��
							break;
						}
						s = s->next;
					}

					if (find_out == 1) //����ҵ��˿��Ե���ĵ�
					{
						cout << s->x << ' ';
						check[s->x] = 1;//���øõ�Ϊ���������
						push(s->x); //���õ��������
						s1 = s1->next; //s1�ƶ�������β
					}
					if (find_out == 0) //���û�п��Ե���ĵ���
						pop(); //������β�������൱�ڻ��ݹ��̣�
					if (s1 == NULL) //�������Ϊ�գ�ǿ�Ƶ���
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
				s1 = head;//ָ��s1ָ������ͷ
				check[i] = 1;
				while (1)
				{
					find_out = 0;//�����־λ
					s = Map[s1->x]->next; //�ҵ�s1->x���ӵĵ�
					while (1)
					{
						if (check[s->x] == 0) //����õ�û�б����ʹ�
						{
							find_out = 1; //���ñ�־λ
							cout << s->x << ' ';
							check[s->x] = 1; //���øõ�Ϊ�����ʹ���
							push(s->x); //���õ�������
										//������Ϊ�ǿ���������������ԶԱ�deep2�������ҵ����Լ���·���еĵ��û���������������Ǽ���������ͬ��ȵ������㡣
						}
						if (s->next == NULL)
							break;
						s = s->next; //�ҵ�s1->x���ӵ���һ����
					}
					s1 = s1->next; //ָ�����
					if (s1 == NULL)//�������Ϊ�գ�ǿ�Ƶ���
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