#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int Elmtype;

typedef struct QNode
{
    Elmtype data;
    struct QNode* next;
}QNode,*QueuePtr;

typedef struct LinkQueue
{
    QueuePtr front,rear;
}LinkQueue;


//初始化队列，创建空队列
Status InitQueue(LinkQueue *Q)
{
    Q->front=Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        exit(_OVERFLOW);
    Q->front->next = NULL;
    return OK;
}

//判断是否空队列
Status QueueEmpty(LinkQueue Q)
{
    if(Q.front == Q.rear)
        return TRUE;
     else
        return FALSE;
}

//求出队列长度
int QueueLength(LinkQueue Q)
{
    int i = 0;
    QueuePtr p;
    p = Q.front;
    while(p != Q.rear)
    {
        i++;
        p = p->next;
    }
    return i;
}

//在队列的末尾添加数据
Status EnQueue(LinkQueue *Q, Elmtype e)
{
   QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
   if(!s)
    exit(_OVERFLOW);
    s->data = e;
    s->next = NULL;

     Q->rear->next = s;     //将队尾结点的一个元素指向s
     Q->rear = s;           //后rear指向s成为新的后结点

     return OK;
   
}

//访问元素成员
void visit(Elmtype e)
{
    printf("%d ",e);
}

//遍历队列元素
Status QueueTraverse(LinkQueue Q)
{
    QueuePtr p;
    p = Q.front->next;
    while(p != Q.rear)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");

    return OK;
}

//获取队头元素
Status GetHead(LinkQueue Q,Elmtype* e)
{
    if(Q.front == Q.rear)
        return ERROR;
        *e = Q.front->next->data;
    return OK;
}

Status DeQueue(LinkQueue *Q, Elmtype *e)
{
    QueuePtr p;

    p = Q->front->next;         //指向队头第一个节点

    if(Q->front == Q->rear)     //如果头尾相等为空队
        return ERROR;
    *e =p->data;                //将删除的数据给e
    Q->front->next = p->next;   //让队头的下一位成为队头
    if(Q->rear == p)            //若删除的就是队尾,尾指针等于头指针，让其成为空队列
        Q->rear = Q->front;
    free(p);

    return OK;
}

//清空队列
Status ClearQueue(LinkQueue *Q)
{
    QueuePtr p,q; 
    p = Q->front->next;
    while(p)
    {
        q =p;
        p = p->next;
        free(q);
        
    }
    Q->rear = Q->front;
    Q->front->next = NULL;
    return OK;
}

//销毁队列Q
Status DestroyDueue(LinkQueue *Q)
{
    while(Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }

    return OK;
}

int main()
{
    Status i;
    Elmtype d;
    LinkQueue Q;

    i = InitQueue(&Q);
    if(i)
        printf("成功构造了一个空队列!\n");
        printf("是否空队列 %d(1:空 0:否)\n",QueueEmpty(Q));
        printf("队列的长度为%d\n",QueueLength(Q));
        EnQueue(&Q,-3);
        EnQueue(&Q,5);
        EnQueue(&Q,10);
        printf("插入3个元素(-5,5,10)后,队列长度为%d\n",QueueLength(Q));
        QueueTraverse(Q);

        i = GetHead(Q,&d);
        if(i == OK)
            printf("队头元素是:%d \n",d);
        DeQueue(&Q,&d);
        if(i == OK)
        printf("删除了队头元素为%d \n",d);
        ClearQueue(&Q);
        printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",Q.front,Q.rear,Q.front->next);
        DestroyDueue(&Q);
        printf("销毁队列后,q.front=%u q.rear=%u\n",Q.front, Q.rear);
        

    return 0;
}