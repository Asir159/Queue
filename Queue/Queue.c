#include <stdio.h>

#define MAXSIZE 20

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Elmtype;
typedef int Status;

typedef struct Queue
{
   Elmtype data[MAXSIZE];
   int front;
   int rear;
}SqQueue;

Status InitQueuse(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status QueueEmpty(SqQueue Q)
{
    if(Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

Status EnQueue(SqQueue *Q,Elmtype e)
{
    //判断队列是否为满
    if((Q->rear+1)% MAXSIZE == Q->front)
        return ERROR;
    Q->data[Q->rear] = e;           //往后添加数据

                                    //若数组没满
    Q->rear =(Q->rear+1) % MAXSIZE; //尾部指针往后移动,若到最后则转到头部

    return OK;
}

Status QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

Status DeQueue(SqQueue *Q,Elmtype* e)
{
    //判断队列是否为空
    if(Q->front == Q->rear)
        return ERROR;
    *e  = Q->data[Q->front];       //把头部元素给e
    Q->front = (Q->front+1) % MAXSIZE; //头指针往后移动,到后放回头部

    return OK;
}

void visit(Elmtype e)
{
    printf("%d ",e);
}

Status QueueTraverse(SqQueue Q)
{
    int i= 0;
    i = Q.front;
    while(i != Q.rear)
    {
        visit(Q.data[i]);
        i = (i+1) % MAXSIZE;
    }
    printf("\n");

    return OK;
}

//获取队头元素
Status GetHead(SqQueue Q, Elmtype* e)
{
    if(Q.front == Q.rear)
        return ERROR;
     else
        *e = Q.data[Q.front];
    return OK;
}

//清空队列
Status ClearQueue(SqQueue* Q)
{
    Q->front=Q->rear = 0;
    return OK;
}

int main()
{
    int i = 0,l;
    SqQueue Q;
    Elmtype d,j;
    InitQueuse(&Q);

    printf("初始化队列后，队列空否? %d(1:空 0:否)\n",QueueEmpty(Q));

    printf("请输入整队列元素(不超过%d个),-1为提前结束符 ",MAXSIZE-1);
    do
    {
        d=i+100;
        if(d == -1)
            break;
        i++;
        EnQueue(&Q,d);
    } while (i<MAXSIZE-1);

    printf("队列长度为: %d\n",QueueLength(Q));
    printf("现在队列空否? %d(1:空 0:否)\n",QueueEmpty(Q));
    printf("连续%d次由队头删除元素,队尾插入元素:\n",MAXSIZE);

    for(l=1;l<MAXSIZE; l++)
    {
        DeQueue(&Q,&d);
        printf("删除元素是%d,插入元素的,插入的元素:%d\n",d,l+1000);
        d = l+1000;
        EnQueue(&Q,d);
    }

    printf("现在队列的元素为: \n");
    QueueTraverse(Q);
    printf("共向队尾插入%d个元素\n",i+MAXSIZE);
    if(l-2 > 0)
    printf("现在由队头删除了%d个元素\n",l-2);
    while(QueueLength(Q) >2)
    {
        DeQueue(&Q,&d);
        printf("删除元素值为%d\n",d);
    }

    j=GetHead(Q,&d);
    if(j)
        printf("现在对头元素为: %d\n",d);
    ClearQueue(&Q);
    printf("清空队列后,队列空否? %d(1:空 0：否)",QueueEmpty(Q));
    
    return 0;
}