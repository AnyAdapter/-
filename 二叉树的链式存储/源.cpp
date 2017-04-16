//�ڴ���ļ��� 
#include<stdio.h>
#include<stdlib.h>
//�Զ�����������
typedef int DataType;

//����������Ĵ洢��ʽ
typedef struct bnode {
	DataType data;
	struct bnode *lchild, *rchild;
	// struct bnode *partent;
}Bnode,*BTree;

//����ջ�Ĵ洢��ʽ������ʵ�����������
typedef struct node {
	struct bnode *link;
	struct node *next;
}StackNode, *PStackNode;
typedef struct {
	PStackNode top;
}LinkStack,*PLinkStack;

//������еĴ洢��ʽ������ʵ�ֲ�α�����
typedef struct node_1 {
	struct bnode *link;
	struct node_1 *next;
}Qnode,*PQNode;
typedef struct {
	PQNode front, real;
}LinkQueue,*PLinkQueue;

//��������(ջ)
PLinkStack Init_LinkStack();	//��ʼ��ջ
int Empty_LinkStack(PLinkStack S); //�ж�ջ�գ�1��ʾ�գ�0��ʾ�ǿգ�
int Push_LinkStack(PLinkStack S, struct bnode  *x);//��ջ������1��ʾ��ջ�ɹ���0��ʾʧ�ܣ�
int Pop_LinkStack(PLinkStack S, struct bnode  **x);//��ջ������1��ʾ��ջ�ɹ���0��ʾʧ�ܣ�
int GetTop_LinkStack(PLinkStack S, struct bnode  **x);//ȥջ��Ԫ�أ�����1��ʾȡջ���ɹ���0��ʾʧ�ܣ�
void Destroy_LinkStack(PLinkStack *LS);	//����ջ

//��������(����)
PLinkQueue Init_LinkQueue();//��ʼ������
int Empty_LinkQueue(PLinkQueue Q);//�ж϶ӿգ�1��ʾ�գ�0��ʾ�ǿգ�
int In_LinkQueue(PLinkQueue Q,struct bnode *x);//���ӣ�����1��ʾ���ӳɹ���0��ʾʧ�ܣ�
int Out_LinkQueue(PLinkQueue Q,struct bnode **x);//���ӣ�����1��ʾ���ӳɹ���0��ʾʧ�ܣ�
int Front_LinkQueue(PLinkQueue Q,struct bnode **x);//ȡ��ͷԪ�أ�����1��ʾȡ��ͷ�ɹ���0��ʾʧ�ܣ�
void Destory_LinkQueue(PLinkQueue *Q);//���ٶ���

//��������(������)
void Count_Tree(BTree t);	//����������Ľ�������������ȫ�ֱ���count��
int Count(BTree t);	//����������Ľ�����������Ϊ����ֵ����
int Height(BTree t);//����������ĸ߶ȣ������Ϊ����ֵ����
BTree CopyTree(BTree t);	//���ƶ������������Ϊ����ֵ����
BTree CreateBinTree();	//������������洢�Ķ�����

//����(�ݹ�)
void PreOrder_1(BTree t);//�������
void InOrder_1(BTree t);//�������
void PostOrder_1(BTree t);//�������
//����(ջ)
void PreOrder_2(BTree t);//�������
void InOrder_2(BTree t);//�������
void PostOrder_2(BTree t);//�������
//��������α�������ʵ�֣�
void Order(BTree t);//��α���������ʵ�֣�
//������
void Visit(DataType data);//�������

//ȫ�ֱ���
int count = 0;

//���������
int main()
{
	return 0;
}

//(ջ)
PLinkStack Init_LinkStack()		//��ʼ��ջ
{
	PLinkStack S;
	S = (PLinkStack)malloc(sizeof(LinkStack));
	if (S != NULL)
	{
		S->top = NULL;
	}
	return S;
}

int Empty_LinkStack(PLinkStack S) //�ж�ջ�գ�1��ʾ�գ�0��ʾ�ǿգ�
{
	if (S->top = NULL)
	{
		return 1;
	}
	return 0;
}

int Push_LinkStack(PLinkStack S, struct bnode  *x)//��ջ������1��ʾ��ջ�ɹ���0��ʾʧ�ܣ�
{
	PStackNode p;
	p = (PStackNode)malloc(sizeof(StackNode));
	if (p == NULL)
	{
		printf("\n�ڴ治��\n");
		return 0;
	}
	p->link = x;
	p->next = S->top;
	S->top = p;
	return 1;
}

int Pop_LinkStack(PLinkStack S, struct bnode  **x)//��ջ������1��ʾ��ջ�ɹ���0��ʾʧ�ܣ�
{
	PStackNode p;
	if (Empty_LinkStack(S) == 1)
	{
		printf("\nջ�գ��޷���ջ\n");
		return 0;
	}
	p = S->top;
	*x = p->link;
	S->top = S->top->next;
	free(p);
	return 1;
}

int GetTop_LinkStack(PLinkStack S, struct bnode  **x)//ȥջ��Ԫ�أ�����1��ʾȡջ���ɹ���0��ʾʧ�ܣ�
{
	if (Empty_LinkStack(S) ==  1)
	{
		printf("\nջ�գ��޷�ȡջ��Ԫ��\n");
		return 0;
	}
	*x = S->top->link;
	return 1;
}

void Destroy_LinkStack(PLinkStack *LS)	//����ջ
{
	PStackNode p, q;
	if (*LS != NULL)
	{
		p = (*LS)->top;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			free(q);
		}
		free(*LS);
	}
	*LS = NULL;
	return;
}
		
//�����У�
PLinkQueue Init_LinkQueue(void)//��ʼ��һ�¶��У���ں������ޣ�����ֵ���¶���ָ�룬null��ʾʧ��
{
	PLinkQueue Q;
	Q = (PLinkQueue)malloc(sizeof(LinkQueue));
	if (Q)
	{
		Q->front = NULL;
		Q->real = NULL;
	}
	return Q;
}

int Empty_LinkQueue(PLinkQueue Q)//�ж϶����Ƿ�Ϊ�գ���ں�����������ָ�룬����ֵ��1��ʾ�ӿգ�0��ʾ�ǿ�
{
	if (Q && Q->front == NULL &&Q->real == NULL)
		return 1;
	else
		return 0;
}

int In_LinkQueue(PLinkQueue Q, struct bnode *x)//��Ӳ�������ں�����������ָ��ʹ����x������ֵ��1��ʾ��ӳɹ���0��ʾ���ʧ��
{
	PQNode p;
	p = (PQNode)malloc(sizeof(Qnode));
	if (!p)
	{
		printf("�ڴ����\n");
		return 0;
	}
	else
	{
		p->link = x;
		p->next = NULL;
		if (Empty_LinkQueue(Q))
			Q->real = Q->front = p;
		else
		{
			Q->real->next = p;
			Q->real = p;
		}
		return 1;
	}
}

int Out_LinkQueue(PLinkQueue Q, struct bnode **x)//���Ӳ�������ں����������е�ָ�룬����ֵ��1��ʾ���ӳɹ���0��ʾ����ʧ��,����Ԫ����**x����
{
	
	PQNode p;
	if (Empty_LinkQueue(Q))
	{
		printf("\n�ӿ�\n");
		return 0;
	}
	*x = Q->front->link;
	p = Q->front;
	Q->front = Q->front->next;
	free(p);
	if (!Q->front)
		Q->real = NULL;
	return 1;
}

int Front_LinkQueeu(PLinkQueue Q, struct bnode **x)//ȡ��ͷԪ�أ���ں����������е�ָ�룬����ֵ��1��ʾ���ӳɹ���0��ʾ����ʧ��,��ͷԪ����**x����
{
	if (Empty_LinkQueue(Q))
	{
		printf("\n�ӿ�\n");
		return 0;
	}
	*x = Q->front->link;
	return 1;
}

void Destroy_LinkQueue(PLinkQueue *Q)//���ٶ��У���ں����������е�ָ��ĵ�ַ������ֵ����
{
	PQNode p;
	PLinkQueue s;
	s = *Q;
	if (*Q)
	{
		while (s->front)
		{
			p = s->front;
			s->front = s->front->next;
			free(p);
		}
		free(*Q);
	}
	*Q = s = NULL;
}
										
//(������)
void Count_Tree(BTree t)	//����������Ľ�������������ȫ�ֱ���count��,����ڶ��������ʱ��Ӧ���Ƚ�count����
{
	if (t != NULL)
	{
		Count_Tree(t->lchild);
		Visit(t->data);
		count += 1;
		Count_Tree(t->rchild);
	}
}

int Count(BTree t)	//����������Ľ�����������Ϊ����ֵ����
{
	int lcount, rcount;
	if (t == NULL)
	{
		return 0;
	}
	lcount = Count(t->lchild);
	rcount = Count(t->rchild);
	return (lcount + rcount + 1);
}

int Height(BTree t)//����������ĸ߶ȣ������Ϊ����ֵ����
{
	int h1, h2;
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		h1 = Height(t->lchild);
		h2 = Height(t->rchild);
		if (h1 > h2)
		{
			return (h1 + 1);
		}
		return (h2 + 1);
	}
}

BTree CopyTree(BTree t)	//���ƶ������������Ϊ����ֵ����
{
	BTree p, q, s;
	if (t == NULL)
	{
		return NULL;
	}
	p = CopyTree(t->lchild);
	q = CopyTree(t->rchild);
	s = (Bnode *)malloc(sizeof(Bnode));
	if (s == NULL)
	{
		return NULL;
	}
	s->data = t->data;
	s->lchild = p;
	s->rchild = q;
	return s;
}

BTree CreateBinTree()//������������洢�Ķ�����
{
	BTree t;
	char ch;
	ch = getchar();
	if (ch == '#' )
	{
		t = NULL;
	}
	else
	{
		t = (Bnode *)malloc(sizeof(Bnode));
		if (t == NULL)
		{
			printf("\n�ڴ治��\n");
			return NULL;
		}
		t->data = ch;
		t->lchild = CreateBinTree();
		t->rchild = CreateBinTree();
	}
	return t;
}

//����(�ݹ�)
void PreOrder_1(BTree t)//�������
{
	if (t != NULL)
	{
		Visit(t->data);
		PreOrder_1(t->lchild);
		PostOrder_1(t->rchild);
	}
}

void InOrder_1(BTree t)//�������
{
	if (t != NULL)
	{
		InOrder_1(t->lchild);
		Visit(t->data);
		InOrder_1(t->rchild);
	}
}

void PostOrder_1(BTree t)//�������
{
	if (t != NULL)
	{
		PostOrder_1(t->lchild);
		PostOrder_1(t->rchild);
		Visit(t->data);
	}
}

//����(ջ)
void PreOrder_2(BTree t)//�������
{
	PLinkStack S;
	BTree p = t;
	S = Init_LinkStack();
	while (p != NULL || Empty_LinkStack(S) == 0)//ջ�ǿջ������ǿ�
	{
		if (p != NULL)
		{
			Visit(p->data);
			Push_LinkStack(S,p);
			p = p->lchild;
		}
		else
		{
			Pop_LinkStack(S,&p);
			p = p->rchild;
		}
	}
}

void InOrder_2(BTree t)//�������
{
	PLinkStack S;
	BTree p = t;
	S = Init_LinkStack();
	while (p != NULL || Empty_LinkStack(S) == 0)//ջ�ǿջ������ǿ�
	{
		if (p != NULL)
		{
			Push_LinkStack(S, p);
			p = p->lchild;
		}
		else
		{
			Pop_LinkStack(S, &p);
			Visit(p->data);
			p = p->rchild;
		}
	}
}

void PostOrder_2(BTree t)//�������
{
	PLinkStack S1;
	PLinkStack S2;
	BTree p = t;
	S1 = Init_LinkStack();
	S2 = Init_LinkStack();
	while (p != NULL || Empty_LinkStack(S2) == 0)//S1ջ�ǿջ������ǿ�
	{
		if (p != NULL)
		{
			Push_LinkStack(S1,p);
			Push_LinkStack(S2,p);
			p = p->rchild;
		}
		else
		{
			Pop_LinkStack(S2,&p);
			p = p->lchild;
		}
	}
	while (Empty_LinkStack(S1) != 0)
	{
		Pop_LinkStack(S1,&p);
		Visit(p->data);
	}
}

//��������α�������ʵ�֣�
void Order(BTree t)//��α���������ʵ�֣�
{
	PLinkQueue Q;
	BTree p = t;
	Q = Init_LinkQueue();
	if (p != NULL)
	{
		Visit(p->data);
		In_LinkQueue(Q,p);
	}
	else
	{
		printf("\n��Ϊ��\n");
		return;
	}
	while ( Empty_LinkQueue(Q) == 0)//���зǿ�
	{
		Out_LinkQueue(Q,&p);
		if (p->lchild != NULL)
		{
			p = p->lchild;
			Visit(p->data);
			In_LinkQueue(Q, p);
		}
		if (p->rchild)
		{
			p = p->rchild;
			Visit(p->data);
			In_LinkQueue(Q, p);
		}
	}
}

//������
void Visit(DataType data)//�������
{
	printf("%c",data);
}
