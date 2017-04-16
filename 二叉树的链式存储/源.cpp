//期待你的加入 
#include<stdio.h>
#include<stdlib.h>
//自定义数据类型
typedef int DataType;

//定义二叉树的存储形式
typedef struct bnode {
	DataType data;
	struct bnode *lchild, *rchild;
	// struct bnode *partent;
}Bnode,*BTree;

//定义栈的存储形式（用于实现三大遍历）
typedef struct node {
	struct bnode *link;
	struct node *next;
}StackNode, *PStackNode;
typedef struct {
	PStackNode top;
}LinkStack,*PLinkStack;

//定义队列的存储形式（用于实现层次遍历）
typedef struct node_1 {
	struct bnode *link;
	struct node_1 *next;
}Qnode,*PQNode;
typedef struct {
	PQNode front, real;
}LinkQueue,*PLinkQueue;

//声明函数(栈)
PLinkStack Init_LinkStack();	//初始化栈
int Empty_LinkStack(PLinkStack S); //判断栈空（1表示空，0表示非空）
int Push_LinkStack(PLinkStack S, struct bnode  *x);//进栈（返回1表示进栈成功，0表示失败）
int Pop_LinkStack(PLinkStack S, struct bnode  **x);//出栈（返回1表示出栈成功，0表示失败）
int GetTop_LinkStack(PLinkStack S, struct bnode  **x);//去栈顶元素（返回1表示取栈顶成功，0表示失败）
void Destroy_LinkStack(PLinkStack *LS);	//销毁栈

//声明函数(队列)
PLinkQueue Init_LinkQueue();//初始化队列
int Empty_LinkQueue(PLinkQueue Q);//判断队空（1表示空，0表示非空）
int In_LinkQueue(PLinkQueue Q,struct bnode *x);//进队（返回1表示进队成功，0表示失败）
int Out_LinkQueue(PLinkQueue Q,struct bnode **x);//出队（返回1表示出队成功，0表示失败）
int Front_LinkQueue(PLinkQueue Q,struct bnode **x);//取对头元素（返回1表示取对头成功，0表示失败）
void Destory_LinkQueue(PLinkQueue *Q);//销毁队列

//声明函数(二叉树)
void Count_Tree(BTree t);	//计算二叉树的结点数，结果放在全局变量count中
int Count(BTree t);	//计算二叉树的结点数，结果作为返回值返回
int Height(BTree t);//计算二叉树的高度，结果作为返回值返回
BTree CopyTree(BTree t);	//复制二叉树，结果作为返回值返回
BTree CreateBinTree();	//创建二叉链表存储的二叉树

//遍历(递归)
void PreOrder_1(BTree t);//先序遍历
void InOrder_1(BTree t);//中序遍历
void PostOrder_1(BTree t);//后序遍历
//遍历(栈)
void PreOrder_2(BTree t);//先序遍历
void InOrder_2(BTree t);//中序遍历
void PostOrder_2(BTree t);//后序遍历
//遍历（层次遍历队列实现）
void Order(BTree t);//层次遍历（队列实现）
//处理结点
void Visit(DataType data);//输出内容

//全局变量
int count = 0;

//主函数入口
int main()
{
	return 0;
}

//(栈)
PLinkStack Init_LinkStack()		//初始化栈
{
	PLinkStack S;
	S = (PLinkStack)malloc(sizeof(LinkStack));
	if (S != NULL)
	{
		S->top = NULL;
	}
	return S;
}

int Empty_LinkStack(PLinkStack S) //判断栈空（1表示空，0表示非空）
{
	if (S->top = NULL)
	{
		return 1;
	}
	return 0;
}

int Push_LinkStack(PLinkStack S, struct bnode  *x)//进栈（返回1表示进栈成功，0表示失败）
{
	PStackNode p;
	p = (PStackNode)malloc(sizeof(StackNode));
	if (p == NULL)
	{
		printf("\n内存不足\n");
		return 0;
	}
	p->link = x;
	p->next = S->top;
	S->top = p;
	return 1;
}

int Pop_LinkStack(PLinkStack S, struct bnode  **x)//出栈（返回1表示出栈成功，0表示失败）
{
	PStackNode p;
	if (Empty_LinkStack(S) == 1)
	{
		printf("\n栈空，无法出栈\n");
		return 0;
	}
	p = S->top;
	*x = p->link;
	S->top = S->top->next;
	free(p);
	return 1;
}

int GetTop_LinkStack(PLinkStack S, struct bnode  **x)//去栈顶元素（返回1表示取栈顶成功，0表示失败）
{
	if (Empty_LinkStack(S) ==  1)
	{
		printf("\n栈空，无法取栈顶元素\n");
		return 0;
	}
	*x = S->top->link;
	return 1;
}

void Destroy_LinkStack(PLinkStack *LS)	//销毁栈
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
		
//（队列）
PLinkQueue Init_LinkQueue(void)//初始化一新队列，入口函数：无，返回值：新队列指针，null表示失败
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

int Empty_LinkQueue(PLinkQueue Q)//判断队列是否为空，入口函数：链队列指针，返回值：1表示队空，0表示非空
{
	if (Q && Q->front == NULL &&Q->real == NULL)
		return 1;
	else
		return 0;
}

int In_LinkQueue(PLinkQueue Q, struct bnode *x)//入队操作，入口函数：链队列指针和带入队x，返回值：1表示入队成功，0表示入队失败
{
	PQNode p;
	p = (PQNode)malloc(sizeof(Qnode));
	if (!p)
	{
		printf("内存溢出\n");
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

int Out_LinkQueue(PLinkQueue Q, struct bnode **x)//出队操作，入口函数：链队列的指针，返回值：1表示出队成功，0表示出队失败,出队元素用**x保存
{
	
	PQNode p;
	if (Empty_LinkQueue(Q))
	{
		printf("\n队空\n");
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

int Front_LinkQueeu(PLinkQueue Q, struct bnode **x)//取队头元素，入口函数：链队列的指针，返回值：1表示出队成功，0表示出队失败,队头元素用**x保存
{
	if (Empty_LinkQueue(Q))
	{
		printf("\n队空\n");
		return 0;
	}
	*x = Q->front->link;
	return 1;
}

void Destroy_LinkQueue(PLinkQueue *Q)//销毁队列：入口函数：链队列的指针的地址，返回值：无
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
										
//(二叉树)
void Count_Tree(BTree t)	//计算二叉树的结点数，结果放在全局变量count中,当求第二个结点数时，应该先将count清零
{
	if (t != NULL)
	{
		Count_Tree(t->lchild);
		Visit(t->data);
		count += 1;
		Count_Tree(t->rchild);
	}
}

int Count(BTree t)	//计算二叉树的结点数，结果作为返回值返回
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

int Height(BTree t)//计算二叉树的高度，结果作为返回值返回
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

BTree CopyTree(BTree t)	//复制二叉树，结果作为返回值返回
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

BTree CreateBinTree()//创建二叉链表存储的二叉树
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
			printf("\n内存不足\n");
			return NULL;
		}
		t->data = ch;
		t->lchild = CreateBinTree();
		t->rchild = CreateBinTree();
	}
	return t;
}

//销毁一个二叉树
void DestroyBinTree(BTree *t)
{
	Bnode *p,*q,*f;
	if ( *t ==NULL)
	{
		return;
	}
	else
	{
		f = *t;
		p = (*t)->lchild;
		q = (*t)->rchild;
		DestroyBinTree(&p);
		DestroyBinTree(&q);
		free(f);
		*t = f = NULL;
	}
}

//遍历(递归)
void PreOrder_1(BTree t)//先序遍历
{
	if (t != NULL)
	{
		Visit(t->data);
		PreOrder_1(t->lchild);
		PostOrder_1(t->rchild);
	}
}

void InOrder_1(BTree t)//中序遍历
{
	if (t != NULL)
	{
		InOrder_1(t->lchild);
		Visit(t->data);
		InOrder_1(t->rchild);
	}
}

void PostOrder_1(BTree t)//后序遍历
{
	if (t != NULL)
	{
		PostOrder_1(t->lchild);
		PostOrder_1(t->rchild);
		Visit(t->data);
	}
}

//遍历(栈)
void PreOrder_2(BTree t)//先序遍历
{
	PLinkStack S;
	Bnode * p = t;
	S = Init_LinkStack();
	while (p != NULL || Empty_LinkStack(S) == 0)//栈非空或者树非空
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

void InOrder_2(BTree t)//中序遍历
{
	PLinkStack S;
	Bnode * p = t;
	S = Init_LinkStack();
	while (p != NULL || Empty_LinkStack(S) == 0)//栈非空或者树非空
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

void PostOrder_2(BTree t)//后序遍历
{
	PLinkStack S1;
	PLinkStack S2;
	Bnode * p = t;
	S1 = Init_LinkStack();
	S2 = Init_LinkStack();
	while (p != NULL || Empty_LinkStack(S2) == 0)//S1栈非空或者树非空
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

//遍历（层次遍历队列实现）
void Order(BTree t)//层次遍历（队列实现）
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
		printf("\n树为空\n");
		return;
	}
	while ( Empty_LinkQueue(Q) == 0)//队列非空
	{
		Out_LinkQueue(Q,&p);
		if (p->lchild != NULL)
		{
			Visit(p->lchild->data);
			In_LinkQueue(Q, p->lchild);
		}
		if (p->rchild !=  NULL)
		{
			Visit(p->rchild->data);
			In_LinkQueue(Q, p->rchild);
		}
	}
}

//处理函数
void Visit(DataType data)//输出内容
{
	printf("%c",data);
}
