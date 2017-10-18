#include <stdio.h>
#define MAX 400
#define SUCC 1
#define FAIL 0
typedef int element_type;

//x进队函数
int addq(int q[],int first,int &last,int &count,int x)
{
    if(count==MAX)
        return FAIL;
    q[last] = x;
    last=(last+1)%MAX;
    count++;
	return SUCC;
}
//x出队函数
int delq(int q[],int &first,int last,int &count,int &x)
{
    if(count==0) 
        return FAIL;
    x=q[first];
    first=(first+1)%MAX;
	count--;
	return SUCC;
}

//输出队列中所有元素的函数
void print(int q[],int first,int count)
{
	int i,j;
	if(count == 0)
	{
		printf("当前队列中没有元素!\n");return;
	}
	printf("当前队列中的元素为：\n");
	i=first;
	for(j=1;j<=count;j++)
	{
        printf("%4d",q[i]);
        i=(i+1)%MAX;
	}
	printf("\n");
}

//主函数
int main()
{
	int q[MAX],first=0,last=0,count=0,c,k,x;
	while(1)
	{
		printf("请输入操作码,1:进队；2:出队;3:显示队内容;0:结束 c=");
		scanf("%d",&c);
		if(c==0) break;
		if(c==1)
		{
			printf("请输入进队元素x:");
			scanf("%d",&x);
			k=addq(q,first,last,count,x);
			if(k==0) printf("队已满，进队失败!\n");
			else printf("%d已进队!\n",x);
		}
		else if(c==2)
		{
			k=delq(q,first,last,count,x);
			if(k==0) printf("队空,无元素出队!\n");
			else printf("元素%d已从队中退出!\n",x);
		}
		else if(c==3) print(q,first,count);
	}
    printf("程序结束\n");
    return 0;
}
